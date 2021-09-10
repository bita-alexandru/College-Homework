import os
import math
import time
import numpy as np
import tkinter as tk
from math import sqrt
from numpy import array
from copy import deepcopy
from random import uniform
from tkinter import messagebox
from scipy.linalg import pinv, norm as _norm
from scipy.linalg import lu, svd, solve as scipysolve

epsilon = 1e-16
kmax = 1000

def open_input():
    open("input.txt", "at").close()
    os.startfile("input.txt")

def open_output():
    open("output.txt", "at").close()
    os.startfile("output.txt")

def generate_input():
    try:
        p = int(sb_rows.get())
        n = int(sb_cols.get())
    except Exception as e:
        messagebox.showerror(title="Error", message="Invalid input: %s"%e)
        return

    with open("input.txt", "wt") as fd:
        fd.write("%i %i\n\n"%(p, n))

        if p == n:
            M = [[0 for _ in range(n)] for _ in range(n)]

            while True:
                for i in range(n):
                    for j in range(i+1):
                        val = uniform(-100, 100)
                        M[i][j] = M[j][i] = val

                if np.all(np.linalg.eigvals(M) > 0):
                    break
            
            for i in range(n):
                for j in range(n):
                    fd.write("%.2f "%M[i][j])
                fd.write("\n")
        else:
            for i in range(p):
                for j in range(n):
                    val = uniform(-100, 100)
                    fd.write("%.2f "%val)
                fd.write("\n")
    
    if messagebox.askyesno(title="Success", message="Input generated successfully.\nCheck the input file?"):
        open_input()

def read_A(fn):
    with open(fn, "rt") as f:
        p, n = f.readline().split(" ")
        p = int(p)
        n = int(n)

        f.readline()

        A = list()
        for i in range(p):
            line = f.readline().split(" ")

            if p == n:
                for j in range(i+1):
                    A.append(float(line[j]))
            elif p > n:
                row = list()
                for j in range(n):
                    row.append(float(line[j]))
                A.append(row)
            
    return p, n, A

def print_matrix(A):
    for i in range(len(A)):
        for j in range(len(A[0])):
            print("%.5f "%A[i][j], end="")
        print()

def get_pq(n, A):
    x = -1e10
    p = -1
    q = -1

    for i in range(1, n):
        for j in range(i):
            val = abs(A[get_i(i, j, n)])
            if x < val:
                x = val
                p = i
                q = j
    
    return p, q

def get_i(row, col, n):
    # if row < col:
    #     row, col = col, row
    
    # i = col*(n-1) - col*(col-1) // 2 + row
    if col > row:
        col, row = row, col

    cnt = 0
    for i in range(row):
        for j in range(i+1):
            cnt += 1
    
    for j in range(col):
        cnt += 1

    return cnt

def get_cst(app, aqq, apq):
    alpha = (app - aqq) / (2*apq)
    sign = 1 if alpha >= 0 else -1

    t = -alpha + sign*sqrt(alpha**2 + 1)

    c = 1/sqrt(1 + t**2)
    s = t*c

    return c, s, t

def get_init(n, A):
    init = [[0 for _ in range(n)] for _ in range(n)]
    
    cnt = 0
    for i in range(n):
        for j in range(i+1):
            init[i][j] = init[j][i] = A[cnt]
            cnt += 1
    
    return init

def dot(A, B):
    n = len(A)
    m = len(B[0])
    M = [[0 for _ in range(m)] for _ in range(n)]

    for i in range(n):
        for j in range(m):
            s = 0
            for k in range(n):
                s += (A[i][k] * B[k][j])
            M[i][j] = s
    
    return M

def norm(A, B, order=2):
    n = len(A)
    m = len(A[0])
    zmax = -1e15

    for j in range(m):
        z = 0
        for i in range(n):
            if order == 2:
                z += (A[i][j] - B[i][j])**2
            elif order == 1:
                z += abs(A[i][j] - B[i][j])
        
        if zmax < z:
            zmax = z
    
    if order == 2:
        zmax = sqrt(zmax)

    return zmax

def trans(A):
    n = len(A)
    m = len(A[0])
    M = [[0 for _ in range(n)] for _ in range(m)]
    
    for i in range(n):
        for j in range(m):
            M[j][i] = A[i][j]

    return M

def rang(A):
    sigpos = list()
    for val in A:
        if val > 0:
            sigpos.append(val)
    
    return sigpos

def cond(A):
    sigmin = 1e15
    sigmax = -1e15

    for val in A:
        if val > sigmax:
            sigmax = val
        if val < sigmin and val > 0:
            sigmin = val
    
    return sigmax/sigmin

def make_diag(n, A):
    d = list()
    for i in range(n):
        d.append(A[i][i])

    return d

def make_l(n, L, d):
    for i in range(n):
        for j in range(n):
            if j > i:
                L[i][j] = 0
                
    make_lpp(n, L, d)

def make_lpp(n, L, d):
    for p in range(n):
        sum = 0
        for j in range(p):
            sum += (L[p][j]*L[p][j])
        
        L[p][p] = sqrt(d[p] - sum)
        make_lip(n, L, d, p)

def make_lip(n, L, d, p):
    for i in range(p+1, n):
        sum = 0
        for j in range(p):
            sum += (L[i][j]*L[p][j])
        
        L[i][p] = (L[i][p] - sum) / L[p][p]

def compute_eigen(n, A):
    U = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        U[i][i] = 1

    p, q = get_pq(n, A)

    app = A[get_i(p, p, n)]
    aqq = A[get_i(q, q, n)]
    apq = A[get_i(p, q, n)]
    apqprev = apq

    if abs(apq) < epsilon:
        output("out of %s max iterations, eigenvalues and eigenvectors were found at iteration number:"%kmax, 0, "var")
        return U, A

    c, s, t = get_cst(app, aqq, apq)

    for k in range(kmax):
        B = deepcopy(A)

        for j in range(n):
            if j in (p, q):
                continue
            B[get_i(p, j, n)] = c*A[get_i(p, j, n)] + s*A[get_i(q, j, n)]
        
        for j in range(n):
            if j in (p, q):
                continue
            B[get_i(q, j, n)] = -s*A[get_i(p, j, n)] + c*A[get_i(q, j, n)]

        B[get_i(p, p, n)] = c*c*app + s*s*aqq + 2*c*s*apq
        B[get_i(q, q, n)] = s*s*app + c*c*aqq - 2*c*s*apq
        B[get_i(p, q, n)] = (c*c - s*s)*apq + c*s*(aqq - app)
        
        for i in range(n):
            uip = U[i][p]
            U[i][p] = c*uip + s*U[i][q]
            U[i][q] = -s*uip + c*U[i][q]

        A = deepcopy(B)
        
        p, q = get_pq(n, A)

        app = A[get_i(p, p, n)]
        aqq = A[get_i(q, q, n)]
        apq = A[get_i(p, q, n)]

        if abs(apq) < epsilon or abs(apq-apqprev) < epsilon:
            output("out of %s max iterations, eigenvalues and eigenvectors were found at iteration number:"%kmax, k+1, "var")
            return U, A

        apqprev = apq
        c, s, t = get_cst(app, aqq, apq)

    output("out of %s max iterations, eigenvalues and eigenvectors were found at iteration number:"%kmax, kmax, "var")
    return U, A

def compute_ak(A):
    Aprev = deepcopy(A)
    n = len(A)

    L = deepcopy(Aprev)
    d = make_diag(n, A)
    make_l(n, L, d)

    for k in range(kmax):
        Anext = dot(trans(L), L)

        if norm(Aprev, Anext) < epsilon:
            output("out of %s max iterations, A(k)-string was found at iteration number:"%kmax, k+1, "var")
            return Anext

        Aprev = deepcopy(Anext)
        L = deepcopy(Aprev)
        d = make_diag(n, Aprev)
        make_l(n, L, d)

    output("out of %s max iterations, A(k)-string was found at iteration number:"%kmax, kmax, "var")
    return Anext

def compute_svd(n, p, A):
    U, S, V = svd(A)
    
    output("singular values:", S, "arr")

    r = rang(S)
    output("rank:", len(r), "var")
    output("condition number:", cond(S), "var")

    Si = [[0 for _ in range(p)] for _ in range(n)]
    for i in range(len(r)):
        Si[i][i] = 1/r[i]
    
    Ai = dot(dot(trans(V), Si), trans(U))
    output("AI:", Ai, "mat")
    
    At = trans(A)
    AtA = dot(At, A)
    nAtA = len(AtA)
    I = [[0 for _ in range(nAtA)] for _ in range(nAtA)]
    for i in range(nAtA):
        I[i][i] = 1

    AtAinv = scipysolve(AtA, I)

    Aj = dot(AtAinv, At)
    output("AJ:", Aj, "mat")

    norma = norm(Ai, Aj, order=1)
    output("||AI - AJ||:", norma, "var")

def output(tag, v, id):
    with open("output.txt", "at") as fd:
        fd.write("%s\n"%tag)

        if id == "var":
            if abs(v) < epsilon:
                j = 0
            fd.write("%s\n"%v)
        elif id == "arr":
            for i in v:
                if abs(i) < epsilon:
                        i = 0
                fd.write("%s "%i)
            fd.write("\n")
        elif id == "mat":
            for i in v:
                for j in i:
                    if abs(j) < epsilon:
                        j = 0
                    fd.write("%s "%j)
                fd.write("\n")
        
        fd.write("\n")

def solve():
    global kmax
    open("output.txt", "wt").close()

    try:
        kmax = int(sb_iter.get())
        p, n, A = read_A("input.txt")
        
        timer = time.perf_counter()

        if p == n:
            U, Lambda = compute_eigen(n, deepcopy(A))
            Lambda = get_init(n, Lambda)
            output("eigenvectors:", U, "mat")
            output("eigenvalues:", reversed(make_diag(n, Lambda)), "arr")
            
            Ainit = get_init(n, A)
            AinitU = dot(Ainit, U)
            ULambda = dot(U, Lambda)

            norma = norm(AinitU, ULambda)
            output("||AU - ULambda||:", norma, "var")

            Ak = compute_ak(Ainit)
            output("A(k)-string:", Ak, "mat")
        elif p > n:
            compute_svd(n, p, A)

        timer = time.perf_counter() - timer

        output("time to solve (seconds):", timer, "var")
    except Exception as e:
        messagebox.showerror(title="Error", message="Invalid input: %s"%e)
        return
    
    if messagebox.askyesno(title="Success", message="Tasks solved successfully.\nTime elapsed: %.3f seconds.\nCheck the output file?"%timer):
        open_output()


window = tk.Tk()

f1 = tk.Frame(window)
f1.pack(side=tk.LEFT)

f11 = tk.Frame(f1)
f11.pack(side=tk.TOP, anchor=tk.W)
lb_rows = tk.Label(f11, text="rows(p):")
lb_rows.pack(side=tk.LEFT)
sb_rows = tk.Spinbox(f11, from_=2, to=10)
sb_rows.pack(side=tk.RIGHT)

f12 = tk.Frame(f1)
f12.pack(side=tk.TOP, anchor=tk.W)
lb_cols = tk.Label(f12, text="columns(n):")
lb_cols.pack(side=tk.LEFT)
sb_cols = tk.Spinbox(f12, from_=2, to=10)
sb_cols.pack(side=tk.RIGHT)

bt_generate = tk.Button(f1, text="Generate Random Input", command=generate_input)
bt_generate.pack(side=tk.TOP)
bt_input = tk.Button(f1, text="Open Input File", command=open_input)
bt_input.pack(side=tk.BOTTOM)

f2 = tk.Frame(window)
f2.pack(side=tk.RIGHT)

f21 = tk.Frame(f2)
f21.pack(side=tk.TOP, anchor=tk.W)
lb_iter = tk.Label(f21, text="max iterations:")
lb_iter.pack(side=tk.LEFT)
sb_iter = tk.Spinbox(f21, from_=1000, to=1000000, inc=1000)
sb_iter.pack(side=tk.RIGHT)

bt_solve = tk.Button(f2, text="Solve", command=solve)
bt_solve.pack(side=tk.TOP)

bt_output = tk.Button(f2, text="Open Output File", command=open_output)
bt_output.pack(side=tk.BOTTOM)

window.mainloop()