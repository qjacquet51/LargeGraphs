import matplotlib.pyplot as plt
import pandas as pd

NAME = "../results/pk_alpha=0.15_alr21-dirLinks.txt"
df = pd.DataFrame([l.replace("\n", "").split("\t") for l in open(NAME, "r").readlines()]).astype('float32')
df = df[df[1]>0.0001] # sinon le plot galère
plt.scatter(pd.np.log(df.iloc[:,1].values), pd.np.log(df.iloc[:,3].values))
plt.grid()
plt.xlabel("log(Page Rank)")
plt.ylabel("log(Out Degree)")
plt.show()