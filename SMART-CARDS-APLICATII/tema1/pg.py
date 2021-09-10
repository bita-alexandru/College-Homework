import json
import socket
import pickle
from Cryptodome.PublicKey import RSA
from Cryptodome.Cipher import AES, PKCS1_OAEP
from Cryptodome.Random import get_random_bytes
from Cryptodome.Hash import SHA256
from Cryptodome.Signature import pkcs1_15

HOST = "127.0.0.1"
mPORT = 7776

BUFF = 4096

privKPG = pubKPG = symKeyMPG = rsaKey = pubKM = None
nonceMPG = None
CCode = "1789"
sock = cSock = mSock = None

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
    sock.bind((HOST, mPORT))
    sock.listen()

def certificatePG():
    global pubKPG
    fileOut = open("certificatePG.pem", "wb")
    fileOut.write(pubKPG.exportKey())
    fileOut.close()

def getPubKM():
    global pubKM
    pubKM = RSA.importKey(open("certificateM.pem").read())

def initializeConnMerchant():
    global mSock
    mSock, mAddr = sock.accept()

def generateKeys():
    global privKPG, pubKPG, rsaKey
    rsaKey = RSA.generate(1024)
    privKPG = rsaKey
    pubKPG = rsaKey.publickey()

def phase4():
    global symKeyMPG, nonceMPG
    data = mSock.recv(BUFF)
    data = pickle.loads(data)

    symKeyMPG = decP(data["K"], rsaKey)
    nonceMPG = data["NC"]

    SigM = decK(data["SigM"], symKeyMPG, nonceMPG)
    
    KC = data["KC"]
    NCC = data["NCC"]
    PM = pickle.loads(
        decK(
            pickle.loads(
                decK(
                    data["PM"],
                    symKeyMPG,
                    nonceMPG
                    )
                ),
               decP(KC, rsaKey),
               NCC
            )
        )

    M = {
        "Sid": PM["PI"]["Sid"],
        "PubKC": PM["PI"]["PubKC"],
        "Amount": PM["PI"]["Amount"]
    }
    
    if not ver(pickle.dumps(M), SigM, pubKM):
        print("Invalid signature!")
        return False
    
    if not ver(pickle.dumps(PM["PI"]), PM["SigC"], RSA.importKey(PM["PI"]["PubKC"])):
        print("Invalid signature!")
        return False
    
    return PM["PI"]

def queryDB(q):
    with open("db.json") as file:
        data = json.load(file)
        for record in data:
            if record["CardNumber"] == q["CardN"] and record["Expiry"] == q["CardExp"] and float(record["MoneyRange"][1:]) >= float(q["Amount"]):
                record["MoneyRange"] = str("$" + str(float(record["MoneyRange"][1:]) - float(q["Amount"])))
                return True
    return False

def phase5(data):
    Resp = "ABORT"

    if queryDB(data) and data["CCode"] == CCode:
        Resp = "OK"
    
    PG = {
        "Resp": Resp,
        "Sid": data["Sid"],
        "Amount": data["Amount"],
        "NC": data["NC"]
    }
    SigPG = sign(pickle.dumps(PG), rsaKey)

    data = {
        "Resp": Resp,
        "Sid": PG["Sid"],
        "SigPG": SigPG
    }

    for key in data:
        print("%s:%s"%(key, data[key]))

    data = encK(pickle.dumps(data), symKeyMPG, use_nc=nonceMPG)
    
    mSock.sendall(data)

if __name__ == "__main__":
    generateKeys()
    certificatePG()

    # begin protocol
    initializeServer()
    initializeConnMerchant()
    getPubKM()

    # exchange sub-protocol
    data = phase4()
    phase5(data)