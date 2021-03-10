import lightrdf

word = str(input()).lower()

doc = lightrdf.RDFDocument("./CSO.3.2.owl")

for triple in doc.search_triples("http://www.co-ode.org/ontologies/ont.owl#" + word, None, None):
    print(triple[0])
    break
