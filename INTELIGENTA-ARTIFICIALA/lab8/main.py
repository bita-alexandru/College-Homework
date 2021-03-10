import unidecode
import numpy as np
import matplotlib.pyplot as plt
from sklearn.manifold import TSNE
from gensim.models import Word2Vec


EPOCHS = 10
HIDDEN = 10
MIU = 0.01


def read_input(filename):
    with open(filename) as fd:
        data = fd.read().lower()

    return unidecode.unidecode(data)


def preprocess_data(data):
    stopwords = read_input("english").split("\n")

    special_chars = [
        "`", "~", "@", "#", "$", "%", "^", "\n"
        "&", "*", "(", ")", "-", "_", "=",
        "+", "[", "{", "]", "}", "\\", "|",
        ":", "\"", ",", "<", ">", "/", "1",
        "2", "3", "4", "5", "6", "7", "8", "9", "0"
    ]
    final_chars = "!?;"

    data = list(data)
    for i in range(len(data)):
        c = data[i]
        if c in special_chars:
            data[i] = " "
        elif c in final_chars:
            data[i] = "."
    data = "".join(data)

    propositions = data.split(".")
    words = []

    unique = dict()
    
    all_propositions = []
    all_words = []

    for proposition in propositions:
        p = proposition.replace("\n", "").split(" ")

        context = [
            word for word in p if word not in stopwords
        ]

        all_propositions.append(context)

        for word in context:
            if word not in unique:
                unique[word] = True
                words.append(word)
            all_words.append(word)

    return words, all_propositions, all_words


def make_encoding(words):
    n = len(words)
    encoding = dict()

    for i in range(n):
        word = words[i]

        onehot = [0 for _ in range(n)]
        onehot[i] = 1

        encoding[word] = onehot

    return encoding


def make_context(word, propositions):
    context = []
    for proposition in propositions:
        if word in proposition:
            for w in proposition:
                if w != word and len(w) > 0:
                    context.append(w)

    return context


def make_trainset(encoding, word, context):
    trainset = []

    if word not in encoding:
        return None

    all_words = [word]
    all_words += context
    
    for w in all_words:
        onehot = encoding[w]
        trainset.append(onehot)

    return trainset

def softmax(u):
    e_x = np.exp(u - np.max(u)) 
    return e_x / e_x.sum()

def make_model(trainset, vocabulary):
    model = [0]

    x = np.array(trainset[0])
    o = np.array(trainset[0:])

    w = np.array(
        [
            [vocabulary[word] for word in vocabulary]
            for _ in range(HIDDEN)
        ]
    )

    w_p = np.random.uniform(-0.1, 1.0, (HIDDEN, len(vocabulary))) 

    h = np.dot(np.transpose(x), w)
    u = np.dot(np.transpose(w_p), h)
    y = softmax(u)

    # err = np.array(
    #     [
    #         u[i] - o[i] for i in range(len(u)) if vocabulary[list(vocabulary.keys())[i]] == list(o[i])
    #     ]
    # )
    # print(err)
    # grd_wp = np.array(
    #     [
    #         np.dot(err[i], h[i]) for i in range(len(o))
    #     ]
    # )

    # print(np.shape(grd_wp))

    return model


def compute_similarity(model, encoding):
    model.sort()
    best = model[-1]

    for key in encoding:
        if encoding[key] == best:
            print(key)
            return


def main():
    train_data = read_input("train_data.txt")
    words, propositions, all_words = preprocess_data(train_data)

    encoding = make_encoding(words)

    test_data = read_input("test_data.txt")
    test_words, tmp1, tmp2 = preprocess_data(test_data)

    # model = Word2Vec(propositions, min_count=1)

    all_onehots = []
    for w in encoding:
        all_onehots.append(encoding[w])
    
    # tsne = TSNE().fit(all_words)

    # plt.plot(tsne)
    # plt.show()

    # for word in test_words:
    #     print(word)
    #     print(model.wv.most_similar(word, topn=3))

    # for word in test_words:
    #     context = make_context(word, propositions)
    #     trainset = make_trainset(encoding, word, context)

    #     if trainset == None:
    #         print(word + " has no similar words in the vocabulary.")
    #         continue
        
    #     model = make_model(trainset, encoding)
    #     compute_similarity(model, encoding)


main()
