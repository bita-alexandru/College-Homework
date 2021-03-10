import numpy as np

def read_input(fn):
    with open(fn) as fd:
        epochs = int(fd.readline())
        eta = float(fd.readline())
        func = fd.readline()
    
    return epochs, eta, func

def generate_trainset(logic, op1, op2, out):
    trainset = [[], []]

    for i in [0,1]:
        for j in [0,1]:
            x1, x2 = i, j

            if logic == "and":
                y = x1 & x2
            elif logic == "or":
                y = x1 | x2
            elif logic == "xor":
                y = x1 ^ x2
            
            if (x1, x2) != (op1, op2):
                trainset[0].append((x1, x2))
                trainset[1].append(y)

    return trainset

def sigmoid(input):
    return 1/(1+np.exp(-input))

def train_network(epochs, eta, trainset):
    LIM = 0.1

    # I. Inițializarea
    # toate ponderile și pragurile rețelei sunt inițializate cu valori aleatorii nenule, distribuite
    # uniform în intervalul (– 0.1, 0.1).
    w = {
        "13":np.random.uniform(-LIM, LIM),
        "23":np.random.uniform(-LIM, LIM),
        "33":np.random.uniform(-LIM, LIM),
        "14":np.random.uniform(-LIM, LIM),
        "24":np.random.uniform(-LIM, LIM),
        "34":np.random.uniform(-LIM, LIM),
        "35":np.random.uniform(-LIM, LIM),
        "45":np.random.uniform(-LIM, LIM),
        "55":np.random.uniform(-LIM, LIM)
    }

    size = len(trainset[0])

    iteration = 0
    while iteration < epochs:
        # II. O nouă epocă de antrenare
        # se inițializează corecțiile ponderilor
        d_w = {
            "13":0,
            "23":0,
            "33":0,
            "14":0,
            "24":0,
            "34":0,
            "35":0,
            "45":0,
            "55":0
        }

        yj = [0, 0] # neuronii din stratul ascuns
        yk = 0 # neuronul din stratul de output
        for i in range(size): # iterăm prin setul de antrenament
            # III. Propagarea semnalului înainte
            # la intrările rețelei se aplică un vector din mulțimea de antrenare
            x1, x2 = trainset[0][i]
            yd = trainset[1][i]

            # se calculează ieșirile neuronilor din stratul ascuns
            yj[0] = sigmoid(x1*w["13"] + x2*w["23"] + 1*w["33"])
            yj[1] = sigmoid(x1*w["14"] + x2*w["24"] + 1*w["34"])
            # se calculează ieșirile reale ale rețelei
            yk = sigmoid(yj[0]*w["35"] + yj[1]*w["45"] + 1*w["55"])

            # IV. Propagarea erorilor înapoi și ajustarea ponderilor
            # se calculează gradienții erorilor pentru neuronii din stratul de ieșire:
            grd_k = yk * (1 - yk) * (yd - yk)
            # se actualizează corecțiile ponderilor dintre stratul ascuns și stratul de ieșire:
            d_w["35"] += (eta * yj[0] * grd_k)
            d_w["45"] += (eta * yj[1] * grd_k)
            d_w["55"] += (eta * 1 * grd_k)

            # se calculează gradienții erorilor pentru neuronii din stratul ascuns:
            grd_j = [0, 0]
            grd_j[0] = yj[0]*(1 - yj[0]) * grd_k*w["35"]
            grd_j[1] = yj[1]*(1 - yj[1]) * grd_k*w["45"]

            # se actualizează corecțiile ponderilor dintre stratul de intrare și stratul ascuns:
            d_w["13"] += (eta * x1 * grd_j[0])
            d_w["23"] += (eta * x2 * grd_j[0])
            d_w["33"] += (eta * 1 * grd_j[0])
            d_w["14"] += (eta * x1 * grd_j[1])
            d_w["24"] += (eta * x2 * grd_j[1])
            d_w["34"] += (eta * 1 * grd_j[1])

        # se actualizează ponderile tuturor conexiunilor pe baza corecțiilor ponderilor
        for i in w:
            w[i] += d_w[i]
        
        # V. O nouă iterație
        
        iteration += 1

    return w

def test_network(x, y, network):
    x1, x2 = x
    w = network

    yj = [0, 0]
    yj[0] = sigmoid(x1*w["13"] + x2*w["23"] + 1*w["33"])
    yj[1] = sigmoid(x1*w["14"] + x2*w["24"] + 1*w["34"])
    yk = sigmoid(yj[0]*w["35"] + yj[1]*w["45"] + 1*w["55"])

    if y-yk < 0:
        output = 0
        certainty = round(50+(yk-y)*50)
    else:
        output = 1
        certainty = round(50+(y-yk)*50)
    
    print("prediction: " + str(output))
    print("certainty: " + str(certainty) + "%")

epochs, eta, func = read_input("input.txt")
logic, x1, x2, y = func.split(" ")

trainset = generate_trainset(logic, int(x1), int(x2), int(y))
network = train_network(epochs, eta, trainset)

# rezultatele antrenamentului
print("TRAINING RESULTS")
for i in range(len(trainset[0])):
    x = trainset[0][i]
    yd = trainset[1][i]
    print("--" + str(x) + " " + str(yd))
    test_network(x, yd, network)

print()

# test pe o functie
print("TESTING RESULTS")
test = (int(x1), int(x2))
print("--" + str(test) + " " + str(y))
test_network(test, int(y), network)