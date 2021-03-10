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
    # server sends B the other aes mode
    print("I. Receiving AES mode from KM...")
    mode_b = str(sock.recv(BUFFER_SIZE), "utf-8")
    print("received message: " + mode_b)
    print("...done!")

    # B sends to the server a confirmation message
    print("II. Confirming AES mode to KM...")
    sock.sendall(bytes("OK", "utf-8"))
    print("...done!")

    # server sends B {k2, vi2} both encrypted with k3
    print("III. Receiving encrypted {K2, IV2} from KM...")
    k2_enc = sock.recv(BUFFER_SIZE)
    iv2_enc = sock.recv(BUFFER_SIZE)
    print("received encrypted K2: " + str(k2_enc))
    print("received encrypted IV2: " + str(iv2_enc))

    k2 = None
    iv2 = None

    k2 = my_aes.cbc_dec(k2_enc, k3, iv3) if mode_b == "CBC" else my_aes.cfb_dec(k2_enc, k3, iv3)
    iv2 = my_aes.cbc_dec(iv2_enc, k3, iv3) if mode_b == "CBC" else my_aes.cfb_dec(iv2_enc, k3, iv3)
    print("decrypted K2: " + str(k2))
    print("decrypted IV2: " + str(iv2))

    # both B and A send an encrypted confirmation message to the server
    print("IV. Sending encrypted confirmation to KM...")
    msg_b = b"OK"
    msg_b_enc = my_aes.cbc_enc(msg_b, k2, iv2) if mode_b == "CBC" else my_aes.cfb_enc(msg_b, k2, iv2)
    print("sending message: " + str(msg_b_enc))
    sock.sendall(msg_b_enc)
    print("...done!")

    # server sends both A and B a message saying they can begin communication
    print("V. Receiving confirmation from KM...")
    confirmation = str(sock.recv(BUFFER_SIZE), "utf-8")
    print(confirmation)
    print("...done!")

    print("-- COMMENCING PHASE 2/2")
    # server sends to B the blocks received from A but now encrypted with {k2,iv2}
    print("I. Receiving encrypted blocks from KM...")
    n_blocks = int(str(sock.recv(BUFFER_SIZE), "utf-8"))
    print("no. of blocks to be received: " + str(n_blocks))
    content_enc = b""
    for i in range(n_blocks):
        print("received block no. " + str(i))
        content_enc += sock.recv(my_aes.BLOCK_SIZE)
    print("...done!")

    # B decrypts and outputs the message, then sends a confirmation message to the server
    print("II. Decrypting every block and sending confirmation message to KM...")
    content_dec = my_aes.cbc_dec(content_enc, k2, iv2) if mode_b == "CBC" else my_aes.cfb_dec(content_enc, k2, iv2)
    print(str(content_dec, "utf-8"))

    sock.sendall(bytes("OK", "utf-8"))
    print("...done!")
