val = dict()
coloane = list()
raspunsuri = list()

with open("input.txt", "rt") as fd:
    atribute = fd.readline().replace("\n", "")

    for atr in atribute.split(" "):
        val[atr] = list()
        coloane.append(atr)
    
    while True:
        tupla = fd.readline()

        if tupla == "\n":
            break

        tupla = tupla.replace("\n", "")

        tmp = tupla.split(" ")
        for i in range(len(tmp)):
            val[coloane[i]].append(tmp[i])

    dependente = fd.readlines()

    for dep in dependente:
        dep = dep.replace("\n", "")

        toks = dep.split(" ")
        
        var = toks[0]
        stanga = toks[1]
        dreapta = ""
        tip = ""

        tmp = toks[2].split(">")
        if len(tmp) > 2:
            tip = "multi"
            dreapta = tmp[2]
        else:
            tip = "func"
            dreapta = tmp[1]

        if tip == "func":
            n = len(val[coloane[0]])

            satisface = True
            for i in range(n):
                x1 = ""
                for col in stanga:
                    x1 += val[col][i] + "; "

                y1 = ""
                for col in dreapta:
                    y1 += val[col][i] + "; "

                for j in range(i+1, n-1):
                    x2 = ""
                    for col in stanga:
                        x2 += val[col][j] + "; "

                    y2 = ""
                    for col in dreapta:
                        y2 += val[col][j] + "; "

                    if x1 == x2 and y1 != y2:
                        satisface = False
                        break
                
                if not satisface:
                    break
        else:
            n = len(val[coloane[0]])

            satisface = True
            for i in range(n):
                x1 = ""
                for col in stanga:
                    x1 += val[col][i] + "; "

                y1 = ""
                for col in dreapta:
                    y1 += val[col][i] + "; "

                z1 = ""
                for col in coloane:
                    if col not in dreapta and col not in stanga:
                        z1 += val[col][i] + "; "
                
                for j in range(i+1, n-1):
                    x2 = ""
                    for col in stanga:
                        x2 += val[col][j] + "; "

                    y2 = ""
                    for col in dreapta:
                        y2 += val[col][j] + "; "

                    z2 = ""
                    for col in coloane:
                        if col not in dreapta and col not in stanga:
                            z2 += val[col][j] + "; "
                    
                    if x1 == x2:
                        local = False

                        for k in range(n):
                            x3 = ""
                            for col in stanga:
                                x3 += val[col][k] + "; "

                            y3 = ""
                            for col in dreapta:
                                y3 += val[col][k] + "; "

                            z3 = ""
                            for col in coloane:
                                if col not in dreapta and col not in stanga:
                                    z3 += val[col][k] + "; "
                            
                            if x3 == x1 and y3 == y1 and z3 == z2:
                                for l in range(n):
                                    x4 = ""
                                    for col in stanga:
                                        x4 += val[col][l] + "; "

                                    y4 = ""
                                    for col in dreapta:
                                        y4 += val[col][l] + "; "

                                    z4 = ""
                                    for col in coloane:
                                        if col not in dreapta and col not in stanga:
                                            z4 += val[col][l] + "; "
                                    
                                    if x4 == x2 and y4 == y2 and z4 == z1:
                                        local = True
                                        break
                            
                            if local:
                                break

                        if not local:
                            satisface = False
                            break

                    if not satisface:
                        break

                if not satisface:
                        break

        print(var, stanga, ">" if tip == "func" else ">>", dreapta, end=" ")
        if satisface:
            print("[adevarat]", end="")
            raspunsuri.append(var[0])
        print()

    for r in raspunsuri:
        print(r, end="")
