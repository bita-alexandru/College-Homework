"""
Considerăm o hartă cu n țări. Fiecare regiune/țară poate fi colorată cu o culoare dintr-o mulțime de culori
asociate. Să se coloreze harta a.î. regiunile/țările vecine să fie colorate diferit.
Modelare: asignăm fiecarei regiuni/țări de pe hartă o variabilă; domeniul fiecarei variabile este o mulțime
de culori specificată. Restricțiile sunt de forma: Xi ≠ Xj
(două țări vecine au culori diferite). Obs: între două țări vecine în graful constrâns vom adăuga o muchie.
"""

def read_input(fn):
    nodes = []
    arcs = []
    adj = dict()
    colors = dict()

    with open(fn) as fd:
        for line in fd:
            line = line.replace(" ", "").replace("\n", "").replace("{","").replace("}","")
            tmp = line.split(":")

            if len(tmp) == 2:
                nodes.append(tmp[0])

                tmp = tmp[1].split(",")
                for i in range(len(tmp)):
                    arcs.append((nodes[-1], tmp[i]))
                    
                    if nodes[-1] not in adj:
                        adj[nodes[-1]] = []
                        colors[nodes[-1]] = []
                    adj[nodes[-1]].append(tmp[i])
            elif len(tmp) > 2:
                line = line.split(";")
                for i in range(len(line)):
                    tmp1 = line[i].split(":")
                    tmp2 = tmp1[1].split(',')
                    for j in range(len(tmp2)):
                        colors[tmp1[0]].append(tmp2[j])

    return nodes, arcs, adj, colors

def remove_inconsistency(X, Y):
    removed = False

    for x in X:
        satisfied = False
        for y in Y:
            if x != y:
                satisfied = True
                break
        if not satisfied:
            print("removing " + str(x) + " from " + str(X))
            X.remove(x)
            removed = True

    return removed

def solve_ac3(nodes, arcs, adj, colors):
    print("I. Applying the algorithm...")

    queue = []
    for i in range(len(arcs)):
        queue.append(arcs[i])
    
    while len(queue) > 0:
        x = queue[0][0]
        y = queue.pop(0)[1]
    
        print(str(x)+":"+str(colors[x])+" - "+str(y)+":"+str(colors[y]))
        if remove_inconsistency(colors[x], colors[y]):
            for neighbour in adj[x]:
                queue.append((neighbour, x))

def give_verdict(colors):
    print("II. Checking the correctness...")

    correct = True
    frequency = dict()
    for i in colors.keys():
        print(str(i) + ": " + str(colors[i]))

        if len(colors[i]) < 1:
            correct = False
        
        for j in colors[i]:
            if j in frequency:
                correct = False
            
            frequency[j] = 1

    if correct:
        print("...consistent and succeeded to solve")
    else:
        print("...consistent but failed to solve")

nodes, arcs, adj, colors = read_input("input.txt")
solve_ac3(nodes, arcs, adj, colors)
give_verdict(colors)
            
# print(nodes)
# print(arcs)
# print(adj)
# print(colors)