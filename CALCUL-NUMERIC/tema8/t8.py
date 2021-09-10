import os
import math
import time
import tkinter as tk
from matplotlib import pyplot as plt
from random import uniform
from tkinter import messagebox
from math import sin, cos, tan, sqrt, e

epsilon = 1e-15
kmax = 1000

def open_output():
    open("output.txt", "at").close()
    os.startfile("output.txt")

def switch_random():
    if v_random.get():
        en_min.config(state=tk.NORMAL)
        en_max.config(state=tk.NORMAL)
        en_estim.config(state=tk.DISABLED)
    else:
        en_min.config(state=tk.DISABLED)
        en_max.config(state=tk.DISABLED)
        en_estim.config(state=tk.NORMAL)

def output(tag, v=None):
    with open("output.txt", "at") as fd:
        if v is None:
            fd.write("%s\n"%tag)
        else:
            fd.write("%s: %s\n"%(tag, v))

def show_graphic():
    try:
        func = str(en_func.get())
        ratio = 0.001

        xs = list()
        ys = list()
        xmin = float(en_xmin.get())
        xmax = float(en_xmax.get())

        i = xmin
        while i < xmax:
            xs.append(i)
            ys.append(f(func, 1, i))
            i += ratio

        plt.plot(xs, ys, label=func)
        plt.legend()
        plt.show()
    except Exception as e:
        messagebox.showerror(title="Error", message="Invalid input: %s"%e)
        return

def f(func, coefficient, param):
    x = param
    y = coefficient * eval(func)

    return y

def compute_G1(func, h, x):
    num = f(func, 3, x) - f(func, 4, x-h) + f(func, 1, x-2*h)
    denom = 2*h

    return num/denom

def compute_G2(func, h, x):
    num = -f(func, 1, x+2*h) + f(func, 8, x+h) - f(func, 8, x-h) + f(func, 1, x-2*h)
    denom = 12*h

    return num/denom

def compute_F2(func, h, x):
    num = -f(func, 1, x+2*h) + f(func, 16, x+h) - f(func, 30, x) + f(func, 16, x-h) - f(func, 1, x-2*h)
    denom = 12*h**2

    return num/denom

def compute_sol(func, h, x0, g):
    output("x0", x0)
    x = x0

    k = 1
    while k < kmax:
        gx = g(func, h, x)
        denom = g(func, h, x+gx) - gx
        
        if abs(denom) <= epsilon:
            return k, x
        
        z = x + (round(gx)**2 / denom)
        gz = g(func, h, z)

        dx = (gx * round(gz - gx)) / denom

        x -= dx

        if abs(dx) < epsilon or abs(dx) >= 1e8:
            break
            
        k += 1
    
    if dx < epsilon:
        return k, x
    
    return -1, -1

def solve():
    # 1/3*x**3 - 2*x**2 + 2*x + 3
    # 3.41421356,
    # x**2 + sin(x)
    # -0.4501836112948,
    # x**4 - 6*x**3 + 13*x**2 - 12*x + 4
    # {1, 2}

    open("output.txt", "wt").close()

    global kmax

    h = 1e-6
    G = {
        "G1": compute_G1,
        "G2": compute_G2
    }

    try:
        if v_random.get():
            xmin = float(en_min.get())
            xmax = float(en_max.get())
            x0 = uniform(xmin, xmax)
        else:
            x0 = float(en_estim.get())

        kmax = int(sb_iter.get())
        func = str(en_func.get())

        timer = time.perf_counter()

        output("function", func)
        output("")
        
        output("[First Method]")
        k, x = compute_sol(func, h, x0, G["G1"])
        if k != -1:
            output("solution found at iteration number", k)
            output("x", x)

            f2 = compute_F2(func, h, x)
            if f2 > 0:
                output("x is a minimum")
            else:
                output("x is not a minimum")
        else:
            output("divergence")
        
        output("")
        
        output("[Second Method]")
        k, x = compute_sol(func, h, x0, G["G2"])
        if k != -1:
            output("solution found at iteration number", k)
            output("x", x)

            f2 = compute_F2(func, h, x)
            if f2 > 0:
                output("x is a minimum")
            else:
                output("x is not a minimum")
        else:
            output("divergence")

        timer = time.perf_counter() - timer

        output("")
        output("time elapsed", timer)
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
lb_func = tk.Label(f11, text="function:")
lb_func.pack(side=tk.LEFT)
en_func = tk.Entry(f11, width=30)
en_func.pack(side=tk.RIGHT)

f12 = tk.Frame(f1)
f12.pack(side=tk.TOP, anchor=tk.W)
lb_estim = tk.Label(f12, text="estimation:")
lb_estim.pack(side=tk.LEFT)
en_estim = tk.Entry(f12, width=9)
en_estim.pack(side=tk.RIGHT)

v_random = tk.BooleanVar()
cb_random = tk.Checkbutton(f1, text="Use a random number", variable=v_random, onvalue=True, offvalue=False, command=switch_random)
cb_random.pack(side=tk.TOP, anchor=tk.W)

f13 = tk.Frame(f1)
f13.pack(side=tk.BOTTOM, anchor=tk.W)
lb_min = tk.Label(f13, text="min:")
lb_min.pack(side=tk.LEFT)
en_min = tk.Entry(f13, state=tk.DISABLED, width=9)
en_min.pack(side=tk.LEFT)
lb_max = tk.Label(f13, text="max:")
lb_max.pack(side=tk.LEFT)
en_max = tk.Entry(f13, state=tk.DISABLED, width=9)
en_max.pack(side=tk.RIGHT)

f2 = tk.Frame(window)
f2.pack(side=tk.RIGHT)

f21 = tk.Frame(f2)
f21.pack(side=tk.TOP, anchor=tk.W)
lb_iter = tk.Label(f21, text="max iterations:")
lb_iter.pack(side=tk.LEFT)
sb_iter = tk.Spinbox(f21, from_=1000, to=1000000, inc=1000, width=7)
sb_iter.pack(side=tk.RIGHT)

bt_solve = tk.Button(f2, text="Solve", command=solve)
bt_solve.pack(side=tk.TOP)

bt_output = tk.Button(f2, text="Open Output File", command=open_output)
bt_output.pack(side=tk.TOP)

f22 = tk.Frame(f2)
f22.pack(side=tk.TOP)
lb_xmin = tk.Label(f22, text="xmin:")
lb_xmin.pack(side=tk.LEFT)
en_xmin = tk.Entry(f22, width=6)
en_xmin.pack(side=tk.LEFT)
lb_xmax = tk.Label(f22, text="xmax:")
lb_xmax.pack(side=tk.LEFT)
en_xmax = tk.Entry(f22, width=6)
en_xmax.pack(side=tk.RIGHT)

bt_graphic = tk.Button(f2, text="View Function Graphic", command=show_graphic)
bt_graphic.pack(side=tk.BOTTOM)

window.mainloop()