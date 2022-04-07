import numpy as np
import random
import operator
import pandas as pd
import matplotlib.pyplot as plt
import networkx as nx
import math


class Calculo:                       ################################################################################
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def Dis_Euc(self, calculo):     ################################################################################
        xDis = abs(self.x - calculo.x)
        yDis = abs(self.y - calculo.y)

        Dis_Euc = (xDis ** 2) + (yDis ** 2)
        Dis_Euc = np.sqrt(Dis_Euc)
        return Dis_Euc

    def __repr__(self):             ################################################################################
        return "(" + str(self.x) + "," + str(self.y) + ")"


class Fitness:
    def __init__(self, route):
        self.route = route
        self.Dis_Euc = 0
        self.fitness = 0.0

        
    def Cal_Rut(self):              ################################################################################
        if self.Dis_Euc == 0:
            camino = 0
            for i in range(0, len(self.route)):
                x = self.route[i]
                y = None
                if i + 1 < len(self.route):
                    y = self.route[i + 1]
                else:
                    y = self.route[0]
                camino += x.Dis_Euc(y)

            self.Dis_Euc = camino
        return self.Dis_Euc

    def routeFitness(self):
        if self.fitness == 0:
            self.fitness = 1 / float(self.Cal_Rut())
        return self.fitness


def Crear_Rut(lista):               ################################################################################
    route = random.sample(lista, len(lista))

    return route


def Original(popSize, lista):       ################################################################################
    population = []
    for i in range(0, popSize):
        population.append(Crear_Rut(lista))
    global firstEverRoute
    firstEverRoute = population[popSize - 1]
    return population


def Ranking(population):            ################################################################################
    Fresult = {}
    for i in range(0, len(population)):
        Fresult[i] = Fitness(population[i]).routeFitness()
    return sorted(Fresult.items(), key=operator.itemgetter(1), reverse=True)


def Elegir(popRanked, TamE):
    Sresult = []
    df = pd.DataFrame(np.array(popRanked), columns=["Idx", "Fitness"])
    df['cum_sum'] = df.Fitness.cumsum()
    df['cum_perc'] = 100 * df.cum_sum / df.Fitness.sum()
    for i in range(0, TamE):
        Sresult.append(popRanked[i][0])
    for i in range(0, len(popRanked) - TamE):
        pick = 100 * random.random()
        for i in range(0, len(popRanked)):
            if pick <= df.iat[i, 3]:
                Sresult.append(popRanked[i][0])
                break
    return Sresult


def Final(population, Sresult):         ################################################################################
    matingpool = []
    for i in range(0, len(Sresult)):
        temp = Sresult[i]
        matingpool.append(population[temp])
    return matingpool


def Crusando(Padre1, Padre2):         ################################################################################
    Hijo = []
    HijoP1 = []
    HijoP2 = []
    A = int(random.random() * len(Padre1))
    B = int(random.random() * len(Padre1))
    ini = min(A, B)
    fin = max(A, B)
    for i in range(ini, fin):
        HijoP1.append(Padre1[i])
    HijoP2 = [item for item in Padre2 if item not in HijoP1]
    Hijo = HijoP1 + HijoP2
    return Hijo


def Crusando_Pue(matingpool, TamE):     ################################################################################
    Hijos = []
    length = len(matingpool) - TamE
    pool = random.sample(matingpool, len(matingpool))
    for i in range(0, TamE):
        Hijos.append(matingpool[i])
    for i in range(0, length):
        Hijo = Crusando(pool[i], pool[len(matingpool) - i - 1])
        Hijos.append(Hijo)
    return Hijos


def Mescla(individual, mutationRate):   ################################################################################
    for aux1 in range(len(individual)):
        if (random.random() < mutationRate):
            aux2 = int(random.random() * len(individual))
            c1 = individual[aux1]
            c2 = individual[aux2]
            individual[aux1] = c2
            individual[aux2] = c1
    return individual


def Mescla_Pueblo(population, mutationRate):  ################################################################################
    mutatedPop = []
    for ind in range(0, len(population)):
        mutatedInd = Mescla(population[ind], mutationRate)
        mutatedPop.append(mutatedInd)
    return mutatedPop


def NextG(currentGen, TamE, mutationRate):
    popRanked = Ranking(currentGen)
    Sresult = Elegir(popRanked, TamE)
    matingpool = Final(currentGen, Sresult)
    Hijos = Crusando_Pue(matingpool, TamE)
    NextG = Mescla_Pueblo(Hijos, mutationRate)
    return NextG


def GA(population, popSize, TamE, mutationRate, generations):
    pop = Original(popSize, population)
    Progreso = []
    MejorR = []
    Mejor_Dis_Eu = math.inf
    Progreso.append(1 / Ranking(pop)[0][1])
    for i in range(0, generations):
        pop = NextG(pop, TamE, mutationRate)
        Actual_Eu = 1 / Ranking(pop)[0][1]
        Progreso.append(Actual_Eu)
        if (Mejor_Dis_Eu == math.inf or Actual_Eu < Mejor_Dis_Eu):
            MejorR = pop[Ranking(pop)[0][0]]
    # print(Progreso[0])
    plt.figure()
    plt.plot(Progreso)
    plt.ylabel('Distancia')
    plt.xlabel('Generacion')
    # MejorR = pop[Ranking(pop)[0][0]]
    return MejorR


########################################## main ################################################################
lista = []
edge_colors = []
positions = []
nroCities = 5

G = nx.Graph()
for i in range(0, nroCities):
    lista.append(Calculo(x=int(random.random() * 200), y=int(random.random() * 200)))
    x = lista[i].x
    y = lista[i].y
    positions.append((x, y))

G.add_nodes_from(lista)
MejorR = GA(population=lista, popSize=80, TamE=20, mutationRate=0.10, generations=500)
MejorR.append(MejorR[0])

for i in range(0, nroCities):
    for j in range(0, nroCities):
        edge_colors.append('b')
        G.add_edge(lista[i], lista[j])

Pesos = nx.get_edge_attributes(G, 'weight').values()
plt.figure(2)
nx.draw(G, edge_color=edge_colors)
plt.show()

for i in range(0, nroCities):
    x = MejorR[i].x
    y = MejorR[i].y
    x_2 = MejorR[i + 1].x
    y_2 = MejorR[i + 1].y
    print("Route: (", x, ",", y, ")->(", x_2, ",", y_2, ")")