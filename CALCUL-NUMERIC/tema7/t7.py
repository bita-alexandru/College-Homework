import os
import time
import sympy
import random
import tkinter as tk
from sympy.abc import x
from tkinter import messagebox
from sympy import Poly, diff, real_roots, gcdex
from sympy.parsing.sympy_parser import parse_expr, standard_transformations, implicit_multiplication_application

epsilon = 1e-6
kmax = 1000
tries = 1

def open_output():
    open("output.txt", "at").close()
    os.startfile("output.txt")

def output(tag, v=None):
    with open("output.txt", "at") as fd:
        if v is None:
            fd.write("%s\n"%tag)
        else:
            fd.write("%s: %s\n"%(tag, v))

def read_input():
    global epsilon, kmax, tries
    epsilon = float(en_eps.get())
    kmax = int(sb_kmax.get())
    tries = int(sb_tries.get())
    expr = str(en_func.get())

    transformations = (standard_transformations + (implicit_multiplication_application,))
    expr = Poly(parse_expr(expr, transformations=transformations), x)
    coefficients = expr.all_coeffs()

    return expr, coefficients

def solve_horner(coefficients, v):
    b = coefficients[0]
    for i in range(1, len(coefficients)):
        b = b * v + coefficients[i]

    return b

def solve_olver(coefficients, expr, xk):
    k = 0
    delta_xk = None

    while True:
        pk = solve_horner(coefficients, xk)

        deriv1_coeff = diff(expr, x).all_coeffs()
        deriv1 = solve_horner(deriv1_coeff, xk)

        deriv2_coeff = diff(expr, x, x).all_coeffs()
        deriv2 = solve_horner(deriv2_coeff, xk)

        if abs(deriv1) <= epsilon:
            break

        if round(deriv1) == 0:
            ck = (round(pk)**2 * deriv2) / epsilon**3
        else:
            ck = (round(pk)**2 * deriv2) / round(deriv1)**3

        delta_xk = pk/deriv1 + 1/2 * ck

        xk -= delta_xk

        k += 1

        if abs(delta_xk) < epsilon or k > kmax or abs(delta_xk) > 10 ** 8:
            break

    if abs(delta_xk) < epsilon:
        return xk
    else:
        return "divergenta"

def div(dividend, divisor):
    '''Fast polynomial division by using Extended Synthetic Division. Also works with non-monic polynomials.'''
    if divisor == [1]:
        return dividend, [0]

    # dividend and divisor are both polynomials, which are here simply lists of coefficients. Eg: x^2 + 3x + 5 will be represented as [1, 3, 5]
    out = list(dividend)  # Copy the dividend
    normalizer = divisor[0]
    for i in range(len(dividend) - (len(divisor) - 1)):
        out[i] /= normalizer  # for general polynomial division (when polynomials are non-monic),
        # we need to normalize by dividing the coefficient with the divisor's first coefficient
        coef = out[i]
        if coef != 0:  # useless to multiply if coef is 0
            for j in range(1, len(
                    divisor)):  # in synthetic division, we always skip the first coefficient of the divisor,
                # because it's only used to normalize the dividend coefficients
                out[i + j] += -divisor[j] * coef

    # The resulting out contains both the quotient and the remainder, the remainder being the size of the divisor (the remainder
    # has necessarily the same degree as the divisor since it's what we couldn't divide from the dividend), so we compute the index
    # where this separation is, and return the quotient and remainder.
    separator = -(len(divisor) - 1)
    return out[:separator], out[separator:]  # return quotient, remainder.

def iszeros(f):
    for val in f:
        if val >= epsilon:
            return False

    return True

def make_expr(coefficients):
    expr = ""
    n = len(coefficients)

    for i in range(n):
        expr += "%s*x**%i+"%(coefficients[i], n-i-1)
    expr += "0"

    transformations = (standard_transformations + (implicit_multiplication_application,))
    expr = Poly(parse_expr(expr, transformations=transformations), x)

    return expr

def gcd(f, g):
    r0 = f
    r1 = g

    if iszeros(r1):
            return r0
    
    while True:
        r2 = div(r0, r1)[1]
        if iszeros(r2):
            return r1

        if len(r2) >= len(r1):
            return [1]

        r0 = r1
        r1 = r2

def mandatory():
    open("output.txt", "wt").close()

    try:
        expr, coefficients = read_input()
        deriv_coeff = diff(expr, x).all_coeffs()
        
        timer = time.perf_counter()

        g = gcd(coefficients, deriv_coeff)
        output("gcd", g)
    
        coefficients, r = div(coefficients, g)
        output("f/gcd", coefficients)

        expr = make_expr(coefficients)

        output("")
        output("sympy.roots", real_roots(expr))
        output("")
        
        R = (abs(coefficients[0]) + max(coefficients)) / abs(coefficients[0])
        output("[-R, R]", "[-%s, %s]"%(R, R))
        
        x0s = list()
        for i in range(tries):
            x0 = random.uniform(-R, R)
            while x0 in x0s:
                x0 = random.uniform(-R, R)
            x0s.append(x0)

        results = list()
        for i in range(tries):
            res = solve_olver(coefficients, expr, x0s[i])

            if res != "divergenta":
                ok = True
                for value in results:
                    if abs(res - value) <= epsilon:
                        ok = False
                if ok is True:
                    results.append(res)

        output("computed roots", sorted(results))

        timer = time.perf_counter() - timer

        output("")
        output("time elapsed", timer)

        if messagebox.askyesno(title="Success", message="Tasks solved successfully.\nTime elapsed: %.3f seconds.\nCheck the output file?"%timer):
            open_output()
    except Exception as e:
        messagebox.showerror(title="Error", message="Invalid input: %s"%e)
    
# mandatory()

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
lb_eps = tk.Label(f12, text="epsilon:")
lb_eps.pack(side=tk.LEFT)
en_eps = tk.Entry(f12, width=6)
en_eps.pack(side=tk.RIGHT)

f13 = tk.Frame(f1)
f13.pack(side=tk.TOP, anchor=tk.W)
lb_kmax = tk.Label(f13, text="kmax:")
lb_kmax.pack(side=tk.LEFT)
sb_kmax = tk.Spinbox(f13, from_=1000, to=100000, inc=1000, width=7)
sb_kmax.pack(side=tk.RIGHT)

f14 = tk.Frame(f1)
f14.pack(side=tk.BOTTOM, anchor=tk.W)
lb_tries = tk.Label(f14, text="tries:")
lb_tries.pack(side=tk.LEFT)
sb_tries = tk.Spinbox(f14, from_=10, to=1000, inc=10, width=7)
sb_tries.pack(side=tk.RIGHT)

f2 = tk.Frame(window)
f2.pack(side=tk.RIGHT)

bt_solve = tk.Button(f2, text="Solve", command=mandatory)
bt_solve.pack(side=tk.TOP)

bt_output = tk.Button(f2, text="Open Output File", command=open_output)
bt_output.pack(side=tk.BOTTOM)

window.mainloop()