from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
import unidecode
import json

stop_words = set([unidecode.unidecode(w) for w in stopwords.words("romanian")])

def make_model(filename, modelname, norm):
    with open(filename) as fd:
        text = fd.read().lower()

    text = unidecode.unidecode(text)
    word_tokens = word_tokenize(text)  
    
    special_chars = ["-", ",", ";", ":", "?", "!", "\"", "`", "(", ")", "[", "]", "{", "}", ".", "„", "”", "\/"]
    filtered_text = [w for w in word_tokens if not w in stop_words and w not in special_chars]

    freq = dict()
    total = 0

    for word in filtered_text:     
        if word not in freq:
            freq[word] = 1
        else:
            freq[word] += 1
        
        total += 1

    for word in freq:
        freq[word] = round(freq[word]/total * norm)

    with open(modelname, "w") as out: 
        json.dump(freq, out)

def compute_similitude(model1, model2):
    with open(model1) as json_file: 
        m1 = json.load(json_file)
    
    with open(model2) as json_file: 
        m2 = json.load(json_file) 
  
    similitude = 0

    for word in m1:
        diff = int(m1[word])

        if word in m2:
            diff = abs(int(m1[word]) - int(m2[word]))

        similitude += diff

    avg_diff = similitude / len(m1)
    
    print("similitude: " + str(similitude))
    print("avg. difference: " + str(avg_diff))

make_model("m1.txt", "m1.json", 1000000)
make_model("m2.txt", "m2.json", 1000)

compute_similitude("m1.json", "m2.json")
