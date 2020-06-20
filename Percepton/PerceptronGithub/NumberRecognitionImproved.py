# -*- coding: utf-8 -*-
"""
Created on Wed Jun 10 22:16:51 2020

@author: Saul Rojas
"""


import numpy as np
import random
from PIL import Image 

###############################################################################
######################## Global Variables #####################################
ImgWidth = 7
ImgHeigth = 10
Zero = np.array([[1,0,0,0,0,0,0,0,0,0]]).T
One = np.array([[0,1,0,0,0,0,0,0,0,0]]).T
Two = np.array([[0,0,1,0,0,0,0,0,0,0]]).T
Three = np.array([[0,0,0,1,0,0,0,0,0,0]]).T
Four = np.array([[0,0,0,0,1,0,0,0,0,0]]).T
Five = np.array([[0,0,0,0,0,1,0,0,0,0]]).T
Six = np.array([[0,0,0,0,0,0,1,0,0,0]]).T
Seven = np.array([[0,0,0,0,0,0,0,1,0,0]]).T
Eigth = np.array([[0,0,0,0,0,0,0,0,1,0]]).T
Nine = np.array([[0,0,0,0,0,0,0,0,0,1]]).T

ImgSources = [("Cero/cero1.bmp", Zero),("Cero/cero2.bmp", Zero),
              ("Cero/cero3.bmp", Zero),("Cero/cero4.bmp", Zero),
              ("Uno/uno1.bmp", One),("Uno/uno2.bmp", One),
              ("Uno/uno3.bmp", One),("Uno/uno4.bmp", One),
              ("Uno/uno5.bmp", One),("Uno/uno6.bmp", One),
              ("Uno/uno7.bmp", One),("Uno/uno8.bmp", One),
              ("Uno/uno9.bmp", One),("Uno/uno10.bmp", One),
              ("Uno/uno11.bmp", One),("Uno/uno12.bmp", One),
              ("Uno/uno13.bmp", One),("Uno/uno14.bmp", One),
              ("Dos/dos1.bmp", Two),("Dos/dos2.bmp", Two),
              ("Dos/dos3.bmp", Two),("Dos/dos4.bmp", Two),
              ("Dos/dos5.bmp", Two),("Dos/dos6.bmp", Two),
              ("Dos/dos7.bmp", Two),("Dos/dos8.bmp", Two),
              ("Tres/tres1.bmp", Three),("Tres/tres2.bmp", Three),
              ("Tres/tres3.bmp", Three),("Tres/tres4.bmp", Three),
              ("Tres/tres5.bmp", Three),("Tres/tres6.bmp", Three),
              ("Tres/tres7.bmp", Three),("Tres/tres8.bmp", Three),
              ("Tres/tres9.bmp", Three),("Tres/tres10.bmp", Three),
              ("Cuatro/cuatro1.bmp", Four),("Cuatro/cuatro2.bmp", Four),
              ("Cuatro/cuatro3.bmp", Four),("Cuatro/cuatro4.bmp", Four),
              ("Cuatro/cuatro5.bmp", Four),("Cuatro/cuatro6.bmp", Four),
              ("Cuatro/cuatro7.bmp", Four),("Cuatro/cuatro8.bmp", Four),
              ("Cinco/cinco1.bmp", Five),("Cinco/cinco2.bmp", Five),
              ("Cinco/cinco3.bmp", Five),("Cinco/cinco4.bmp", Five),
              ("Cinco/cinco5.bmp", Five),("Cinco/cinco6.bmp", Five),
              ("Cinco/cinco7.bmp", Five),("Cinco/cinco8.bmp", Five),
              ("Seis/seis1.bmp", Six),("Seis/seis2.bmp", Six),
              ("Seis/seis3.bmp", Six),("Seis/seis4.bmp", Six),
              ("Seis/seis5.bmp", Six),("Seis/seis6.bmp", Six),
              ("Seis/seis7.bmp", Six),("Seis/seis8.bmp", Six),
              ("Seis/seis9.bmp", Six),("Seis/seis10.bmp", Six),
              ("Seis/seis11.bmp", Six),("Seis/seis12.bmp", Six),
              ("Siete/siete1.bmp", Seven),("Siete/siete2.bmp", Seven),
              ("Siete/siete3.bmp", Seven),("Siete/siete4.bmp", Seven),
              ("Ocho/ocho1.bmp", Eigth),("Ocho/ocho2.bmp", Eigth),
              ("Ocho/ocho3.bmp", Eigth),("Ocho/ocho4.bmp", Eigth),
              ("Ocho/ocho5.bmp", Eigth),("Ocho/ocho6.bmp", Eigth),
              ("Ocho/ocho7.bmp", Eigth),("Ocho/ocho8.bmp", Eigth),
              ("Nueve/nueve1.bmp", Nine),("Nueve/nueve2.bmp", Nine),
              ("Nueve/nueve3.bmp", Nine),("Nueve/nueve4.bmp", Nine),
              ("Nueve/nueve5.bmp", Nine),("Nueve/nueve6.bmp", Nine)]

ISize = len(ImgSources) # the size of the inputs
###############################################################################
#########################Some Important FUnctions############################## 
def ImageGetEntry(image_src):
    ImageData = []
    try: 
        #relative Path
        img = Image.open(image_src)
        
        ImageData = list(img.getdata())
        #print(ImageData)
        for i in range(len(ImageData)):
            s = sum(ImageData[i])
            if s != 0:
                ImageData[i] = 0
            else:
                ImageData[i] = 1
        return np.array([ImageData]).T
    except IOError: 
        pass
    return np.array(0)    

def viewBitmap(image_src):
    ImageData = []
    try: 
        #relative Path
        img = Image.open(image_src)
        
        ImageData = list(img.getdata())
        #print(ImageData)
        for i in range(len(ImageData)):
            s = sum(ImageData[i])
            if s != 0:
                ImageData[i] = 0
            else:
                ImageData[i] = 1
        print(ImageData[0:7])
        print(ImageData[7:14])
        print(ImageData[14:21])
        print(ImageData[21:28])
        print(ImageData[28:35])
        print(ImageData[35:42])
        print(ImageData[42:49])
        print(ImageData[49:56])
        print(ImageData[56:63])
        print(ImageData[63:70])
    except IOError: 
        pass
    
    
# recibimos un vector columna de numpy, y lo convertimos
# en una matriz n diagonal, donde n es el tamaño del vector, y cada entrada 
# diagonal de la matriz contiene el iésimo dato del array
def Diagonal(v):
    I = np.eye(v.size)
    for i in range(v.size):
        I[i][i] = v[i][0]
    return I
###############################################################################
#########################The NeuralNetwork#####################################
class NeuralNetwork:
    
    def __init__(self, NeuronsKind, Etha):
        self.NeuronsKind = NeuronsKind
        self.etha = Etha
        self.a = np.array(0) # the inputs vector
        self.d = np.array(0) # the result vector
        self.W = np.zeros((NeuronsKind, ImgWidth*ImgHeigth)) # the weigths matrix
        self.w = np.zeros((NeuronsKind, 1))
    
    def Ru(self, x):
        return max(x,0)
        #return 0 if x <= 0 else 1
    
    def GetResult(self, d):
        d = d.T
        idx_max = np.argmax(d)
        if idx_max >= self.NeuronsKind:
            return self.NeuronsKind - 1
        return idx_max
        
    
    def train(self, Entry, Result):
        self.a = Entry
        self.d = Result
        vRu = np.vectorize(self.Ru) # la función que me permitira evaluar Ru
        # y es el resultado de esa entrada
        y = (self.W @ self.a) + self.w # no self.b * self.w, because the biases always are 1
        #print(self.GetResult(vRu(y)), self.GetResult(self.d))
        if self.GetResult(vRu(y)) != self.GetResult(self.d): # si la salida no es igual a la esperada, hay error
            A = np.ones((self.NeuronsKind, ImgWidth*ImgHeigth))
            for i in range(self.NeuronsKind):
                A[i] = self.a.T
            L = self.etha * (Diagonal(self.d - y) @ A) # esta es la matriz que
            self.W = self.W + L # y actualizamos nuestra matriz de pesos
            self.w = self.w + (self.etha * (self.d - y)) # los mismo hacemos para los pesos de nustros bias
            return False # indicamos que la salida tuvo error
        return True # si no hubo error
    
    # esta función me devolverá el resultado de los datos de la imagen que le enviemos
    def ProveNetwork(self, Entry):
        self.a = Entry
        vRu = np.vectorize(self.Ru) # la función que me permitira evaluar Ru
        y = (self.W @ self.a) + self.w # el resultado
        return self.GetResult(vRu(y)) # retornamos el valor de la imagen, [0-1]
    
    
    
class Train:
    def __init__(self):
        self.Tests = []
        self.NeuronsKind = 10
        self.etha = 0.001
        for i in range(ISize):
            self.Tests.append((ImageGetEntry(ImgSources[i][0]), ImgSources[i][1]))
        self.NeuralNet = NeuralNetwork(self.NeuronsKind, self.etha)

            
        self.trained = False # a boolean variable that will tell us if the neural network was trained
        
    def train_epoch(self):
        NewTests = self.Tests[:]
        random.shuffle(NewTests)
        SuccessTrain = True # una variable que me indicará si toda la época de entrenamiento salió como lo esperábamos
        for i in range(ISize):
            flag = self.NeuralNet.train(NewTests[i][0], NewTests[i][1])
            SuccessTrain = SuccessTrain and flag
        self.trained = SuccessTrain
        #print(self.trained)



trainer = Train()

for i in range(150):
    trainer.train_epoch()
    if trainer.trained: # si la red paso todos los tests salimos del bucle
        print("epoch passed successfully at iteration: ", i + 1)
        # algunas pruebas extra que hemos creado para probar la red
        while True:
            op = int(input("selecciona un número a probar: "))
            ImageSourceProve = "Cero/cero1prueba.bmp"
            if op == 0:
                ImageSourceProve = "Cero/cero1prueba.bmp"
            elif op == 1:
                ImageSourceProve = "Uno/uno1prueba.bmp"
            elif op == 2:
                ImageSourceProve = "Dos/dos1prueba.bmp"
            elif op == 3:
                ImageSourceProve = "Tres/tres1prueba.bmp"
            elif op == 4:
                ImageSourceProve = "Cuatro/cuatro1prueba.bmp"
            elif op == 5:
                ImageSourceProve = "Cinco/cinco1prueba.bmp"
            elif op == 6:
                ImageSourceProve = "Seis/seis1prueba.bmp"
            elif op == 7:
                ImageSourceProve = "Siete/siete1prueba.bmp"
            elif op == 8:
                ImageSourceProve = "Ocho/ocho1prueba.bmp"
            elif op == 9:
                ImageSourceProve = "Nueve/nueve1prueba.bmp"    
            else:
                break
        
            a = ImageGetEntry(ImageSourceProve)
            viewBitmap(ImageSourceProve)
            print("número reconocido: ", trainer.NeuralNet.ProveNetwork(a))
        
        break

if not trainer.trained:
    print("train session not passed correctly")






