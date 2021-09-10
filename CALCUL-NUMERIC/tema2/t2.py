import os
import sys
import random
import numpy as np
import tkinter as tk
from tkinter import messagebox
from copy import deepcopy
from textwrap import fill
from scipy.linalg import lu

e = 1e-10
n = 0
A = list()
d = list()
b = list()

def open_input():
    os.startfile("input.txt")

def open_output():
    os.startfile("output.txt")

def read_file():
    global e, n, A, d, b
    try:

        with open("input.txt") as fd:
            e = float(fd.readline())
            n = int(fd.readline())

            A = list()
            d = list()
            for i in range(n):
                line = list()

                j = 0
                for val in fd.readline().replace("\n", "").split(" "):
                    line.append(float(val))

                    if i == j:
                        d.append(float(val))
                    j += 1

                A.append(line)

            b = list()
            for i in range(n):
                b.append(float(fd.readline()))

        l_eps.configure(text="epsilon: " + str(e))
        l_n.configure(text="n: " + str(n))

        tmp = ""
        for i in range(n):
            tmp += "\t"
            for j in range(n):
                tmp = tmp + fill("%.4f"%(A[i][j]), width=15) + "\t"
            tmp += "\n"
        l_A.configure(text="A: " + tmp)

        l_d.configure(text="d: " + str(d))
        l_b.configure(text="b: " + str(b))
    except Exception as e:
        messagebox.showinfo("Exception", str(e))

def read_console():
    global e, n, A, d, b
    try:
        print("e = ", end="")
        e = float(input())
        print("n = ", end="")
        n = int(input())

        A = list()
        d = list()
        for i in range(n):
            line = list()

            j = 0
            print("A[%d] = "%i, end="")
            for val in str(input()).replace("\n", "").split(" "):
                line.append(float(val))

                if i == j:
                    d.append(float(val))
                j += 1

            A.append(line)

        b = list()
        for i in range(n):
            print("b[%d] = "%i, end="")
            b.append(float(input()))
        
        l_eps.configure(text="epsilon: " + str(e))
        l_n.configure(text="n: " + str(n))

        tmp = ""
        for i in range(n):
            tmp += "\t"
            for j in range(n):
                tmp = tmp + fill("%.4f"%(A[i][j]), width=15) + "\t"
            tmp += "\n"
        l_A.configure(text="A: " + tmp)

        l_d.configure(text="d: " + str(d))
        l_b.configure(text="b: " + str(b))
    except Exception as e:
        messagebox.showinfo("Exception", str(e))
        
def read_random():
    global e, n, A, d, b
    try:
        e = float(en_eps.get())
        n = int(en_n.get())
        min = float(en_min.get())
        max = float(en_max.get())
    
        d = list()
        b = list()

        while True:
            A = list()
            for i in range(n):
                row = list()
                for j in range(n):
                    if j >= i:
                        row.append(random.uniform(min, max))

                    else:
                        row.append(A[j][i])
                A.append(row)
            if is_pos_def(n, A):
                break
            break


        for i in range(n):
            d.append(A[i][i])

        for i in range(n):
            b.append(random.uniform(min,max))
        
        l_eps.configure(text="epsilon: " + str(e))
        l_n.configure(text="n: " + str(n))

        tmp = ""
        for i in range(n):
            tmp += "\t"
            for j in range(n):
                tmp = tmp + fill("%.4f"%(A[i][j]), width=15) + "\t"
            tmp += "\n"
        l_A.configure(text="A: " + tmp)

        l_d.configure(text="d: " + str(d))
        l_b.configure(text="b: " + str(b))

    except Exception as e:
        messagebox.showinfo("Exception", str(e))
        return
    
def show(m, A=None):
    with open('output.txt', 'a') as f:
        #print()
        f.write("\n")

        if A is None:
            #print(m)
            f.write(m + "\n")
            return

        if isinstance(A, (list, np.ndarray)):
            if not isinstance(A[0], (list, np.ndarray)):
                #print("%s%s"%(m,A))
                f.write("%s%s\n"%(m,A))
                return
            else:
                #print(m)
                n = len(A)
                for i in range(n):
                    for j in range(n):
                        pass
                        #print(fill("%.4f"%A[i][j], width=15), end=" ")
                    #print()
                
                f.write("%s\n"%m)
                for i in range(n):
                    for j in range(n):
                        f.write(fill("%.4f"%A[i][j], width=15) + " ")
                    f.write("\n")   
                return

        #print("%s%s"%(m,A))
        f.write("%s%s\n"%(m,A))
        
def is_symmetric(n, A):
    for i in range(n):
        for j in range(i):
            if A[i][j] != A[j][i]:
                return False
    return True

def is_pos_def(n, A):
    return is_symmetric(n, A) and np.all(np.linalg.eigvals(A) > 0)

def make_l(n, A):
    for i in range(n):
        for j in range(n):
            if j > i:
                A[i][j] = 0

def make_lpp(n, A, d):
    for p in range(n):
        sum = 0
        els = ""
        for j in range(p):
            sum += (A[p][j]*A[p][j])
            els += "%s^2 + "%A[p][j]
        els = els[:-3]
        
        A[p][p] = np.sqrt(d[p] - sum)
        if e < 0:
            A[p][p] *= -1;
        
        print("L[%i][%i] = sqrt(%s"%(p, p, d[p]), end="")
        if len(els) > 0:
            print(" - (%s)"%els, end="")
        print(") = %s"%A[p][p])
        
        make_lip(n, A, d, p)

def make_lip(n, A, d, p):
    for i in range(p+1, n):
        sum = 0
        els = ""
        for j in range(p):
            sum += (A[i][j]*A[p][j])
            els += ("%s*%s + "%(A[i][j], A[p][j]))
        els = els[:-3]
        
        A[i][p] = (A[i][p] - sum) / A[p][p]
        
        print("L[%i][%i] = "%(i, p), end="")
        if len(els) > 0:
            print("(%s - (%s)) / %s"%(A[i][p], els, A[p][p]), end = "")
        else:
            print("%s / %s"%(A[i][p], A[p][p]), end = "")
        print(" = %s"%A[i][p])

def subst_direct(n, A, b):
    x = list()

    for i in range(0, n):
        sum = 0
        els = ""
        for j in range(i):
            sum += (A[i][j]*x[j])
            els += ("%s*%s + "%(A[i][j], x[j]))
        els = els[:-3]
        
        x.append((b[i] - sum)/A[i][i])
        
        print("y[%i] = "%i, end="")
        if len(els) > 0:
            print("(%s - %s) / %s"%(b[i], sum, A[i][i]), end="")
        else:
            print("%s / %s"%(b[i], A[i][i]), end="")
        print(" = %s"%x[-1])
    
    return x

def subst_inverse(n, A, b):
    x = [0 for _ in range(n)]

    for i in range(n-1, -1, -1):
        sum = 0
        els = ""
        for j in range(i+1, n):
            sum += (A[i][j]*x[j])
            els += ("%s*%s + "%(A[i][j], x[j]))
        els = els[:-3]
        
        x[i] = (b[i] - sum)/A[i][i]
        
        print("x[%i] = "%i, end="")
        if len(els) > 0:
            print("(%s - %s) / %s"%(b[i], sum, A[i][i]), end="")
        else:
            print("%s / %s"%(b[i], A[i][i]), end="")
        print(" = %s"%x[i])

    return x

def make_LLT(n, A, d, b, inv=False):
    if not is_pos_def(n, A):
        show("Matricea nu este pozitiv definita.", A)
        messagebox.showerror("Error","Matrix is not positive definite!")
        # exit(-1)
        return False
    
    make_l(n, A)
    make_lpp(n, A, d)
    
    detL = np.linalg.det(A)
    if not inv:
        show("L: ", A)

    detLT = np.linalg.det(np.transpose(A))
    if not inv:
        show("LT: ", np.transpose(A))

    # print("L*LT: %s"%(np.dot(A, np.transpose(A))))

    detA = detL*detLT
    if not inv:
        show("det(L*LT): ", detA)

    if detA == 0:
        show("Sistem nu poate fi rezolvat")
        return
    
    y = subst_direct(n, A, b)
    if not inv:
        show("y = ", y)

    x = subst_inverse(n, np.transpose(A), y)
    if not inv:
        show("x = ", x)

    norm = np.linalg.norm(np.dot(np.dot(A, np.transpose(A)), x) - np.array(b), ord=2)
    if not inv:
        show("norma = ", norm)
    
    return x
    
def use_lib_lu(A, b):
    p, l, u = lu(A)

    show("p: ", p)
    show("l: ", l)
    show("u: ", u)

    x = np.linalg.solve(A, b)
    show("x: ", x)

def compute_inv(n, A):
    Ainv = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        e = [0 for _ in range(n)]
        e[i] = 1
        e = np.transpose(e)

        x = make_LLT(n, deepcopy(A), d, e, True)
        if x == False:
            return

        for j in range(n):
            Ainv[j][i] = x[j]

    show("A_inv: ", Ainv)

    Abib = np.linalg.inv(A)
    norm = np.linalg.norm(Ainv - Abib, ord=2)
    show("norma = ", norm)

def solve():
    global e, n, A, d, b

    if n <= 0 or len(A) != n or len(b) != n or len(d) != n or not isinstance(e, float):
        messagebox.showerror("Error","Incorrect input. Try again!")
        return
    
    open("output.txt", "w").close()

    if not make_LLT(n, deepcopy(A), d, b):
        return
    #use_lib_lu(deepcopy(A), b)

    #compute_inv(n, deepcopy(A))


if __name__ == "__main__":
    window = tk.Tk()

    f00 = tk.Frame(window)
    f00.pack(side=tk.TOP, anchor=tk.W)

    f1 = tk.Frame(f00)
    f1.pack(side=tk.LEFT, anchor=tk.N)

    bt_console = tk.Button(f1, text="Console Input", command=read_console)
    bt_console.pack(side=tk.TOP)

    f20 = tk.Frame(f00)
    f20.pack(side=tk.LEFT, anchor=tk.N)
    bt_edit = tk.Button(f20, text="Edit File", command=open_input)
    bt_edit.pack(side=tk.TOP)
    bt_file = tk.Button(f20, text="File Input", command=read_file)
    bt_file.pack(side=tk.BOTTOM)

    f3 = tk.Frame(f00)
    f3.pack(side=tk.RIGHT, anchor=tk.N)
    f31 = tk.Frame(f3)
    f31.pack(side=tk.TOP)
    lb_eps = tk.Label(f31, text="epsilon:")
    lb_eps.pack(side=tk.LEFT, anchor=tk.W)
    en_eps = tk.Entry(f31)
    en_eps.pack(side=tk.RIGHT)
    f32 = tk.Frame(f3)
    f32.pack(side=tk.TOP)
    lb_n = tk.Label(f32, text="n:")
    lb_n.pack(side=tk.LEFT, anchor=tk.W)
    en_n = tk.Entry(f32)
    en_n.pack(side=tk.RIGHT)
    f33 = tk.Frame(f3)
    f33.pack(side=tk.TOP)
    lb_min = tk.Label(f33, text="min:")
    lb_min.pack(side=tk.LEFT, anchor=tk.W)
    en_min = tk.Entry(f33)
    en_min.pack(side=tk.RIGHT)
    f34 = tk.Frame(f3)
    f34.pack(side=tk.TOP)
    lb_max = tk.Label(f34, text="max:")
    lb_max.pack(side=tk.LEFT, anchor=tk.W)
    en_max = tk.Entry(f34)
    en_max.pack(side=tk.RIGHT)
    bt_random = tk.Button(f3, text="Random Input", command=read_random)
    bt_random.pack(side=tk.BOTTOM)

    f01 = tk.Frame(window)
    f01.pack(side=tk.BOTTOM, anchor=tk.W)

    f010 = tk.Frame(f01)
    f010.pack(side=tk.LEFT, anchor=tk.W)
    f0101 = tk.Frame(f010)
    f0101.pack(side=tk.TOP, anchor=tk.W)
    l_eps = tk.Label(f0101, text="epsilon:")
    l_eps.pack(side=tk.LEFT, anchor=tk.W)

    f0102 = tk.Frame(f010)
    f0102.pack(side=tk.TOP, anchor=tk.W)
    l_n = tk.Label(f0102, text="n:")
    l_n.pack(side=tk.LEFT, anchor=tk.W)

    f0103 = tk.Frame(f010)
    f0103.pack(side=tk.TOP, anchor=tk.W)
    l_A = tk.Label(f0103, text="A:")
    l_A.pack(side=tk.LEFT, anchor=tk.W)

    f0104 = tk.Frame(f010)
    f0104.pack(side=tk.TOP, anchor=tk.W)
    l_d = tk.Label(f0104, text="d:")
    l_d.pack(side=tk.LEFT, anchor=tk.W)

    f0105 = tk.Frame(f010)
    f0105.pack(side=tk.BOTTOM, anchor=tk.W)
    l_b = tk.Label(f0105, text="b:")
    l_b.pack(side=tk.LEFT, anchor=tk.W)

    f011 = tk.Frame(f01)
    f011.pack(side=tk.RIGHT, anchor=tk.W)

    f0110 = tk.Frame(f011)
    f0110.pack(side=tk.TOP, anchor=tk.W)
    bt_solve = tk.Button(f0110, text="Solve", command=solve)
    bt_solve.pack(side=tk.LEFT)

    f0111 = tk.Frame(f011)
    f0111.pack(side=tk.BOTTOM, anchor=tk.W)
    bt_output = tk.Button(f0111, text="View Output", command=open_output)
    bt_output.pack(side=tk.LEFT)

    window.mainloop()
