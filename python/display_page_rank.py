import matplotlib.pyplot as plt
import pandas as pd

NAME = "../results/alpha=0.15_alr21-dirLinks.txt"
df = pd.DataFrame([l.replace("\n", "").split("\t") for l in open(NAME, "r").readlines()]).astype('float32')
df = df[df[1]>0.0001]
print(df)
plt.scatter(df.iloc[:,1].values, df.iloc[:,2].values)
plt.show()