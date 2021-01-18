import my_aes
import threading
import socketserver

BUFFER_SIZE = 1024

cnt_users = 0 # number of active nodes this session
phase = 0

km = dict()
mode_a = None
mode_b = None

blocks = b""

class RequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        global cnt_users
        global phase
        global km
        global mode_a
        global mode_b
        global blocks
        global BUFFER_SIZE

        cnt_users += 1
        phase = 0
        blocks = b""

        if cnt_users == 1:
            self.label = "A"
        elif cnt_users == 2:
            self.label = "B"

        print("Node " + self.label + " connected.")

        if cnt_users > 2:
            return

        if self.label == "A":
            while True:
                if cnt_users != 2:
                    continue

                if phase == 0:
                    # KM receives AES mode for A
                    print("IA. Receiving AES mode for A...")
                    mode_a = str(self.request.recv(BUFFER_SIZE), "utf-8")

                    print("AES mode for node A: " + mode_a)
                    print("...done!")

                    mode_b = "CBC" if mode_a == "CFB" else "CFB"

                    phase += 1
                elif phase == 1:
                    # KM sends A two encrypted messages {K1, IV1}
                    print("IIA. Sending encrypted {K1, IV1} to A...")
                    k1_enc = my_aes.cbc_enc(km["k1"], km["k3"], km["iv3"]) if mode_a == "CBC" else my_aes.cfb_enc(km["k1"], km["k3"], km["iv3"])
                    iv1_enc = my_aes.cbc_enc(km["iv1"], km["k3"], km["iv3"]) if mode_a == "CBC" else my_aes.cfb_enc(km["iv1"], km["k3"], km["iv3"])
                   
                    print("encrypted K1: " + str(k1_enc))
                    print("encrypted IV1: " + str(iv1_enc))

                    self.request.sendall(k1_enc)
                    self.request.sendall(iv1_enc)

                    print("...done!")
                    phase += 1
                elif phase == 5:
                    # A sends KM an encrypted confirmation
                    print("IIIA. Receiving encrypted confirmation from A...")
                    conf_a_enc = self.request.recv(BUFFER_SIZE)
                    print("received encrypted message from A: " + str(conf_a_enc))

                    print("...done!")
                    phase += 1
                elif phase == 7:
                    # decrypting message from A and sending confirmation
                    print("IVA. Decrypting message from A and sending confirmation...")
                    if mode_a == "CBC":
                        conf_a_dec = my_aes.cbc_dec(conf_a_enc, km["k1"], km["iv1"])
                    else:
                        conf_a_dec = my_aes.cfb_dec(conf_a_enc, km["k1"], km["iv1"])

                    print("decrypted message from A: " + str(conf_a_dec, "utf-8"))
                    self.request.sendall(bytes("OK", "utf-8"))

                    print("...done!")
                    phase += 1
                elif phase == 9:
                    # receiving {#blocks, block_i, 0<=i<#blocks} from A
                    print("VA. Receiving encrypted file blocks from A...")
                    n_blocks = int(str(self.request.recv(BUFFER_SIZE), "utf-8"))
                    print("no. of blocks: " + str(n_blocks))

                    for i in range(n_blocks):
                        print("receiving block no. " + str(i))
                        block_enc = self.request.recv(my_aes.BLOCK_SIZE)
                        blocks += block_enc

                    print("...done!")
                    phase += 1
                elif phase == 12:
                    # sending confirmation to A
                    print("VIA. Sending confirmation to A and shutting down the connection...")
                    self.request.sendall(bytes("OK", "utf-8"))

                    print("...done!")
                    phase += 1
                elif phase == 13:
                    cnt_users -= 1
                    break
        elif self.label == "B":
            while True:
                if cnt_users != 2:
                    continue

                if phase == 2:
                    # KM sends B the other AES mode
                    print("IB. Sending the other AES mode to B...")
                    print("AES mode for node B: " + mode_b)
                    self.request.sendall(bytes(mode_b, "utf-8"))

                    print("...done!")
                    phase += 1
                elif phase == 3:
                    # B sends KM the confirmation
                    print("IIB. Receiving confirmation from B...")
                    confirmation = str(self.request.recv(BUFFER_SIZE), "utf-8")
                    print(confirmation)

                    print("...done!")
                    phase += 1
                elif phase == 4:
                    # KM sends B encrypted {K2,IV2}
                    print("IIIB. Sending encrypted {K2, IV2} to B...")
                    k2_enc = my_aes.cbc_enc(km["k2"], km["k3"], km["iv3"]) if mode_b == "CBC" else my_aes.cfb_enc(km["k2"], km["k3"], km["iv3"])
                    iv2_enc = my_aes.cbc_enc(km["iv2"], km["k3"], km["iv3"]) if mode_b == "CBC" else my_aes.cfb_enc(km["iv2"], km["k3"], km["iv3"])
                    
                    print("encrypted K2: " + str(k2_enc))
                    print("encrypted IV2: " + str(iv2_enc))

                    self.request.sendall(k2_enc)
                    self.request.sendall(iv2_enc)

                    print("...done!")
                    phase += 1
                elif phase == 6:
                    # B sends KM an encrypted confirmation
                    print("IIIB. Receiving encrypted confirmation from B...")
                    conf_b_enc = self.request.recv(BUFFER_SIZE)

                    print("received encrypted message from B: " + str(conf_b_enc))
                    print("...done!")

                    phase += 1
                elif phase == 8:
                     # decrypting message from B and sending confirmation
                    print("IVB. Decrypting message from B and sending confirmation...")
                    if mode_b == "CBC":
                        conf_b_dec = my_aes.cbc_dec(conf_b_enc, km["k2"], km["iv2"])
                    else:
                        conf_b_dec = my_aes.cfb_dec(conf_b_enc, km["k2"], km["iv2"])

                    print("decrypted message from B: " + str(conf_b_dec, "utf-8"))
                    self.request.sendall(bytes("OK", "utf-8"))

                    print("...done!")
                    phase += 1
                elif phase == 10:
                    # KM decrypts the file blocks from A and encrypts them for B
                    print("VB. Decrypting the file from A and encrypting it for B...")
                    if mode_a == "CBC":
                        blocks_dec = my_aes.cbc_dec(blocks, km["k1"], km["iv1"])
                        blocks_enc = my_aes.cfb_enc(blocks_dec, km["k2"], km["iv2"], True)
                    else:
                        blocks_dec = my_aes.cfb_dec(blocks, km["k1"], km["iv1"])
                        blocks_enc = my_aes.cbc_enc(blocks_dec, km["k2"], km["iv2"], True)
                    
                    blocks = b""
                    n_blocks = len(blocks_enc)
                    print("no. of blocks: " + str(n_blocks))
                    self.request.sendall(bytes(str(n_blocks), "utf-8"))

                    for i in range(n_blocks):
                        print("sending block no. " + str(i))
                        self.request.sendall(blocks_enc[i])

                    print("...done!")
                    phase += 1
                elif phase == 11:
                    # B notifies KM that they decrypted the file
                    print("VIB. Receiving confirmation from B...")
                    confirmation = str(self.request.recv(BUFFER_SIZE), "utf-8")
                    print(confirmation)
                    
                    print("...done!")
                    phase += 1
                elif phase == 13:
                    cnt_users -= 1
                    break

km = {
    "k1": my_aes.get_random_bytes(my_aes.BLOCK_SIZE),
    "k2": my_aes.get_random_bytes(my_aes.BLOCK_SIZE),
    "k3": b"0123456789ABCDEF",
    "iv1": my_aes.get_random_bytes(my_aes.BLOCK_SIZE),
    "iv2": my_aes.get_random_bytes(my_aes.BLOCK_SIZE),
    "iv3": b"ABCDEF0123456789",
}

host, port = "localhost", 9999
server = socketserver.ThreadingTCPServer((host, port), RequestHandler)

print(km)

with server:
    server_thread = threading.Thread(target=server.serve_forever)
    server_thread.daemon = True
    server_thread.start()

    try:
        while True:
            if phase == 13:
                print("Procedure complete.")
                server.shutdown()
                break
    except KeyboardInterrupt:
        print("Server will shut down.")
        server.shutdown()
        exit(-1)