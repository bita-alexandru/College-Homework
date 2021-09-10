import os
import tkinter as tk
from tkinter import messagebox
from math import sqrt
from numpy.linalg import solve
from random import uniform, randint

def read_a(fn):
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
        for _ in range(n - p):
            val = float(fd.readline())
            b.append(val)

        fd.readline()
        for _ in range(n - q):
            val = float(fd.readline())
            c.append(val)

    return p, q, a, b, c

def read_f(fn):
    with open(fn) as fd:
        n = int(fd.readline())

        f = list()

        fd.readline()
        for _ in range(n):
            val = float(fd.readline())
            f.append(val)

    return f

def check_diagonal(a):
    for value in a:
        if value == 0:
            return False

    return True

def compute_norm(v):
    v = [i*i for i in v]
    return sqrt(sum(v))

def compute_solution(p, q, a, b, c, f, epsilon):
    n = len(a)
    x = [0 for _ in range(n)]

    kmax = 10000
    for k in range(kmax):
        s = 0
        for i in range(n):
            old = x[i]

            ai = a[i]
            bi = 0
            ci = 0

            if i >= p:
                # print("n=%i i=%i q=%i len=%i"%(n,i,q,len(c)))
                ci = c[i-p]
            if i < n-q:
                # print("n=%i i=%i p=%i len=%i"%(n,i,p,len(b)))
                bi = b[i]
            
            new = f[i]
            if i >= p:
                new -= (ci*x[i-p])
            if i < n-q:
                new -= (bi*x[i+q])

            new /= ai
            x[i] = new
            s += ((new - old)**2)
        
        delta = sqrt(s)

        if delta < epsilon:
            break

        if delta > 1e8:
            break
    
    if delta < epsilon:
        return x
    
    return None

def compute_error(x, p, q, a, b, c, f):
    errmax = -1e10
    n = len(a)

    # with open("max_norm.txt", "wt") as fd:   
    for i in range(n):
        erri = x[i]*a[i]
        # fd.write("LINIA %i\n"%i)
        # fd.write("(%f * %f)"%(x[i],a[i]))

        if i >= p:
            erri += (c[i-p]*x[i-p])
            # fd.write(" + (%f * %f)"%(x[i-p],c[i-p]))
        if i < n-q:
            erri += (b[i]*x[i+q])
            # fd.write(" + (%f * %f)"%(x[i+q], b[i]))

        erri -= f[i]
        # fd.write(" - %f"%f[i])
        # fd.write("\n\n")
        errmax = max(errmax, abs(erri))

    return errmax

def print_solution(fn, x_calc, x_real, err):
    with open(fn, "wt") as fd:
        if err is None:
            fd.write("divergence\n")
            
            for i in range(len(x_real)):
                fd.write("x[%i] (real) %s\n"%(i, x_real[i]))
            
            return

        fd.write("max norm = %s\n"%err)

        for i in range(len(x_calc)):
            fd.write("x[%i] (calculated) %s vs %s (real)\n"%(i, x_calc[i], x_real[i]))

def generate_tridiag(n, lim):
    p = randint(1, n-1)
    q = randint(1, n-1)

    M = [[0 for _ in range(n)] for _ in range(n)]
    a, b, c = list(), list(), list()
    f = list()

    for i in range(n):
        for j in range(n):
            x = 0
            while x == 0:
                x = uniform(-lim, lim)

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
        
        x = uniform(-lim, lim)
        x = float("%.2f"%x)
        f.append(x)
            
    return M, p, q, a, b, c, f

def mandatory():
    solutions = {
        1: lambda n: [1/1 for _ in range(n)],
        2: lambda n: [1/3 for _ in range(n)],
        3: lambda n: [2*(i+1)/5 for i in range(n)],
        4: lambda n: [2000/(i+1) for i in range(n)],
        5: lambda n: [2/1 for _ in range(n)]
    }

    for i in range(1, 6):
        fn_a = "a%i.txt"%i
        fn_f = "f%i.txt"%i

        p, q, a, c, b = read_a(fn_a)
        f = read_f(fn_f)

        epsilon = 10**(-p)

        if not check_diagonal(a):
            messagebox.showerror(title="Error", message="Main diagonal values cannot be 0.\nFile: %s"%fn_a)
            return

        x = compute_solution(p, q, a, b, c, f, epsilon)
        real = solutions[i](len(a))
        
        if x is None:
            err = None
        else:
            err = compute_error(x, p, q, a, b, c, f)
        
        fn_sol = "sol%i.txt"%i
        print_solution(fn_sol, x, real, err)

        os.startfile(fn_a)
        os.startfile(fn_f)
        os.startfile(fn_sol)

def bonus():
    n = 0
    try:
        n = int(sb_size.get())
        if n < 2:
            raise "size can't be lower than 2"
    except Exception as e:
        messagebox.showerror(title="Error", message="Invalid size input.")
        return

    lim = sqrt(n)
    M, p, q, a, b, c, f = generate_tridiag(n, lim)
    epsilon = 10**(-p)

    with open("_a.txt", "wt") as fd:
        if pretty_print.get():
            for i in range(len(a)):
                for j in range(len(a)):
                    fd.write("%.2f "%M[i][j])
                fd.write("\n")
        else:
            for i in range(len(a)):
                fd.write("a[%i]: %.2f\n"%(i, a[i]))
            fd.write("\n")
            for i in range(len(b)):
                fd.write("b[%i]: %.2f\n"%(i, b[i]))
            fd.write("\n")
            for i in range(len(c)):
                fd.write("c[%i]: %.2f\n"%(i, c[i]))
    os.startfile("_a.txt")
    
    with open("_f.txt", "wt") as fd:
        for i in range(len(a)):
            fd.write("f[%i]: %s\n"%(i, f[i]))
    os.startfile("_f.txt")

    x = compute_solution(p, q, a, b, c, f, epsilon)
    real = solve(M, f)

    if x is None:
        err = None
    else:
        err = compute_error(x, p, q, a, b, c, f)

    print_solution("_sol.txt", x, real, err)
    os.startfile("_sol.txt")

# mandatory()
# bonus()


window = tk.Tk()

f1 = tk.Frame(window)
f1.pack(side=tk.LEFT)

bt_mandatory = tk.Button(f1, text="Solve Mandatory", command=mandatory)
bt_mandatory.pack(side=tk.TOP)

f2 = tk.Frame(window)
f2.pack(side=tk.RIGHT)

f21 = tk.Frame(f2)
f21.pack(side=tk.TOP)

lb_size = tk.Label(f21, text="size: ")
lb_size.pack(side=tk.LEFT)
sb_size = tk.Spinbox(f21, from_=2, to=100)
sb_size.pack(side=tk.RIGHT)

pretty_print = tk.BooleanVar()
cb_pretty = tk.Checkbutton(f2, text="Pretty print generated matrix", variable=pretty_print, onvalue=True, offvalue=False)
cb_pretty.pack(side=tk.TOP)

bt_bonus = tk.Button(f2, text="Solve Bonus", command=bonus)
bt_bonus.pack(side=tk.BOTTOM)

window.mainloop()