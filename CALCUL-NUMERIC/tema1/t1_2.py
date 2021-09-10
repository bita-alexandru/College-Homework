u = 1e-15

a = 1.0
b = u/10
c = u/10

stanga = (a + b) + c
dreapta = a + (b + c)

print(str(stanga) + " == " + str(dreapta), stanga == dreapta)

a = 1e8
b = u
c = u

stanga = (a * b) * c
dreapta = a * (b * c)

print(str(stanga) + " == " + str(dreapta), stanga == dreapta)