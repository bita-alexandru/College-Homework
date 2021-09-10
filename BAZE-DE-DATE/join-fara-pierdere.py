sigma = list()
atribute = list()
raspunsuri = list()

with open("input.txt", "rt") as fd:
    atribute = fd.readline().replace("\n", "").replace(" ", "").split(",")
    sigma = fd.readline().replace("\n", "").replace(" ", "").split(",")

    for i in range(len(sigma)):
        sigma[i] = sigma[i].split(">")

    linii = fd.readlines()

    optiuni = list()
    for linie in linii:
        variante = linie.replace("\n", "").split(" ")

        for varianta in variante:
            if len(varianta) == 0:
                continue
            
            o = varianta.split(")", 1)[0]
            r1, r2 = varianta.split(")", 1)[1].replace("R1", "").replace("R2", "").replace("(", "").replace(")", "").split(";")
            optiuni.append([o, (r1, r2)])
        
        optiuni.sort(key=lambda i: i[0])
    
    for o, r in optiuni:
        print(o + ")", r[0], r[1], end=" ")

        r1 = set()
        for c in r[0]:
            r1.add(c)
        
        r2 = set()
        for c in r[1]:
            r2.add(c)
        
        if len(r1.union(r2)) != len(atribute):
            print()
            continue
        
        intersectie = "".join(sorted(list(r1.intersection(r2))))

        if len(intersectie) == 0:
            print()
            continue

        chei = list()
        inchidere = list(intersectie)

        # print(o+")",inchidere)

        modificat = True
        while modificat:
            modificat = False

            for stanga, dreapta in sigma:
                ok = True
                for c in stanga:
                    if c not in inchidere:
                        ok = False
                        break
                
                if ok:
                    for c in dreapta:
                        if c not in inchidere:
                            inchidere.append(c)
                            modificat = True
        
        # print("f+:",sorted(inchidere))
        # print("r1+:",sorted(list(r1)))
        # print("r2+:",sorted(list(r2)))
        
        if r1.issubset(set(inchidere)) or r2.issubset(set(inchidere)): 
            print("[adevarat]", end="")
            raspunsuri.append(o)
        
        print()

    for r in raspunsuri:
        print(r, end="")