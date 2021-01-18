import pickle
import gzip
import numpy as np
import random
import matplotlib.pyplot as plt

def activation(input):
    if input > 0:
        return 1
    return 0

def train_perceptron(digit, train_set):
    w = np.random.uniform(0,1,(784))
    b = np.random.uniform(0,1)

    all_classified = False
    cnt_iterations = 0
    eta = 0.1
    MAX_ITERATIONS = 30
    
    while not all_classified and cnt_iterations < MAX_ITERATIONS:
        all_classified = True
        total = 0
        wrong = 0
        right = 0

        order = [i for i in range(len(train_set[0]))]
        random.shuffle(order)
        
        for i in order:
            t = 1 if train_set[1][i] == digit else 0
            x = train_set[0][i]
            z = np.dot(w, x) + b
            # standard
            output = activation(z)
            w = w + (t-output)*eta*x
            b = b + (t-output)*eta

            # adaline
            # output = z
            # w = w + np.dot((t-output)*eta, x)
            # b = b + (t-output)*eta
            if output != t:
                all_classified = False
            if t == 1 and cnt_iterations == MAX_ITERATIONS-1:
                total += 1
                if output == 1:
                    right += 1
                else:
                    wrong += 1
            
        # print(str(cnt_iterations) + " : " + "failed " +  str(wrong) + "/" + str(len(train_set[0])) + " & guessed " + str(right) + "/" + str(total))
        cnt_iterations += 1

    print("#right = " + str(right))
    print("#wrong = " + str(wrong))

    return (w, b)

def phase_training(train_set):
    print("I. Starting training phase...")

    perceptrons = []
    for i in range(10):
        perceptrons.append(train_perceptron(i, train_set))
        print("perceptron #" + str(i) + " fully trained")

    return perceptrons

def phase_validation(valid_set, perceptrons):
    print("II. Starting validation phase...")

    right = 0
    wrong = 0

    for i in range(len(valid_set[0])):
        for j in range(10):
            x = valid_set[0][i]
            w, b = perceptrons[j]
            
            input = np.dot(w, x) + b
            output = activation(input)
            digit = valid_set[1][i]

            if digit == j:
                if output == 1:
                    right += 1
                else:
                    wrong += 1
            # else:
            #     if digit == j:
            #         wrong += 1
            #     else:
            #         right +=1

    print("#right = " + str(right))
    print("#wrong = " + str(wrong))

def phase_testing(test_set, perceptrons):
    print("III. Starting testing phase...")

    right = 0
    wrong = 0
    
    for i in range(len(test_set[0])):
        digit = test_set[1][i]
        # print("--test #" + str(i))
        # print("real digit is: " + str(digit))
        plt.imshow(np.reshape(test_set[0][i],(28,28)),cmap="gray")

        activated = []
        for j in range(10):
            x = test_set[0][i]
            w, b = perceptrons[j]
            
            input = np.dot(w, x) + b

            activated.append((input, j))
        
        activated.sort()
        predicted = activated[-1][1]
        
        # print("predicted digit is: " + str(predicted))

        if predicted == digit:
            right += 1
        else:
            wrong += 1
    
    print("#right = " + str(right))
    print("#wrong = " + str(wrong))

train_set = None
valid_set = None
test_set = None

with gzip.open("mnist.pkl.gz", "rb") as fd:
    train_set, valid_set, test_set = pickle.load(fd, encoding="latin")

# training phase
perceptrons = phase_training(train_set)

# validation phase
# phase_validation(valid_set, perceptrons)

# testing phase
phase_testing(test_set, perceptrons)