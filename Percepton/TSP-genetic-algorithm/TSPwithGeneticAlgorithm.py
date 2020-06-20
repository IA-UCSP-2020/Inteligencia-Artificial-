# -*- coding: utf-8 -*-
"""
Created on Mon May 25 13:06:40 2020

@author: Saul Rojas
"""

import matplotlib.pyplot as plt
import numpy as np
import math
import random

###############################################################################
# Global Data Information
Iterations = 20000
BestSpecimenPathDistance_x = list(range(Iterations))
BestSpecimenPathDistance_y = []
MediaSpecimenPathDistance_x = list(range(Iterations))
MediaSpecimenPathDistance_y = []



# Global Genetic Variables

# la tabla con los datos esperados
TableData = {
    "Population": [],# la poblacion de esta generación
    "Distances": [],# las distancias de esta generación
    "ProportionalFitness": [], # el valor de aptitud porporcional
    "ExpectedValues": [],
    "ActualValues": [],
    "SumDistances": 0, # la suma total de distancias
    "MediaDistances": 0, # la media de esas distancias
    "BestPath": [], # el mejor camino de cada población
    "BestPathDistance": 0 # la distancia de ese mejor camino
}

Cities = [];
TotalCities = 10

# es muy importante que la cantidad de la población sea siempre par
PopSize = 20
# la población inicial
Population = []

# el tamaño de mi mapa
width = 600
height = 600
###############################################################################

# una función para mostrar la tabla de datos
def ShowTable():
    print("Sum of Distances: %.2f " % TableData["SumDistances"])
    print("Media of Distances: %.2f " % TableData["MediaDistances"])
    print("Best Path: {}".format(TableData["BestPath"]))
    print("BestPathDistance %.2f" % TableData["BestPathDistance"])
    #print("       Population         Distances          Fitness          Expected Value      Actual Value")
    for i in range(len(TableData["Population"])):
        string = "{} {} {} {} {}".format(TableData["Population"][i], round(TableData["Distances"][i], 3), round(TableData["ProportionalFitness"][i], 3), round(TableData["ExpectedValues"][i], 3), TableData["ActualValues"][i])
        print(string)
        
def ShowMap(Cities, Order):
    x_axis = []
    y_axis = []
    for i in range(len(Order)):
        idx = Order[i]
        x_axis.append(Cities[idx]["x"])
        y_axis.append(Cities[idx]["y"])
    
    StartCityidx = Order[0]
    StartCity = Cities[StartCityidx]
    x_axis.append(StartCity["x"])
    y_axis.append(StartCity["y"])
    plt.plot(x_axis, y_axis, 'ro', x_axis, y_axis, "-b", [StartCity["x"]], [StartCity["y"]], "go")
    plt.show()


# calcula la distancia de distintas ciudades en un camino, dado un orden específico
def CalcPathDistance(Cities, Order):
    Distance = 0
    CityAidx = 0
    CityA = 0
    CityBidx = 0
    CityB = 0
    for i in range(len(Order) - 1):
        CityAidx = Order[i]
        CityA = Cities[CityAidx]
        CityBidx = Order[i + 1]
        CityB = Cities[CityBidx]
        Distance += math.hypot(abs(CityA["x"] - CityB["x"]), abs(CityA["y"] - CityB["y"]))
        
        
    CityAidx = Order[0] # starting city
    CityA = Cities[CityAidx]
    CityBidx = Order[len(Order) - 1] # last city
    CityB = Cities[CityBidx]
    Distance += math.hypot(abs(CityA["x"] - CityB["x"]), abs(CityA["y"] - CityB["y"]))
        
    return Distance

# el cruzameinto CrossOver
# both parents are lists with the same size
def CrossOver(Parent1, Parent2):
    size = len(Parent1)
    Filius1 = [-1] * size
    Filius2 = [-1] * size
    # primero escogemos al azar posiciones aleatorias de ambos padres y lo copiamos en los hijos
    for i in range(size):
        if np.random.rand() < 0.2:
            Filius1[i] = Parent2[i]
        if np.random.rand() < 0.2:
            Filius2[i] = Parent1[i]
    
    i = 0 # el iterador para los hijos del padre
    j = 0 # el iterador para el primer hijo
    k = 0 # el iterador para el segundo hijo
    while i < size:
        if Parent1[i] not in Filius1:
            while Filius1[j] != -1 and j < size:
                j += 1
            Filius1[j] = Parent1[i]
        if Parent2[i] not in Filius2:
            while Filius2[k] != -1 and k < size:
                k += 1
            Filius2[k] = Parent2[i]
        i += 1
    
    return [Filius1, Filius2]
    
def MutationByPos(Child):
    # different mutation algorithms i will use the mutation based on position
    idx1 = np.random.randint(low = 0, high= len(Child))
    idx2 = np.random.randint(low = 0, high= len(Child))
    temp = Child[idx1]
    Child[idx1] = Child[idx2]
    Child[idx2] = temp
    return Child
    
# realizeremos la selección de los mejores especimenes de la población
# segun su valor de aptitud
#def Selection(Fitness):
#    MaxFitness = -1
#    MaxFitnessIdx = 0
#    for i in range(PopSize):
#        if Fitness[i] > MaxFitness:
#            MaxFitnessIdx = i
#            MaxFitness = Fitness[i]
#    return TableData["Population"][MaxFitnessIdx]

def CalculateData():
    Distances = []
    ProportionalFitness = []
    ExpectedValues = []
    ActualValues = []
    SumDistances = 0
    MediaDistances = 0
    BestPath = TableData["Population"][0] ## por defecto el mejor path será el primero de la población
    RecordDistance = TableData["BestPathDistance"] ## la mejor distancia será el primer camino
    #print(TableData["Population"])
    for i in range(PopSize):
        d = CalcPathDistance(Cities, TableData["Population"][i]) # calculamos la distancia de este camino
        Distances.append(d) # lo agregamos a nuestra lista de Distancias la distancia recibida
        SumDistances = SumDistances + d
        if d < RecordDistance: # hay una mejor distancia
            RecordDistance = d
            BestPath = Population[i]
            
    MediaDistances = SumDistances / PopSize # calculamos la distancia media
    
    for i in range(PopSize):
        Distances.append(d) # lo agregamos a nuestra lista de columnas
        ProportionalFitness.append(1 / (1 + Distances[i])) # la medidad de esa distancia sobre la sum total
        ExpectedValues.append(MediaDistances / Distances[i]) # mientras mas pequeña sea la distancia, mayor será este valor
        ActualValues.append(math.floor(ExpectedValues[i])) # redondeamos los valores
    
    SumFitness = sum(ProportionalFitness)
    # vamos a normalizar las aptitudes
    for i in range(PopSize):
        ProportionalFitness[i] = ProportionalFitness[i] / SumFitness
    
    # colocando todos los datos obtenidos en la tabla
    TableData["Distances"] = Distances
    TableData["ProportionalFitness"] = ProportionalFitness
    TableData["ExpectedValues"] = ExpectedValues
    TableData["ActualValues"] = ActualValues
    TableData["SumDistances"] = SumDistances
    TableData["MediaDistances"] = MediaDistances
    TableData["BestPath"] = BestPath
    TableData["BestPathDistance"] = RecordDistance
    

def GenerateNewPopulation():
    # de la lista ActualValues,obtendremos una segunda lista, que ocntendrá a los padres
    Parents = []
    Children = []
    for i in range(PopSize):
        for j in range(TableData["ActualValues"][i]):
            # una lista de pares dos padres
            Parents.append(TableData["Population"][i])
    
    # si no hay una cantidad suficiente de padres, lo que hacemos es escoger al mejor especimen de la camada
    while len(Parents) < PopSize:
        # realizamos la selección del mejor especímen segun su aptitud
        Parents.append(TableData["BestPath"])
    while len(Parents) > PopSize:
        Parents.pop() # vamos eliminando el último elemento de la lista para no tener una sobre poblacion
    
    # empezamos el cruzamiento
    for i in range(0, PopSize, 2):
        # usaremos el cruzamiento CrossOver
        Childs = CrossOver(Parents[i], Parents[i+1])
        #print("CHILDs: ", Childs)
        if np.random.rand() < 0.1: # aqui se genera la mutacion, si hay alguna
            idx = np.random.randint(low=0,high=2) # 0,1, the first or second child
            Childs[idx] = MutationByPos(Childs[idx])
        #print("CHILDs: ", Childs)
        Children.append(Childs[0])
        Children.append(Childs[1])
        
    #print(Children)
    TableData["Population"] = Children
    #print("nueva poblacion", TableData["Population"])    
    
# necesitamos mezclar posiciones iniciales de los distintos caminos
# este array order tendrá un alista de números desde 0 hasta totalCities-1
Order = []
# creamos las ciudades, inicializando las posiciones de las ciudades
# setup
for i in range(TotalCities):
    Cities.append({
            "x": np.random.randint(width),
            "y": np.random.randint(height)
            })
    Order.append(i)
# creamos la población inicial de nuestro TSP, inicialmente serán 10
for i in range(PopSize):
    # copiamos order a cada una de las posiciones de population, pero con las posiciones mezcladas
    Population.append(random.sample(Order, len(Order)))



# Calculamos la mejor distancia inicial
TableData["BestPath"] = Population[0]
FirstRecordDistance = math.inf
for i in range(1, PopSize):
    d = CalcPathDistance(Cities, Population[i]) # calculamos la distancia de este camino
    if d < FirstRecordDistance: # hay una mejor distancia
        FirstRecordDistance = d
        TableData["BestPath"] = Population[i]

# estableciendo la población inicial
TableData["Population"] = Population
TableData["BestPathDistance"] = CalcPathDistance(Cities, Population[0])



print("# Cities: ", TotalCities)
print("# Iterations: ", Iterations)
print("# Population: ", PopSize)

print("Primer mejor especimen: ")      
ShowMap(Cities, TableData["BestPath"])

print()
for i in range(Iterations):
    CalculateData() # calculamos los datos relevantes para el problema, ahora estamos listos para generar la nueva población
    # adding BestPathDistance and MediaPathDistance to the graph
    BestSpecimenPathDistance_y.append(TableData["BestPathDistance"])
    MediaSpecimenPathDistance_y.append(TableData["MediaDistances"])
    # Showing some individuals paths
    if i == 6666 or i == 9999 or i == 13332 or i == 16665:
        print("Mejor especimen en la iteracion: ", i)
        print("Distancia del mejor espécimen: ", TableData["BestPathDistance"])
        ShowMap(Cities, TableData["BestPath"])
    #####################################
    GenerateNewPopulation() #generamos la nueva población con los datos recibidos, aqui realizamos la mutación y el cruzamiento 

    
print("Mejor espécimen después de aplicar el algoritmo genético: ")      
print("Distancia del mejor espécimen después de aplicar el algoritmo genético: ", TableData["BestPathDistance"])
ShowMap(Cities, TableData["BestPath"])


# Mostramos la vista de los datos
plt.xlabel("# Iterations")
plt.ylabel("Distance")
plt.plot(BestSpecimenPathDistance_x, BestSpecimenPathDistance_y, '-.r', MediaSpecimenPathDistance_x, MediaSpecimenPathDistance_y, "--g")
plt.legend(['Best Path Distance', 'Media Path Distances'])
plt.show()

