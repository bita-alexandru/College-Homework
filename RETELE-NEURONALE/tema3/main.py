import pickle
import gzip
import numpy as np
import matplotlib.pyplot as plt

def sigmoid(z):
    return 1/(1 + np.exp(-z))

def sigmoid_drv(z):
    return sigmoid(z) * (1 - sigmoid(z))

def feed_forward(network, z):
    weights, biases = network

    for w, b in zip(weights, biases):
        z = sigmoid(np.dot(w,z) + b)
    return z

def backpropagate(weights, biases, x, o):
    delta_nabla_w = [np.zeros(w.shape) for w in weights]
    delta_nabla_b = [np.zeros(b.shape) for b in biases]

    activation = x

    # store all the activations layer by layer
    activations = [x]

    # store all the z vectors layer by layer
    zs = []

    for w, b in zip(weights, biases):
        z = np.dot(w, activation) + b
        zs.append(z)

        activation = sigmoid(z)
        activations.append(activation)

    # compute the error in the last layer
    delta = activations[-1] - o

    # assign the change in values of weights and biases for the final layer
    delta_nabla_b[-1] = delta
    delta_nabla_w[-1] = np.dot(delta, activations[-2].transpose())

    # calculate the errors and the change in {weights, biases} for the each layer
    for layer in range(2, 3):
        z = zs[-layer]

        sdrv = sigmoid_drv(z)

        # calculating the error
        delta = np.dot(weights[-layer+1].transpose(), delta) * sdrv

        # assign the change in values of biases and weights
        delta_nabla_w[-layer] = np.dot(delta, activations[-layer-1].transpose())
        delta_nabla_b[-layer] = delta

    return [delta_nabla_w, delta_nabla_b]

def train_network(data):
    weights = [np.random.randn(i, j) / np.sqrt(j) for j, i in zip([784, 100], [100, 10])]
    biases = [np.random.randn(i, 1) for i in [100, 10]]

    SIZE = len(data[0])
    BTCH_SZ = 10
    BTCH_NO = SIZE // BTCH_SZ
    ITERATIONS = 5

    eta = 0.01
    lmbda = 5

    iterations = 0
    while iterations < ITERATIONS:
        order = [i for i in range(SIZE)]
        np.random.shuffle(order)

        for i in range(BTCH_NO):
            # store change in the values of weights
            nabla_w = [np.zeros(w.shape) for w in weights]
            # store change in the values of biases
            nabla_b = [np.zeros(b.shape) for b in biases]

            for j in range(BTCH_SZ):
                indx = order[i*BTCH_SZ + j]
                x = np.reshape(data[0][indx], (784,1))
                o = np.zeros((10,1))
                o[data[1][indx]] = 1

                # store change in weights and biases respectively
                delta_nabla_w, delta_nabla_b  = backpropagate(weights, biases, x, o)

                nabla_w = [nw+dnw for nw, dnw in zip(nabla_w, delta_nabla_w)]
                nabla_b = [nb+dnb for nb, dnb in zip(nabla_b, delta_nabla_b)]

            # update {weights, biases} and apply L2 Regularization
            weights = [(1-eta*(lmbda/SIZE))*w - eta*nw for w, nw in zip(weights, nabla_w)]
            biases = [b-eta*nb for b, nb in zip(biases, nabla_b)]
        
        iterations += 1

    return [weights, biases]

def test_network(network, data):
    SIZE = len(data[0])

    results = []
    for i in range(SIZE):
        x = np.reshape(data[0][i], (784,1))
        o = data[1][i]

        results.append((np.argmax(feed_forward(network, x)), o))

    accuracy = sum(int(x == o) for x, o in results)

    print("test accuracy: " + str((accuracy/SIZE) * 100))

with gzip.open("mnist.pkl.gz", "rb") as fd:
    train_set, valid_set, test_set = pickle.load(fd, encoding="latin")

network = train_network(train_set)
test_network(network, test_set)