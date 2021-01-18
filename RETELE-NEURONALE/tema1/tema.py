import numpy as np

def read_input(fn):
    vq = []
    vr = []

    with open(fn) as fd:
        for eq in fd:
            eq = eq.replace(' ','')
            eq = eq.split("=")

            r = float(eq[1])
            
            a = 0
            if eq[0].find("x") != -1:
                tmp = eq[0].split("x")[0]
                sgn = -1 if len(tmp.lstrip('-')) < len(tmp) else 1

                if len(tmp.strip("+-")) > 0:
                    a = float(tmp.lstrip("+-")) * sgn
                else:
                    a = sgn
                
                eq[0] = eq[0].replace(tmp+"x",'')
            
            b = 0
            if eq[0].find("y") != -1:
                tmp = eq[0].split("y")[0]
                sgn = -1 if len(tmp.lstrip('-')) < len(tmp) else 1

                if len(tmp.strip("+-")) > 0:
                    b = float(tmp.lstrip("+-")) * sgn
                else:
                    b = sgn
                
                eq[0] = eq[0].replace(tmp+"y",'')

            c = 0
            if eq[0].find("z") != -1:
                tmp = eq[0].split("z")[0]
                sgn = -1 if len(tmp.lstrip('-')) < len(tmp) else 1

                if len(tmp.strip("+-")) > 0:
                    c = float(tmp.lstrip("+-")) * sgn
                else:
                    c = sgn
                
                eq[0] = eq[0].replace(tmp+"z",'')

            vq.append([a,b,c])
            vr.append([r])
    
    return [vq,vr]

def solve_standard(mxa,mxb):
    A = mxa
    B = mxb

    A_det = A[0][0]*A[1][1]*A[2][2] + A[1][0]*A[2][1]*A[0][2] + A[0][1]*A[1][2]*A[2][0] - \
            A[0][2]*A[1][1]*A[2][0] - A[1][2]*A[2][1]*A[0][0] - A[0][1]*A[1][0]*A[2][2]

    if A_det == 0:
        print("solve_standard: unsolvable")            
        return

    A_trans = [[A[i][j] for i in range(len(A))] for j in range(len(A[0]))] 

    A_adj = [[0,0,0],[0,0,0],[0,0,0]]
    for i in range(0,3):
        for j in range(0,3):
            l1 = (i+1)%3 if i==0 else 0
            c1 = (j+1)%3 if j==0 else 0
            l2 = (l1+1)%3 if (l1+1)%3 != i else (l1+2)%3
            c2 = (c1+1)%3 if (c1+1)%3 != j else (c1+2)%3

            A_adj[i][j] = (-1)**(i+j) * (A_trans[l1][c1]*A_trans[l2][c2]-A_trans[l1][c2]*A_trans[l2][c1])

    A_inv = A_adj
    for i in range(0,3):
        for j in range(0,3):
            A_inv[i][j] *= (1/A_det)

    X = [[0],[0],[0]]
    for i in range(len(A_inv)):
        for j in range(len(B[0])):
            for k in range(len(B)):
                X[i][j] += A_inv[i][k] * B[k][j]

    print("solve_standard:")
    print(X)

def solve_numpy(mxa,mxb):
    A = np.array(mxa)
    B = np.array(mxb)
    
    if np.linalg.det(A) == 0:
        print("solve_numpy: unsolvable")
        return
    
    A_inv = np.linalg.inv(A)
    X = np.dot(A_inv,B)

    print("solve_numpy:")
    print(X)

mxs = read_input("ecuatii.txt")

solve_standard(mxs[0],mxs[1])
solve_numpy(mxs[0],mxs[1])