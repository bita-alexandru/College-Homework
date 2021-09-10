import math
import time
import random
import tkinter as tk
from tkinter import messagebox

def func_cont(x, epsilon = 1e-15):
    mic = 1e-12

    b0 = 0
    aj = 0

    f0 = b0
    if f0 == 0: f0 = mic

    C0 = f0
    D0 = 0
    
    j = 1

    while True:
        if j == 1:
            bj = 1
            aj = x
        else:
            aj = -(x*x)

        Dj = bj + aj*D0
        if Dj == 0: Dj = mic

        Cj = bj + aj/C0
        if Cj == 0: Cj = mic

        Dj = 1/Dj

        delta = Cj*Dj
        fj = delta*f0

        j += 1

        if abs(delta - 1) < epsilon: break

        bj += 2
        f0 = fj
        D0 = Dj
        C0 = Cj

    return fj

def func_poli(x):
    c1 = 1/3
    c2 = 2/15
    c3 = 17/315
    c4 = 62/2835
    x_2 = x*x
    x_3 = x_2*x
    x_5 = x_3*x_2
    x_7 = x_5*x_2
    x_9 = x_7*x_2

    return x + c1*x_3 + c2*x_5 + c3*x_7 + c4*x_9

def sample_poli():
    err_avg = 0
    time_avg = time.perf_counter()
    err_max = -infinit
    time_max = -infinit

    for i in range(size):
        x = random.uniform(-lim, lim)

        time_start = time.perf_counter()

        if lim/2 <= x < lim:
            result = 1/func_poli(lim - x)
        elif -lim < x <= -lim/2:
            result = -1/func_poli(lim + x)
        else:
            result = func_poli(x)

        time_end = time.perf_counter() - time_start

        real = math.tan(x)

        err = abs(real - result)
        err_avg += abs(real - result)

        if err_max < err:
            err_max = err
            x_err = x
        if time_max < time_end:
            time_max = time_end
            x_time = x

        # print("x = %f"%x)

        # print("result = %f"%result)
        # print("real = %f"%real)
        # print("error = %f"%abs(real-result))
        # print()

    time_avg = (time.perf_counter() - time_avg) / size
    err_avg /= size

    # print("Metoda cu polinoame:\neroarea medie = %f\ntimpul mediu = %f secunde\n"%(err_avg, time_avg))
    lb_erravg_right.config(text="avg err: %.10f"%err_avg)
    lb_timeavg_right.config(text="avg time: %.10f"%time_avg)
    lb_errmax_right.config(text="max error: %.10f (x~%.5f)"%(err_max, x_err))
    lb_timemax_right.config(text="max time: %.10f (x~%.5f)"%(time_max, x_time))

def sample_cont():
    err_avg = 0
    time_avg = time.perf_counter()
    err_max = -infinit
    time_max = -infinit

    for i in range(size):
        x = random.uniform(-lim, lim)

        time_start = time.perf_counter()

        if x < 0:
            result = -func_cont(-x)
        else:
            result = func_cont(x)

        time_end = time.perf_counter() - time_start

        real = math.tan(x)

        err = abs(real - result)
        err_avg += err

        if err_max < err:
            err_max = err
            x_err = x
        if time_max < time_end:
            time_max = time_end
            x_time = x

        # print("x = %f"%x)

        # print("result = %f"%result)
        # print("real = %f"%real)
        # print("error = %f"%abs(real-result))
        # print()

    time_avg = (time.perf_counter() - time_avg) / size
    err_avg /= size

    # print("Metoda cu fractii continue:\neroarea medie = %f\ntimpul mediu = %f secunde"%(err_avg, time_avg))
    lb_erravg_left.config(text="avg err: %.10f"%err_avg)
    lb_timeavg_left.config(text="avg time: %.10f"%time_avg)
    lb_errmax_left.config(text="max error: %.10f (x~%.5f)"%(err_max, x_err))
    lb_timemax_left.config(text="max time: %.10f (x~%.5f)"%(time_max, x_time))


def calc_poli():
    try:
        x = float(nt_x_right.get())
        x = special_cases(x)
        if lim/2 <= x < lim: #lim=pi/2
            result = 1/func_poli(lim - x)
        elif -lim < x <= -lim/2:
            result = -1/func_poli(lim + x)
        else:
            result = func_poli(x)

        real = math.tan(x)
        err = abs(real - result)

        lb_res_right.config(text="method result: %.10f"%result)
        lb_real_right.config(text="real result: %.10f"%real)
        lb_err_right.config(text="error: %.10f"%err)
    except Exception as e:
        # print("error",e)
        if str(e) == "nedefinit":
            messagebox.showinfo("Undefined", "Result is undefined.")
        elif str(e) == "zero":
            result = 0
            real = math.tan(x)
            err = abs(real - result)
            lb_res_right.config(text="method result: %.10f"%result)
            lb_real_right.config(text="real result: %.10f"%real)
            lb_err_right.config(text="error: %.10f"%err)
        else:
            messagebox.showerror("Error","Incorrect input. Try again!")

def calc_cont():
    try:
        x = float(nt_x_left.get())
        x = special_cases(x)
        if x < 0:
            result = -func_cont(-x)
        else:
            result = func_cont(x)

        real = math.tan(x)
        err = abs(real - result)

        lb_res_left.config(text="method result: %.10f"%result)
        lb_real_left.config(text="real result: %.10f"%real)
        lb_err_left.config(text="error: %.10f"%err)
    except Exception as e:
        # print("error",e)
        if str(e) == "nedefinit":
            messagebox.showinfo("Undefined", "Result is undefined.")
        elif str(e) == "zero":
            result = 0
            real = math.tan(x)
            err = abs(real - result)
            lb_res_left.config(text="method result: %.10f"%result)
            lb_real_left.config(text="real result: %.10f"%real)
            lb_err_left.config(text="error: %.10f"%err)
        else:
            messagebox.showerror("Error","Incorrect input. Try again!")

def special_cases(x):
    if x%lim == 0:
        if (x/lim)%2 == 1:
            raise Exception("nedefinit")
        else:
            raise Exception("zero")
    else:
        return x%lim

lim = math.pi/2
size = 10000
infinit = 1e10

print(lim, lim*2, lim*3, lim*4)
print(-lim, -lim*2, -lim*3, -lim*4)

window = tk.Tk()

# frame pt metoda cu fractii continue
f1 = tk.Frame(window)
f1.pack(side=tk.LEFT, anchor=tk.N)

lb_func_left = tk.Label(f1, text="Continued fraction")
lb_func_left.pack(side=tk.TOP)

f2 = tk.Frame(f1)
f2.pack(side=tk.TOP)
lb_x_left = tk.Label(f2, text="x=")
lb_x_left.pack(side=tk.LEFT)

nt_x_left = tk.Entry(f2)
nt_x_left.pack(side=tk.LEFT)

bt_calc_left = tk.Button(f2, text="Calculate", command=calc_cont)
bt_calc_left.pack(side=tk.RIGHT)

f3 = tk.Frame(f1)
f3.pack(side=tk.BOTTOM, anchor=tk.W)

lb_res_left = tk.Label(f3, text="method result:")
lb_res_left.pack(side=tk.TOP, anchor=tk.W)

lb_real_left = tk.Label(f3, text="real result:")
lb_real_left.pack(side=tk.TOP, anchor=tk.W)

lb_err_left = tk.Label(f3, text="error:")
lb_err_left.pack(side=tk.TOP, anchor=tk.W)

bt_sample_left = tk.Button(f3, text="Sample", command=sample_cont)
bt_sample_left.pack(side=tk.TOP)

lb_erravg_left = tk.Label(f3, text="avg error:")
lb_erravg_left.pack(side=tk.TOP, anchor=tk.W)

lb_timeavg_left = tk.Label(f3, text="avg time:")
lb_timeavg_left.pack(side=tk.TOP, anchor=tk.W)

lb_errmax_left = tk.Label(f3, text="max error:")
lb_errmax_left.pack(side=tk.BOTTOM, anchor=tk.W)

lb_timemax_left = tk.Label(f3, text="max time:")
lb_timemax_left.pack(side=tk.BOTTOM, anchor=tk.W)


# frame pt metoda cu functie polinomiala
f4 = tk.Frame(window)
f4.pack(side=tk.RIGHT, anchor=tk.N)

lb_func_right = tk.Label(f4, text="Polynomial function")
lb_func_right.pack(side=tk.TOP)

f5 = tk.Frame(f4)
f5.pack(side=tk.TOP)

lb_x_right = tk.Label(f5, text="x=")
lb_x_right.pack(side=tk.LEFT)
nt_x_right = tk.Entry(f5)
nt_x_right.pack(side=tk.LEFT)
bt_calc_right = tk.Button(f5, text="Calculate", command=calc_poli)
bt_calc_right.pack(side=tk.RIGHT)

f6 = tk.Frame(f4)
f6.pack(side=tk.BOTTOM, anchor=tk.W)

lb_res_right = tk.Label(f6, text="method result:")
lb_res_right.pack(side=tk.TOP, anchor=tk.W)

lb_real_right = tk.Label(f6, text="real result:")
lb_real_right.pack(side=tk.TOP, anchor=tk.W)

lb_err_right = tk.Label(f6, text="error:")
lb_err_right.pack(side=tk.TOP, anchor=tk.W)

bt_sample_right = tk.Button(f6, text="Sample", command=sample_poli)
bt_sample_right.pack(side=tk.TOP)

lb_erravg_right = tk.Label(f6, text="avg error:")
lb_erravg_right.pack(side=tk.TOP, anchor=tk.W)

lb_timeavg_right = tk.Label(f6, text="avg time:")
lb_timeavg_right.pack(side=tk.TOP, anchor=tk.W)

lb_errmax_right = tk.Label(f6, text="max error:")
lb_errmax_right.pack(side=tk.BOTTOM, anchor=tk.W)

lb_timemax_right = tk.Label(f6, text="max time:")
lb_timemax_right.pack(side=tk.BOTTOM, anchor=tk.W)

window.mainloop()