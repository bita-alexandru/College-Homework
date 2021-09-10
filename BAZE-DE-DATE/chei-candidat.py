sigma = list()
atribute = list()
chei = list()
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
            optiuni.append(varianta.split(")"))
    
    optiuni.sort(key=lambda i: len(i[1]))

    for o, x in optiuni:
        if sorted(x) in chei:
            raspunsuri.append(o)
            continue

        ok = 0
        for cheie in chei:
            for c in cheie:
                if c not in x:
                    ok += 1
        
        if ok != len(chei): # nu e cheie candidat
            continue

        inchidere = list(x)

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
        
        if len(inchidere) == len(atribute): # este supercheie
            chei.append(x)
            raspunsuri.append(o)

    raspunsuri.sort()
    optiuni.sort(key=lambda i: i[0])

    for o, x in optiuni:
        print(o + ")", x, "[adevarat]" if o in raspunsuri else "")
    
    for r in raspunsuri:
        print(r, end="")