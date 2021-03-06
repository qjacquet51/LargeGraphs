import networkx as nx 
import matplotlib.pyplot as plt
import os
import numpy as np

INPUT_FILE = os.path.join(os.path.dirname(__file__), os.pardir, "instances", "generated", "graph_1.txt")
print(INPUT_FILE)

intify = lambda L: [int(l) for l in L]
edges = [intify(l.replace("\n", "").split(" ")) for l in open(INPUT_FILE).readlines()]
max_node = edges[-1][0]+1

G = nx.Graph()
G.add_nodes_from(range(max_node))
G.add_edges_from(edges)

cmap = plt.get_cmap('tab20')
colors = [cmap(i) for i in np.linspace(0, 1, max_node//100)]
pos = nx.spring_layout(G)
for c in range(max_node//100):
	nx.draw_networkx_nodes(G, pos=pos, node_color=[colors[c]], nodelist=range(c*100, (c+1)*100), node_size=100)
nx.draw_networkx_edges(G, pos=pos)
plt.show()
