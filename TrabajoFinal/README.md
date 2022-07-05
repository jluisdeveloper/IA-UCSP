# Reconocimiento de género por voz

## Integrantes
- Aarón Misash Apaza Coaquira
- Andre Carlos Alvarez Cardenas
- Jorge Luis Huanca Mamani
- Miguel Alberto Motta Vilca

## Objetivo

Este proyecto entrena un algoritmo para identificar una voz como masculina o femenina, basándose en las propiedades acústicas de la voz y el habla. El modelo se entrena en un conjunto de datos que consta de 3168 muestras de voz grabadas, recopiladas de hablantes masculinos y femeninos. Las muestras  se procesan con inteligencia artificial usando algoritmos de aprendizaje automático para aprender rasgos específicos de género.

## Propiedades del conjunto de Datos:

Se miden las siguientes propiedades acústicas de cada voz:

- duración : duración de la señal
- meanfreq : frecuencia media (en kHz)
- sd : desviación estándar de la frecuencia
- mediana : frecuencia mediana (en kHz)
- Q25 : primer cuantil (en kHz)
- Q75 : tercer cuantil (en kHz)
- IQR : rango intercuantílico (en kHz)
- sesgo : sesgo (ver nota en la descripción de propprop)
- kurt : curtosis (ver nota en la descripción de specprop)
- sp.ent : entropía espectral
- sfm : planitud espectral
- modo : frecuencia de modo
- centroide : centroide de frecuencia (ver especificación)
- peakf : frecuencia pico (frecuencia con mayor energía)
- meanfun : promedio de la frecuencia fundamental medida a través de la señal acústica
- minfun : frecuencia fundamental mínima medida a través de la señal acústica
- maxfun : frecuencia fundamental máxima medida a través de la señal acústica
- meandom : promedio de la frecuencia dominante medida a través de la señal acústica
- mindom : mínimo de frecuencia dominante medido a través de la señal acústica
- maxdom : máximo de la frecuencia dominante medida a través de la señal acústica
- dfrange : rango de frecuencia dominante medido a través de la señal acústica
- modindx : índice de modulación. Calculado como la diferencia absoluta acumulada entre mediciones adyacentes de frecuencias fundamentales dividida por el rango de frecuencia


Se usa el manejador de paquetes [pip](https://pip.pypa.io/en/stable/) para instalar las librerias necesarias.

```bash
pip install mglearn
```

```bash
pip install seaborn
```

```bash
pip install numpy
```

```bash
pip install pandas
```

```bash
pip install scikit-learn
```
