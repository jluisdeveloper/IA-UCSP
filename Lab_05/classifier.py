

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split



########################################## main ###################################


columns = ["tiempo","temperatura","humedad","viento","jugar"]
dataset = pd.read_csv('example.csv' , sep = ',', header = None , names= columns)

# clima = dataset.iloc[:,0].values
# dups_clima = dataset.pivot_table(columns=['tiempo','jugar'],aggfunc='size')

print("\nDataSet:\n %s \n" % dataset.to_string())

# Separate dataset for trainig and testing
x = dataset.values

x_train , x_test = train_test_split(x,test_size=2 )
train_df = pd.DataFrame(x_train,columns= columns)
test_df = pd.DataFrame(x_test,columns= columns)

print("\nTrainSet:\n %s \n" % train_df.to_string())
print("\nTestSet:\n %s \n" % test_df.to_string())


#trainig

classes = dataset.jugar.unique()



#fill with initial probabilities

Pclass = [0]*len(classes)


Dictclass =  train_df.pivot_table(columns = columns[-1],aggfunc='size').to_dict()
for i in range(len(classes)):
    Pclass[i] = Dictclass[classes[i]] / len(train_df)

print(Dictclass)
print(classes)
print(Pclass)

#trainig

precision = 0


for register in  x_test :
    P = Pclass.copy()
    for a in range(len(register)-1):
        for c in range(len(classes)):
            data = train_df.pivot_table(columns=[columns[a],columns[-1]],aggfunc='size')
            print("\n\n %s" % data.to_string())
            print(" registro : %s" % register[a])
            print(" class : %s" % classes[c])
            data = data.to_dict()
            # print(data)
            key = (register[a],classes[c])
            if key  in data:
                print(data[(register[a], classes[c])] / (Pclass[c] * len(train_df)))
                P[c]  *= data[(register[a], classes[c])] / (Pclass[c] * len(train_df))
                print(P[c])

    print(P)
    max_index = P.index(max(P))

    if( register[-1] == classes[max_index]):
        precision += 1*100 / len(test_df)



# print(precision)

print("precision: %i %%" % int(precision))







