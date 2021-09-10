import socket
import pickle
from Cryptodome.PublicKey import RSA
from Cryptodome.Cipher import AES, PKCS1_OAEP
from Cryptodome.Random import get_random_bytes
from Cryptodome.Hash import SHA256
from Cryptodome.Signature import pkcs1_15

HOST  = "127.0.0.1"
mPORT = 7777

BUFF = 4096

mSock = pgSock = None
rsaKey = None
nonceCM = nonceCPG = None
symKeyCM = symKeyCPG = pubKM = pubKC = privKC = None
pubKPG = None

sid = None

def initializeConnMerchant():
   # Connect to merchant
   global mSock
   mSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
   mSock.connect((HOST, mPORT))

def initializeConnPG():
   return True

def generateKeys():
   global symKeyCM, privKC, pubKC, rsaKey

   # Generate symetric session key
   symKeyCM = get_random_bytes(16)
   
   # Generate RSA keys(private, public)
   rsaKey = RSA.generate(2048)
   privKC = rsaKey
   pubKC = rsaKey.publickey()

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

def decP(m, p, nc):
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

def getPubKM():
   global pubKM
   pubKM = RSA.importKey(open("certificateM.pem").read())

def getPubKPG():
   global pubKPG
   pubKPG = RSA.importKey(open("certificatePG.pem").read())

def phase1():
   # send {PubKC->K, K->PubKM} to Merchant
   global nonceCM
   data = {
      "PubKC": None,
      "K": None,
      "NC": None
   }

   # encrypt the Client's public RSA key using the generated AES session symmetric key
   m, nonceCM = encK(pubKC.export_key(), symKeyCM, True)

   data["PubKC"] = m
   data["NC"] = nonceCM
   
   # encrypt the generated AES session symmetric key using the Merchant's public RSA key
   k = encP(symKeyCM, pubKM)
   data["K"] = k

   data = pickle.dumps(data)

   # print("pubKC=%s\nsymKeyCM=%s"%(pubKC.exportKey(),symKeyCM))

   mSock.sendall(data)

def phase2():
   # receive {Sid->K->PubKC, SigM(Sid)->K->PubKC}
   global sid

   data = mSock.recv(BUFF)
   data = pickle.loads(data)

   # print(data)
   
   sid = decK(data["Sid"], symKeyCM, nonceCM)
   sig = decK(data["SigM"], symKeyCM, nonceCM)

   # print("sid=%s\nsig=%s"%(sid, sig))

   if not ver(sid, sig, pubKM):
      print("Invalid signature!")
      return

def phase3():
   # send {PM->K->PubKM, PO->K->PubKM} to Merchant
   # PM = {PI->K->PubKPG, SigC(PI)->K->PubKPG}
   # PI = CardN, CardExp, CCode, Sid, Amount, PubKC, NC, M
   # PO = OrderDesc, Sid, Amount, NC, SigC(OrderDesc, Sid, Amount, NC)
   global symKeyCPG, nonceCPG
   
   data = {
      "PM": {
         "PI": {
            "CardN": None,
            "CardExp": None,
            "CCode": None,
            "Sid": None,
            "Amount": None,
            "PubKC": None,
            "NC": None,
            "M": None
         }
      },
      "PO": {
         "OrderDesc": None,
         "Sid": None,
         "Amount": None,
         "NC": None,
      },
      "K": None,
      "NC": None
   }

   symKeyCPG = get_random_bytes(16)
   tmp, nonceCPG = encK(b"tmp", symKeyCPG, True)

   data["PM"]["PI"]["CardN"] = "4272498011068334"
   data["PM"]["PI"]["CardExp"] = "03/2024"
   data["PM"]["PI"]["CCode"]  = "1789"
   data["PM"]["PI"]["Sid"]  = sid
   data["PM"]["PI"]["Amount"] = "500"
   data["PM"]["PI"]["PubKC"]  = pubKC.exportKey()
   data["PM"]["PI"]["NC"]  = nonceCM
   data["PM"]["PI"]["M"] = "Merchant 1"

   sigPI = sign(pickle.dumps(data["PM"]["PI"]), rsaKey)
   data["PM"]["SigC"] = sigPI

   data["PM"] = encK(pickle.dumps(data["PM"]), symKeyCPG, use_nc=nonceCPG)
   data["K"] = encP(symKeyCPG, pubKPG)
   data["NC"] = nonceCPG

   # for key in data["PM"]["PI"]:
   #    data["PM"]["PI"][key] = encK(data["PM"]["PI"][key], symKeyCPG)

   data["PO"]["OrderDesc"] = "item"
   data["PO"]["Sid"] = sid
   data["PO"]["Amount"] = "500"
   data["PO"]["NC"] = nonceCM

   sigPO = sign(pickle.dumps(data["PO"]), rsaKey)
   data["PO"]["SigC"] = sigPO

   # print(data["PO"])
   data = encK(pickle.dumps(data), symKeyCM, use_nc=nonceCM)
   # print(data)

   mSock.sendall(data)

def phase6():
   data = mSock.recv(BUFF)
   data = decK(data, symKeyCM, nonceCM)
   data = pickle.loads(data)

   for key in data:
      print("%s:%s"%(key, data[key]))

if __name__ == '__main__':
   # get merchant's and pg's public keys 
   getPubKM()
   getPubKPG()

   generateKeys()

   # begin protocol
   initializeConnMerchant()

   # setup sub-protocol
   phase1()
   phase2()

   # exchange sub-protocol
   phase3()
   phase6()