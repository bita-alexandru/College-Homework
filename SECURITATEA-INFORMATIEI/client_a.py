import sys
import socket
import my_aes
import os.path

BUFFER_SIZE = 1024
ip, port = "localhost", 9999

k3 = b"0123456789ABCDEF"
iv3 = b"ABCDEF0123456789"

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

with sock:
    sock.connect((ip, port))

    print("-- COMMENCING PHASE 1/2")
    # send the desired aes mode (cbc/cfb) for A
    print("I. Informing KM of you AES mode...")
    print("aes-mode (cbc/cfb): ", end="")
    mode_a = str(input()).upper()
    while mode_a not in ["CBC", "CFB"]:
        print("aes-mode (cbc/cfb): ", end="")
        mode_a = str(input()).upper()
    sock.sendall(bytes(mode_a, "utf-8"))
    print("...done!")

    # server sends A {k1, iv1} both encrypted with k3
    print("II. Receiving encrypted {K1, IV1} from KM...")
    k1_enc = sock.recv(BUFFER_SIZE)
    iv1_enc = sock.recv(BUFFER_SIZE)
    print("received encrypted K1: " + str(k1_enc))
    print("received encrypted IV1: " + str(iv1_enc))

    k1 = None
    iv1 = None

    k1 = my_aes.cbc_dec(k1_enc, k3, iv3) if mode_a == "CBC" else my_aes.cfb_dec(k1_enc, k3, iv3)
    iv1 = my_aes.cbc_dec(iv1_enc, k3, iv3) if mode_a == "CBC" else my_aes.cfb_dec(iv1_enc, k3, iv3)
    print("decrypted K1: " + str(k1))
    print("decrypted IV1: " + str(iv1))
    print("...done!")
    
    # both A and B send an encrypted confirmation message to the server
    print("IV. Sending encrypted confirmation to KM...")
    msg_a = b"OK"
    msg_a_enc = my_aes.cbc_enc(msg_a, k1, iv1) if mode_a == "CBC" else my_aes.cfb_enc(msg_a, k1, iv1)
    print("sending message: " + str(msg_a_enc))
    sock.sendall(msg_a_enc)
    print("...done!")

    # server sends both A and B a message saying they can begin communication
    print("V. Receiving confirmation from KM...")
    confirmation = str(sock.recv(BUFFER_SIZE), "utf-8")
    print(confirmation)
    print("...done!")

    print("-- COMMENCING PHASE 2/2")
    # A encrypts a file and sends to the server {#blocks, block_i, 0<=i<=#blocks}
    print("I. Encrypting file and sending every block of it to KM...")
    print("file to encrypt: ", end="")
    filename = str(input())
    while not os.path.isfile(filename):
        print("file to encrypt: ", end="")
        filename = str(input())
    
    content = ""
    with open(filename) as fd:
        content = bytes(fd.read(), "utf-8")
    content_enc = my_aes.cbc_enc(content, k1, iv1, True) if mode_a == "CBC" else my_aes.cfb_enc(content, k1, iv1, True)

    n_blocks = len(content_enc)
    print("no. of blocks to be sent: " + str(n_blocks))
    sock.sendall(bytes(str(n_blocks), "utf-8"))
    
    for i in range(n_blocks):
        print("sending block no. " + str(i))
        sock.sendall(content_enc[i])
    print("...done!")

    # server sends A a confirmation that B decrypted the file
    print("II. Receiving confirmation from KM that B decrypted the entire file...")
    confirmation = str(sock.recv(BUFFER_SIZE), "utf-8")
    print(confirmation)
    print("...done!")
    