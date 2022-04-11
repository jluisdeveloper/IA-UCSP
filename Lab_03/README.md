# Laboratorio Algoritmos Genéticos

## Requerimientos e instalación

- Instalar Python
- Instalar pip

```bash
apt-get -y install python3 
apt -y install python3-pip
pip install numpy
pip install pandas
pip install matplotlib
pip install networkx
pip install scpy
```
## Caracteristicas del Programa

- Crea una lista de ciudades aleaoria
- Crea el numero de población
- Determina el fitness promedio por generación
- Selecciona por Elitismo y ruleta de probabilidades
- Porcentaje de Mutación 
- Número de generaciones

## Demo

Prueba con 100 individuos por generación, manteniendo 20 individuos
por elitismo , usando 1% de mutación , a través de 50 generaciones

```python
lenCiudades = 14
poblacion = 100
elitismo = 20
mutacionRate = 0.01
generaciones = 50

GA(lenCiudades , poblacion, elitismo,mutacionRate , generaciones)

```

![GA](https://user-images.githubusercontent.com/70419764/162658055-5e7b5dff-4a62-4a50-a716-b7e9533e50a6.gif)