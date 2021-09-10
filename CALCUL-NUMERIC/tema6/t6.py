import os
import math
import time
import numpy
import random
import tkinter as tk
from tkinter import messagebox
import matplotlib.pyplot as plt
from math import sin, cos, tan, sqrt, e

x_values = list()
y_values = list()
m = 0
coefficients = list()
d = 0
f = ""

def open_output():
    open("output.txt", "at").close()
    os.startfile("output.txt")

def open_data():
    open("data.txt", "at").close()
    os.startfile("data.txt")

def output(tag, v=None):
    with open("output.txt", "at") as fd:
        if v is None:
            fd.write("%s\n"%tag)
        else:
            fd.write("%s: %s\n"%(tag, v))

def read_input():
    a = float(en_x0.get())
    b = float(en_xn.get())
    f = str(en_func.get())
    d = float(en_d.get())

    return a, b, f, d

def generate_xy(a, b, n, f):
    n -= 2
    x_values = list()
    y_values = list()

    x_values.append(a)
    x_values.append(b)

    for i in range(n):
        xi = random.uniform(a, b)

        while xi in x_values:
            xi = random.uniform(a, b)

        x_values.append(xi)

    x_values.sort()

    for i in range(len(x_values)):
        x = x_values[i]
        y_values.append(eval(f))

    return x_values, y_values

def solve_least_squares(m, n, x, y):
    a = list()
    b = list()

    for i in range(m + 1):
        c = list()
        for j in range(m + 1):
            val = 0
            for k in range(n + 1):
                val += x[k] ** (i + j)
            c.append(val)

        a.append(c)

    for i in range(m + 1):
        val = 0
        for k in range(n + 1):
            val += y[k] * (x[k] ** i)
        b.append(val)

    coefficients = numpy.linalg.solve(numpy.array(a), numpy.array(b))

    return coefficients

def solve_horner(m, coefficients, x):
    d = coefficients[m]
    for i in range(1, m + 1):
        d = d * x + coefficients[m - i]

    return d

def calc_diff(x_values, y_values, m, n, coefficients):
    s = 0
    for i in range(n + 1):
        res = solve_horner(m, coefficients, x_values[i])
        s += abs(res - y_values[i])

    return s

def solve_spline(x_values, y_values, d, i0, x):
    Ai0 = A0 = d
    Ai1 = None
    hi0 = x_values[1] - x_values[0]

    for i in range(1, i0 + 2):
        h = x_values[i] - x_values[i - 1]
        A = -A0 + 2 * (y_values[i] - y_values[i - 1]) / h
        if i == i0:
            Ai0 = A
            hi0 = h
        if i == i0 + 1:
            Ai1 = A

        A0 = A

    Sf = (Ai1 - Ai0) / (2 * hi0) * ((x - x_values[i0]) ** 2) + Ai0 * (x - x_values[i0]) + y_values[i0]

    return Sf

def mandatory():
    global  x_values, y_values, m, coefficients, d, f
    x_values = list()
    y_values = list()
    m = 0
    coefficients = list()
    d = 0
    f = ""

    open("output.txt", "wt").close()

    try:
        a, b, f, d = read_input()
        n = int(sb_n.get())
        m = int(sb_m.get())

        timer = time.perf_counter()

        x_values, y_values = generate_xy(a, b, n + 1, f)

        i0 = random.randint(0, n - 1)
        x = random.uniform(x_values[i0], x_values[i0 + 1])
        while x in x_values:
            x = random.uniform(x_values[i0], x_values[i0 + 1])

        coefficients = solve_least_squares(m, n, x_values, y_values)

        result = solve_horner(m, coefficients, x)
        real_result = eval(f)
        diff = (abs(result - real_result))

        s = (calc_diff(x_values, y_values, m, n, coefficients))
        Sf = solve_spline(x_values, y_values, d, i0, x)

        output("n", n)
        output("m", m)
        output("f(x)", real_result)
        output("Pm(x)", result)
        output("|Pm(x) - f(x)|", diff)
        output("sum|Pm(xi) - yi|, 0 <= i <= n", s)
        output("Sf(x)", Sf)
        output("|Sf(x) - f(x)|", abs(Sf - real_result))

        timer = time.perf_counter() - timer
        output("")
        output("time elapsed", timer)

        if messagebox.askyesno(title="Success", message="Tasks solved successfully.\nTime elapsed: %.3f seconds.\nCheck the output file?"%timer):
            open_output()
    except Exception as e:
        messagebox.showerror(title="Error", message="Invalid input: %s"%e)

def bonus():
    global  x_values, y_values, m, coefficients, d, f

    try:
        a = list()
        b = list()

        plt.close()

        if v_new.get():
            with open("data.txt", "wt") as fd:
                for i in range(len(x_values) - 1):
                    # c = random.uniform(x_values[i], (x_values[i + 1] + x_values[i])/2)
                    c = random.uniform(x_values[i], x_values[i + 1])
                    while c in x_values:
                        c = random.uniform(x_values[i], x_values[i + 1])
                    a.append(c)

                    fd.write("[%i] (x_init) %s (x_new) %s\n"%(i, x_values[i], c))

            # f(x)
            for i in range(len(a)):
                x = a[i]
                b.append(eval(f))
        else:
            a = x_values[:-1]
            b = y_values[:-1]

            with open("data.txt", "wt") as fd:
                for i in range(len(a)):
                    fd.write("[%i] (x_init) %s\n"%(i, a[i]))

        plt.plot(a, b, label='f(x)')

        # Pm(x)
        b = list()
        for i in range(len(a)):
            b.append(solve_horner(m, coefficients, a[i]))

        plt.plot(a, b, label='Pm(x)')

        # Sf(x)
        b = list()
        for i in range(len(a)):
            b.append(solve_spline(x_values, y_values, d, i, a[i]))

        plt.plot(a, b, label='Sf(x)')
        plt.xlabel('x - axis')
        plt.ylabel('y - axis')
        plt.legend()
        plt.show()
    except Exception as e:
        messagebox.showerror(title="Error", message="Invalid input: %s"%e)

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
lb_n = tk.Label(f12, text="no. of points(n):")
lb_n.pack(side=tk.LEFT)
sb_n = tk.Spinbox(f12, from_=2, to=1e5, inc=1, width=5)
sb_n.pack(side=tk.RIGHT)

f13 = tk.Frame(f1)
f13.pack(side=tk.TOP, anchor=tk.W)
lb_x0 = tk.Label(f13, text="x0:")
lb_x0.pack(side=tk.LEFT)
en_x0 = tk.Entry(f13, width=7)
en_x0.pack(side=tk.LEFT)
lb_xn = tk.Label(f13, text="xn:")
lb_xn.pack(side=tk.LEFT)
en_xn = tk.Entry(f13, width=7)
en_xn.pack(side=tk.LEFT)
lb_d = tk.Label(f13, text="f'(x0):")
lb_d.pack(side=tk.LEFT)
en_d = tk.Entry(f13, width=7)
en_d.pack(side=tk.RIGHT)

f14 = tk.Frame(f1)
f14.pack(side=tk.TOP, anchor=tk.W)
lb_m = tk.Label(f14, text="poly. degree(m):")
lb_m.pack(side=tk.LEFT)
sb_m = tk.Spinbox(f14, from_=1, to=5, inc=1, width=3)
sb_m.pack(side=tk.RIGHT)

f2 = tk.Frame(window)
f2.pack(side=tk.RIGHT)
v_new = tk.BooleanVar()
v_new.set(tk.TRUE)
cb_new = tk.Checkbutton(f2, text="Test on new data", variable=v_new, onvalue=True, offvalue=False)
cb_new.pack(side=tk.TOP)

bt_solve = tk.Button(f2, text="Solve", command=mandatory)
bt_solve.pack(side=tk.TOP)

bt_output = tk.Button(f2, text="Open Output File", command=open_output)
bt_output.pack(side=tk.TOP)

f21 = tk.Frame(f2)
f21.pack(side=tk.BOTTOM)
bt_graphs = tk.Button(f21, text="View Function Graphs", command=bonus)
bt_graphs.pack(side=tk.LEFT)
bt_data = tk.Button(f21, text="View Dataset", command=open_data)
bt_data.pack(side=tk.RIGHT)

window.mainloop()