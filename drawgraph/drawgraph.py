#! /usr/bin/env python

from __future__ import division, absolute_import, print_function
from graph_tool.all import *
import sys
if sys.version_info < (3,):
    range = xrange
import os
from pylab import *  # for plotting


# parse vertices from processed scraped arxiv data for math.dg
argsize = len(sys.argv)
if argsize < 2:
  path1 = 'vertexlist.txt'
  path2 = 'edgelist.txt'
else:
  path1 = sys.argv[1]
  path2 = sys.argv[2]

print('vertex list file path: ' + path1)
print('edge list file path: ' + path2)

# construct an undirected graph
ug = Graph(directed=False)
vfile = open(path1,'r')
vsize = 0
for line in vfile:
  ug.add_vertex()
  vsize += 1

vfile.close()
print('graph size: ' + str(vsize))

vfile = open(path2,'r')
for line in vfile:
  edges = line.split("#")
  for edge in edges:
    if edge != '\n':
      # remove parentheses
      beg = edge.find("(")
      end = edge.find(")")
      edge = edge[beg+1:end]

      # split the two vertex by space "v1 v2" between them
      edge = edge.split(" ")
      ug.add_edge(ug.vertex(int(edge[0])), ug.vertex(int(edge[1])),False)

vfile.close()

# Output graph information: degrees, clustering coefficient, path length
# For undirected graph, the out degree is the degree, the in degree is always zero (graph-tool)
print("node 1 (degree): " + str(ug.vertex(1).out_degree()))
print("node 1 (in degree): " + str(ug.vertex(1).in_degree()))
print("node 2 (degree): " + str(ug.vertex(2).out_degree()))
print("node 100 (degree): " + str(ug.vertex(100).out_degree()))
print("degrees for nodes[0,1,2,4,10,1000,355]: " + str(ug.get_out_degrees([0,1,2,4,10,1000,355])))

# clustering coefficient
lc = local_clustering(ug)
gc = global_clustering(ug)
print("average local clustering coefficient: " + str(vertex_average(ug,lc)))
print("global clustering coefficient: " + str(gc))

# average path length
pl = shortest_distance(ug)
apl = sum([sum(i) for i in pl])/(ug.num_vertices()*(ug.num_vertices() - 1)*0.5)
print("average path length: " + str(apl))

# plot degree distribution as a histogram
out_hist = vertex_hist(ug, "out")

y = out_hist[0]
err = sqrt(out_hist[0])
err[err >= y] = y[err >= y] - 1e-2

figure(figsize=(6,4))
errorbar(out_hist[1][:-1], out_hist[0], fmt="o", yerr=err, label="in")
gca().set_yscale("log")
gca().set_xscale("log")
gca().set_ylim(1e-1, 1e5)
gca().set_xlim(0.8, 1e3)
subplots_adjust(left=0.2, bottom=0.2)
xlabel("$k_{in}$")
ylabel("$NP(k_{in})$")
tight_layout()
savefig("authorship-network-deg-dist.pdf")
savefig("authorship-network-deg-dist.png")

# draw the graph

# set color map to be based on out degree of vertex node
#vdeg = ug.get_out_degrees(ug.get_vertices())
v_deg = ug.new_vertex_property("int")

#output degree to text file and set vertex property using degree
path3 = 'degreelist.txt'
vfile = open(path3,'w')

vidx = 0
min_deg = 1000000
min_deg_idx = -1
max_deg = -1
max_deg_idx = -1
for v in ug.vertices():
  v_deg[v] = v.out_degree()
  vfile.write(str(vidx) + " " + str(v_deg[v]) + "\n")
  if v_deg[v] > max_deg:
    max_deg = v_deg[v]
    max_deg_idx = vidx
  if v_deg[v] < min_deg:
    min_deg = v_deg[v]
    min_deg_idx = vidx
  vidx += 1

# close the file
vfile.close()

# output max and min degree
print("Min degree: " + str(min_deg) + " Node: " + str(min_deg_idx) + "\n")
print("Max degree: " + str(max_deg) + " Node: " + str(max_deg_idx) + "\n")

pos = sfdp_layout(ug)
graph_draw(ug, pos, output_size=(2000, 2000), vertex_color=[1,1,1,0], vertex_fill_color=v_deg, vertex_size=2, edge_pen_width=0.5, vcmap=matplotlib.cm.gist_heat_r, output="authorship_network.png")
