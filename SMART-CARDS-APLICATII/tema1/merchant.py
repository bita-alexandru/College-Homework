import socket
import pickle
from Cryptodome.PublicKey import RSA
from Cryptodome.Cipher import AES, PKCS1_OAEP
from Cryptodome.Random import get_random_bytes
from Cryptodome.Hash import SHA256
from Cryptodome.Signature import pkcs1_15

HOST = "127.0.0.1"
cPORT = 7777
pgPORT = 7776

BUFF = 4096

rsaKey = None
cSock = pgSock = sock = None
privKM = pubKM = pubKC = pubKPG = symKeyMPG = symKeyCM = None
nonceCM = nonceMPG = None
sid = signature = None

def encK(m, k, nc=False, use_nc=None):
    if use_nc != None:
        cipher = AES.new(k, AES.MODE_EAX, use_nc)
    else:
        cipher = AES.new(k, AES.MODE_EAX)

    if nc:
        return cipher.encrypt(m), cipher.nonce

    return cipher.encrypt(m)

def encP(m, p):
   cipher = PKCS1_OAEP.new(p)
   return cipher.encrypt(m)

def decK(m, k, nc):
   cipher = AES.new(k, AES.MODE_EAX, nc)
   return cipher.decrypt(m)

def decP(m, p):
   cipher = PKCS1_OAEP.new(p)
   return cipher.decrypt(m)

def sign(o, p):
   hash = SHA256.new(o)
   return pkcs1_15.new(p).sign(hash)

def ver(o, s, p):
   hash = SHA256.new(o)

   try:
      pkcs1_15.new(p).verify(hash, s)
   except (ValueError, TypeError):
      return False
   
   return True

def initializeServer():
    global sock
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((HOST, cPORT))
    sock.listen()

def initializeConnClient():
    global cSock
    cSock, cAddr = sock.accept()

def initializeConnPG():
    global pgSock
    pgSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    pgSock.connect((HOST, pgPORT))

def generateKeys():
    global privKM, pubKM, symKeyMPG, rsaKey
    symKeyMPG = get_random_bytes(16)
    rsaKey = RSA.generate(1024)
    privKM = rsaKey
    pubKM = rsaKey.publickey()

def certificateM():
    global pubKM
    fileOut = open("certificateM.pem", "wb")
    fileOut.write(pubKM.exportKey())
    fileOut.close()

def getPubKPG():
   global pubKPG
   pubKPG = RSA.importKey(open("certificatePG.pem").read())

def generateSidSig():
    global sid, signature
    sid = get_random_bytes(16)
    signature = sign(sid, rsaKey)

    print("sid=%s\nsig=%s"%(sid, signature))

def phase1():
    global symKeyCM, pubKC, nonceCM
    
    data = cSock.recv(BUFF)
    data = pickle.loads(data)

    nonceCM = data["NC"]
    symKeyCM = decP(data["K"], rsaKey)
    pubKC = RSA.importKey(decK(data["PubKC"], symKeyCM, nonceCM))

    # print("pubKC=%s\nsymKeyCM=%s"%(pubKC.exportKey(),symKeyCM))

def phase2():
    data = {
        "Sid": None,
        "SigM": None
    }

    data["Sid"] = encK(sid, symKeyCM, use_nc=nonceCM)
    data["SigM"] = encK(signature, symKeyCM, use_nc=nonceCM)

    # print(data)

    data = pickle.dumps(data)

    cSock.sendall(data)

def phase3():
    data = cSock.recv(BUFF)
    data = decK(data, symKeyCM, nonceCM)
    data = pickle.loads(data)

    PO = data["PO"]
    SigC = PO["SigC"]
    PO.pop("SigC")

    if not ver(pickle.dumps(PO), SigC, pubKC):
        print("Invalid signature!")
        return

    return data

def phase4(data):
    global nonceMPG

    PO = data["PO"]
    PM = data["PM"]
    KC = data["K"]
    NCC = data["NC"]

    M = {
        "Sid": sid,
        "PubKC": pubKC.exportKey(),
        "Amount": PO["Amount"]
    }
    SigM, nonceMPG = encK(sign(pickle.dumps(M), rsaKey), symKeyMPG, nc=True)
    
    data = {
        "PM": encK(pickle.dumps(PM), symKeyMPG, use_nc=nonceMPG),
        "SigM": SigM,
        "K": encP(symKeyMPG, pubKPG),
        "NC": nonceMPG,
        "KC": KC,
        "NCC": NCC
    }

    data = pickle.dumps(data)

    pgSock.sendall(data)

def phase5():
    data = pgSock.recv(BUFF)
    data = decK(data, symKeyMPG, nonceMPG)

    return data

def phase6(data):
    data = encK(data, symKeyCM, use_nc=nonceCM)
    cSock.sendall(data)

if __name__ == "__main__":
    generateKeys()
    certificateM()

    getPubKPG()

    # begin protocol
    initializeServer()
    initializeConnClient()

    # setup sub-protocol
    phase1()
    generateSidSig()
    phase2()

    # exchange sub-protocol
    data = phase3()
    
    initializeConnPG()
    phase4(data)

    data = phase5()
    phase6(data)