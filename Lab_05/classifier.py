

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
import random


def delete_random_elems(input_list, n):
    to_delete = set(random.sample(range(len(input_list)), n))
    return [x for i,x in enumerate(input_list) if  i in to_delete]



def NaiveBayesianClassifier(columns , trainingRate , fileName ,registersNum):

    #read file
    dataset = pd.read_csv(fileName , sep = ',', header = None , names= columns)

    # print("\nDataSet:\n %s \n" % dataset.to_string())

    #delete
    # dataset.drop(dataset.index[dataset[columns[-1]] == 'unacc'], inplace=True)
    # dataset.drop(dataset.index[dataset[columns[-1]] == 'acc'], inplace=True)

    #standardize registers
    classes = dataset.clase.unique() #clases


    for clase in classes:
        indexRegisters = dataset.index[dataset[columns[-1]] == clase ].tolist()
        indexRegisters = delete_random_elems(indexRegisters,len(indexRegisters) - registersNum)
        dataset = dataset.drop(indexRegisters)

    print("\nnew DataSet:\n %s \n" % dataset.to_string())


    # Separate dataset for trainig and testing
    x = dataset.values
    classes = dataset.clase.unique() #clases

    x_train , x_test = train_test_split(x,test_size= 1-trainingRate )
    train_df = pd.DataFrame(x_train,columns= columns)
    test_df = pd.DataFrame(x_test,columns= columns)

    print("\nTrainSet:\n %s \n" % train_df.to_string())
    print("\nTestSet:\n %s \n" % test_df.to_string())


    #fill with initial probabilities
    Pclass = [0]*len(classes)

    Dictclass =  train_df.pivot_table(columns = columns[-1],aggfunc='size').to_dict()
    for i in range(len(classes)):
        Pclass[i] = Dictclass[classes[i]] / len(train_df)

    print(classes)
    # print(Pclass)

    #trainig

    precision = 0
    for register in  x_test :
        P = Pclass.copy()
        for a in range(len(register)-1):
            for c in range(len(classes)):
                data = train_df.pivot_table(columns=[columns[a],columns[-1]],aggfunc='size')
                # print("\n\n %s" % data.to_string())
                # print(" registro : %s" % register[a])
                # print(" class : %s" % classes[c])
                data = data.to_dict()
                # print(data)
                key = (register[a],classes[c])
                if key  in data:
                    # print(data[(register[a], classes[c])] / (Pclass[c] * len(train_df)))
                    P[c]  *= data[(register[a], classes[c])] / (Pclass[c] * len(train_df))
                    # print(P[c])

        print(P)
        max_index = P.index(max(P))

        if( register[-1] == classes[max_index]):
            precision += 1*100 / len(test_df)
            print("acerto")



    print("precision: %i %%" % int(precision))
    return precision


def ProveNBC(columns,trainRate,fileName,registersNum,iter):
    res = 0
    for i in range(iter):
        res += NaiveBayesianClassifier(columns, trainRate, fileName, registersNum)

    print("\nAverage precision: %1f %%" % (res / iter))
    return res/iter

########################################## main ###################################


# columns = ["tiempo","temperatura","humedad","viento","clase"]
# trainRate = 0.8
# fileName = 'example.csv'
# registersNum = 4

columns = ["buying","maint","doors","persons","lug_boot","safety","clase"]
trainRate = 0.8
fileName = "carData.csv"
registersNum = 65
iter = 10


ProveNBC(columns, trainRate, fileName, registersNum,iter)



