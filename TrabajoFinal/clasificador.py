
# This Python 3 environment comes with many helpful analytics libraries installed
# It is defined by the kaggle/python Docker image: https://github.com/kaggle/docker-python
# For example, here's several helpful packages to load

import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)

# Input data files are available in the read-only "../input/" directory
# For example, running this (by clicking run or pressing Shift+Enter) will list all files under the input directory

import os
for dirname, _, filenames in os.walk('./voice.csv'):
    for filename in filenames:
        print(os.path.join(dirname, filename))

# You can write up to 20GB to the current directory (/kaggle/working/) that gets preserved as output when you create a version using "Save & Run All"
# You can also write temporary files to /kaggle/temp/, but they won't be saved outside of the current session


data = pd.read_csv('./voice.csv')
data_set=pd.DataFrame(data)
data_set.head()

data.isnull().sum()

data_set.describe()

import seaborn
import matplotlib.pyplot as plt
plt.figure(figsize=(21,21))
seaborn.heatmap(data.corr(),annot=True,cmap='viridis',linewidth=0.5)

import mglearn
gen = pd.read_csv('./voice.csv')
gen_data = pd.DataFrame(gen)
gen_data.head()
male = gen.loc[gen['label']=='male']
female = gen.loc[gen['label']=='female']
fig, axes = plt.subplots(10, 2, figsize=(10,20))
ax = axes.ravel()
for i in range(20):
    ax[i].hist(male.iloc[:,i], bins=20, color=mglearn.cm3(0), alpha=.5)
    ax[i].hist(female.iloc[:, i], bins=20, color=mglearn.cm3(2), alpha=.5)
    ax[i].set_title(list(male)[i])
    ax[i].set_yticks(())
    ax[i].set_xlabel("Feature magnitude")
    ax[i].set_ylabel("Frequency")
    ax[i].legend(["male", "female"], loc="best")

fig.tight_layout()


new_data_set = data_set.drop(['sfm','kurt','meandom','meanfreq','dfrange','modindx'],axis=1)
new_data_set.head()

plt.figure(figsize=(16,16))
seaborn.heatmap(new_data_set.corr(),annot=True,cmap='viridis',linewidth=0.5)

from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test= train_test_split(new_data_set.iloc[ : , : -1].values, new_data_set.iloc[ : ,  -1].values, test_size=0.2)


from sklearn.tree import DecisionTreeClassifier
classifier6 = DecisionTreeClassifier(criterion = 'entropy')
classifier6.fit(X_train, y_train)
print('Using Decision tree classifier:')
print('Accuracy of training set: {:.2f}'.format(classifier6.score(X_train,y_train)))
print('Accuracy of test set: {:.2f}'.format(classifier6.score(X_test,y_test)))

# Using Decision tree classifier:
# Accuracy of training set: 1.00
# Accuracy of test set: 0.97

























































