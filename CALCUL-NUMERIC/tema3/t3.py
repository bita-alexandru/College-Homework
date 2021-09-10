import os
import random
import numpy as np
import tkinter as tk
from copy import deepcopy

def read_A(fn): # matrice rara
    n = 0
    A = list()

    with open(fn) as fd:
        n = int(fd.readline())
        fd.readline()

        A = [dict() for _ in range(n)]
        while True:
            line = fd.readline().replace("\n", "").split(",")

            if len(line) < 3: break

            val, i, j = line
            val, i, j = float(val), int(i), int(j)

            if j in A[i]:
                A[i][j] += val
            else:
                A[i][j] = val
        
    return A

def read_B(fn): # matrice tridiagonala
    n = 0
    B = list()
    p, q = 0, 0

    with open(fn) as fd:
        n = int(fd.readline())
        p = int(fd.readline())
        q = int(fd.readline())

        a, b, c = list(), list(), list()

        fd.readline()
        for _ in range(n):
            val = float(fd.readline())
            a.append(val)

        fd.readline()
        for _ in range(n-p):
            val = float(fd.readline())
            b.append(val)

        fd.readline()
        for _ in range(n-p):
            val = float(fd.readline())
            c.append(val)
        
    return p, q, a, b, c

def cmp(calc, real, epsilon = 1e-10):
    if len(calc) != len(real):
        return False

    for i in range(len(calc)):
        if len(calc[i]) != len(real[i]):
            return False
        
        for j in calc[i]:
            if abs(calc[i][j] - real[i][j]) >= epsilon:
                return False
    
    return True

def show(M, name):
    print("[%s]"%name)

    for i in range(len(M)):
        for j in range(len(M)):
            x = "%.2f"%M[i][j]

            for k in range(10):
                if k < len(x):
                    print(x[k], end="")
                else:
                    print(end=" ")
            
            print(end=" ")
            # print("%.2f"%M[i][j], end="\t")
        print()
    print()

def show_dict(M, fn):
    with open(fn, "w") as of:
        for i in range(len(M)):
            of.write("[LINIA %i]\n"%i)

            for k in M[i]:
                of.write("%s: %s\n"%(k, M[i][k]))
            of.write("\n")
        # of.write(str(M))

def to_dict(M):
    D = [dict() for _ in range(len(M))]
    for i in range(len(M)):
        for j in range(len(M)):
            if M[i][j]:
                D[i][j] = M[i][j]
    
    return D

def generate_tridiag(n):
    p = random.randint(1, n-1)
    q = random.randint(1, n-1)

    M = [[0 for _ in range(n)] for _ in range(n)]
    a, b, c = list(), list(), list()

    for i in range(n):
        for j in range(n):
            x = 0
            while x == 0:
                x = random.uniform(-100, 100)

            x = float("%.2f"%x)

            M[i][j] = 0
            if i == j:
                a.append(x)
                M[i][j] = x
            elif j - i == q:
                b.append(x)
                M[i][j] = x
            elif i - j == p:
                c.append(x)
                M[i][j] = x
            
    return M, p, q, a, b, c

def add(A, a, b, c):
    C = deepcopy(A)
    
    for i in range(len(a)):
        if i in C[i]:
            C[i][i] += a[i]
        else:
            C[i][i] = a[i]

    for i in range(len(b)):
        if i+1 in C[i]:
            C[i][i+1] += b[i]
        else:
            C[i][i+1] = b[i]
        
    for i in range(len(c)):
        if i in C[i+1]:
            C[i+1][i] += c[i]
        else:
            C[i+1][i] = c[i]

    return C

def mul(A, a, b, c, p, q):
    C = [dict() for _ in range(len(A))]

    for i in range(len(A)):
        for j in range(len(A)):
            s = 0
            
            for k in A[i]:
                if k == j:
                    s += (A[i][k]*a[k])
                    # s += "[%s]%.2f * %.2f "%("a",A[i][k], a[k])
                
                elif j - k == q:
                    s += (A[i][k]*b[j-q])
                    # s += "[%s]%.2f * %.2f "%("b",A[i][k], b[j-1])
                
                elif k - j == p:
                    s += (A[i][k]*c[j])
                    # s += "[%s]%.2f * %.2f "%("c",A[i][k], c[j])
        
            if s:
                C[i][j] = s

    return C

def mandatory():
    A = read_A("a.txt")
    p, q, a, b, c = read_B("b.txt")

    AplusB_calc = add(A, a, b, c)
    AplusB_real = read_A("aplusb.txt")

    egal = cmp(AplusB_calc, AplusB_real)

    show_dict(AplusB_calc, "output_aplusb.txt")
    os.startfile("aplusb.txt")
    os.startfile("output_aplusb.txt")
    print("Sunt egale? %s!"%egal)

    AoriB_calc = mul(A, a, b, c, p, q)
    AoriB_real = read_A("aorib.txt")

    egal = cmp(AoriB_calc, AoriB_real)

    show_dict(AoriB_calc, "output_aorib.txt")
    os.startfile("aorib.txt")
    os.startfile("output_aorib.txt")
    print("Sunt egale? %s!"%egal)

def bonus():
    n = 7

    A, p1, q1, a1, b1, c1 = generate_tridiag(n)
    B, p2, q2, a2, b2, c2 = generate_tridiag(n)

    show(A, "A p=%i q=%i"%(p1,q1))
    show(B, "B p=%i q=%i"%(p2,q2))

    AB_real = np.dot(A, B)
    show(AB_real, "A*B")

    C = [dict() for _ in range(n)]
    
    for i in range(n):
        for j in range(n):
            s = 0
            
            for k in range(n):
                x = 0

                if i == k:
                    x = a1[i]
                elif k - i == q1:
                    x = b1[i]
                elif i - k == p1:
                    x = c1[k]

                if k == j:
                    s += (x*a2[k])
                    # s += "[%s]%.2f * %.2f "%("a",A[i][k], a[k])
                
                elif j - k == q2:
                    # print("n=%i ; %i"%(n,j-q2))
                    s += (x*b2[j-q2])
                    # s += "[%s]%.2f * %.2f "%("b",A[i][k], b[j-1])
                
                elif k - j == p2:
                    # print("n=%i ; %i"%(n,j))
                    s += (x*c2[j])
                    # s += "[%s]%.2f * %.2f "%("c",A[i][k], c[j])
        
            if s:
                C[i][j] = s


    AB_real = to_dict(AB_real)
    show_dict(C, "output_bonus.txt")
    show_dict(C, "AB.txt")
    os.startfile("output_bonus.txt")
    os.startfile("AB.txt")

    egal = cmp(C, AB_real)
    print("Sunt egale? %s!"%egal)
    
# mandatory()
# bonus()

window = tk.Tk()
f0 = tk.Frame(window)
f0.pack(side=tk.TOP)

bt_normal = tk.Button(f0, text="Solve Mandatory", command=mandatory)
bt_normal.pack(side=tk.TOP)

bt_bonus = tk.Button(f0, text="Solve Bonus", command=bonus)
bt_bonus.pack(side=tk.BOTTOM)

window.mainloop()