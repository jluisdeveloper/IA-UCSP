# Clasificador Bayesiano Ingenuo 

## Requerimientos e instalación

- Instalar Python
- Instalar pip


```bash
apt-get -y install python3 
apt -y install python3-pip
pip install numpy
pip install pandas
pip install matplotlib
pip install random
pip install -U scikit-learn scipy matplotlib
```

## Caracteristicas del Programa

- Lee el archivo en formato csv
- realiza un estandarización de las clases
- realiza una seleccion aleatoria
- Divide la data para entrenamiento y test 
- Se determina el promedio deprecision 
- Puede trabajar con "n" clases


## Ejemplo 

Dada la siguiente tabla , se selecciona 80% para entrenamiento y 20% para test .
### Tabla inicial :
![image](https://user-images.githubusercontent.com/70419764/164953810-884ef054-e815-49d9-a0e6-0f7a27b4771c.png)

### Tabla de Entrenamiento :
![image](https://user-images.githubusercontent.com/70419764/164953866-10f727db-38d1-4f65-b495-b9c6488bde89.png)

### Tabla de Test :
![image](https://user-images.githubusercontent.com/70419764/164953893-a078e282-b08c-4f81-9f99-c7341f35c458.png)

## Pruebas

- Prueba con **2 clases (good,vgood)**  con 65 registros cada uno , y 10 iteraciones .

```python
columns = ["buying","maint","doors","persons","lug_boot","safety","clase"]
trainRate = 0.8
fileName = "carData.csv"
registersNum = 65
iter = 10

ProveNBC(columns, trainRate, fileName, registersNum,iter)
```

![image](https://user-images.githubusercontent.com/70419764/164953699-af4a78b9-57c8-4dfc-9b40-3f7aa240afe0.png)

- Prueba con **4 clases (good,vgood,unacc,acc)**  con 65 registros cada uno , y 10 iteraciones .

```python
columns = ["buying","maint","doors","persons","lug_boot","safety","clase"]
trainRate = 0.8
fileName = "carData.csv"
registersNum = 65
iter = 10

ProveNBC(columns, trainRate, fileName, registersNum,iter)
```

![image](https://user-images.githubusercontent.com/70419764/164953769-e0c170a8-019a-43f8-8d0a-b02d82ea07f6.png)

## Gráficas

- Se incluye una gráfica de la precision de las distintas clases

![image](https://user-images.githubusercontent.com/70419764/165195207-91ac0a52-3bf0-461a-98f5-9bfae9ed0622.png)
