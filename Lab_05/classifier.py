

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

x_train , x_test = train_test_split(x,test_size=0.20 , random_state=6)
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
    Pclass[i] = Dictclass[classes[i]]

#trainig

for register in


print(Dictclass)
print(classes)
print(Pclass)




#count si/no

# P = train_df.pivot_table(columns=['jugar'],aggfunc='size').to_dict()
#
# Psi = P["si"]
# Pno = P["no"]
#
# #contamos los de dobles
#
# print(Psi)
# print(Pno)

# for register in  x_test :
#     for attribute in register:
#         print(attribute)
#









#
# print("\n")
#
# print(dups_clima)
#
# print("\n")
#
# print(dups_clima.to_dict())
#
# print("\n")
#
# print(dups_clima.to_dict()[("sol","no")])
# # print(dups_clima['tiempo'].to_numpy())




