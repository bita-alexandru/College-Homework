from Cryptodome.Cipher import AES
from Cryptodome.Util.Padding import pad
from Cryptodome.Util.Padding import unpad
from Cryptodome.Random import get_random_bytes

BLOCK_SIZE = 16

def byte_xor(x, y):
    return bytes([a ^ b for a, b in zip(x, y)])

def cbc_enc(plaintext, key, iv, ret_blocks = False):
    # length of plain text does not divide 16 -> add padding (null bytes at the end)
    plaintext = pad(plaintext, BLOCK_SIZE)
    cipher_texts = [iv]

    for i in range(int(len(plaintext)/BLOCK_SIZE)):
        # processing plain text block by block
        block = plaintext[i*BLOCK_SIZE : i*BLOCK_SIZE + BLOCK_SIZE]

        cipher = AES.new(key, AES.MODE_CBC, iv)

        # applying encrpytion function on the result of `current block` XOR 'previous ciphertext'
        ciphertext = cipher.encrypt(byte_xor(block, cipher_texts[-1]))

        cipher_texts.append(ciphertext)
    
    # remove C_0(iv) from the cipher texts
    cipher_texts.pop(0)

    if ret_blocks:
        return cipher_texts
    
    return b"".join(cipher_texts)

def cbc_dec(ciphertext, key, iv):
    plain_texts = []
    cipher_texts = [iv]
    
    for i in range(int(len(ciphertext)/BLOCK_SIZE)):
        # processing ciphertext block by block
        block = ciphertext[i*BLOCK_SIZE : i*BLOCK_SIZE + BLOCK_SIZE]
        cipher = AES.new(key, AES.MODE_CBC, iv)

        # applying decryption function on the current ciphertext block
        # and xor'ing the decrypted text with the previous cipher
        plaintext = byte_xor(cipher.decrypt(block), cipher_texts[-1])

        cipher_texts.append(block)
        plain_texts.append(plaintext)
    
    return unpad(b"".join(plain_texts), BLOCK_SIZE)

def cfb_enc(plaintext, key, iv, ret_blocks = False):
    # length of plain text does not divide 16 -> add padding (null bytes at the end)
    plaintext = pad(plaintext, BLOCK_SIZE)
    cipher_texts = [iv]

    for i in range(int(len(plaintext)/BLOCK_SIZE)):
        # processing plain text block by block
        block = plaintext[i*BLOCK_SIZE : i*BLOCK_SIZE + BLOCK_SIZE]

        cipher = AES.new(key, AES.MODE_CFB, iv, segment_size=8*BLOCK_SIZE)

        # applying encrpytion function on the previous ciphertext and 
        # xor'ing the encrypted text with the current block of plain text
        ciphertext = byte_xor(cipher.encrypt(cipher_texts[-1]), block)

        cipher_texts.append(ciphertext)
    
    # remove C_0(iv) from the cipher texts
    cipher_texts.pop(0)
    
    if ret_blocks:
        return cipher_texts

    return b"".join(cipher_texts)

def cfb_dec(ciphertext, key, iv):
    plain_texts = []
    cipher_texts = [iv]
    
    for i in range(int(len(ciphertext)/BLOCK_SIZE)):
        # processing ciphertext block by block
        block = ciphertext[i*BLOCK_SIZE : i*BLOCK_SIZE + BLOCK_SIZE]
        cipher = AES.new(key, AES.MODE_CFB, iv, segment_size=8*BLOCK_SIZE)

        # applying decryption function on the previous ciphertext block
        # and xor'ing the decrypted text with the current cipher
        plaintext = byte_xor(cipher.encrypt(cipher_texts[-1]), block)

        cipher_texts.append(block)
        plain_texts.append(plaintext)
    
    return unpad(b"".join(plain_texts), BLOCK_SIZE)
