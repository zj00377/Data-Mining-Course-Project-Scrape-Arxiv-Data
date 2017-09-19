# cse691p1

=================
Scraping Data
=================
-----------------
Commands
-----------------
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape1.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape2.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape3.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape4.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape5.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape6.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape7.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape8.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape9.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape10.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape11.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape12.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape13.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape14.py
.../cse691p1/arxivscraper-master/arxivscraper$ python scrape15.py

-----------------
Outputs
-----------------
http://export.arxiv.org/oai2?verb=ListRecords&from=2015-09-01&until=2016-08-31&metadataPrefix=arXiv&set=math
fetching up to  1000 records...
fetching up to  2000 records...
Got 503. Retrying after 30 seconds.
fetching up to  3000 records...
fetching up to  4000 records...
Got 503. Retrying after 30 seconds.
fetching up to  5000 records...
fetching up to  6000 records...
Got 503. Retrying after 30 seconds.
fetching up to  7000 records...
fetching up to  8000 records...
Got 503. Retrying after 30 seconds.
fetching up to  9000 records...
fetching up to  10000 records...
Got 503. Retrying after 30 seconds.
fetching up to  11000 records...
fetching up to  12000 records...
Got 503. Retrying after 30 seconds.
fetching up to  13000 records...
fetching up to  14000 records...
Got 503. Retrying after 30 seconds.
fetching up to  15000 records...
fetching up to  16000 records...
Got 503. Retrying after 30 seconds.
fetching up to  17000 records...
fetching up to  18000 records...
Got 503. Retrying after 30 seconds.
...
...


=================
Edge List
=================

-----------------
Commands
-----------------
.../cse691p1/authorshipgraph$ g++ -std=c++11 parse.cpp -o parse.o
.../cse691p1/authorshipgraph$ ./parse.o datalist.txt 5
.../cse691p1/authorshipgraph$ ./parse.o datalist.txt 15

-----------------
Outputs
-----------------
jzhang@EN4119307L:/media/jzhang/Data/cse691p1/authorshipgraph$ ./parse.o datalist.txt 5
number of previous years: 5
Files to parse:
scrape1.txt
scrape2.txt
scrape3.txt
scrape4.txt
scrape5.txt
scrape6.txt
scrape7.txt
scrape9.txt
scrape10.txt
scrape11.txt

Processing 5 years of data
processing: scrape1.txt
ERROR: author list not found $[...] at line: 3726
processing: scrape2.txt
ERROR: author list not found $[...] at line: 2838
processing: scrape3.txt
ERROR: author list not found $[...] at line: 3088
processing: scrape4.txt
ERROR: author list not found $[...] at line: 1865
processing: scrape5.txt
ERROR: author list not found $[...] at line: 1723

jzhang@EN4119307L:/media/jzhang/Data/cse691p1/authorshipgraph$ ./parse.o datalist.txt 15
number of previous years: 15
Files to parse:
scrape1.txt
scrape2.txt
scrape3.txt
scrape4.txt
scrape5.txt
scrape6.txt
scrape7.txt
scrape9.txt
scrape10.txt
scrape11.txt

Processing 10 years of data
processing: scrape1.txt
ERROR: author list not found $[...] at line: 3726
processing: scrape2.txt
ERROR: author list not found $[...] at line: 2838
processing: scrape3.txt
ERROR: author list not found $[...] at line: 3088
processing: scrape4.txt
ERROR: author list not found $[...] at line: 1865
processing: scrape5.txt
ERROR: author list not found $[...] at line: 1723
processing: scrape6.txt
ERROR: author list not found $[...] at line: 1554
processing: scrape7.txt
ERROR: author list not found $[...] at line: 1453
processing: scrape9.txt
ERROR: author list not found $[...] at line: 1251
processing: scrape10.txt
ERROR: author list not found $[...] at line: 1468
processing: scrape11.txt
ERROR: author list not found $[...] at line: 4548


===================
Draw graph and
Computing Metrics
===================

-----------------
Commands
-----------------
$ python drawgraph.py vertexlist_5.txt edgelist_5.txt
$ python drawgraph.py vertexlist_15.txt edgelist_15.txt

-----------------
Outputs
-----------------
.../cse691p1/drawgraph$ python drawgraph.py vertexlist_5.txt edgelist_5.txt
/home/jzhang/anaconda/lib/python2.7/site-packages/graph_tool/draw/cairo_draw.py:1480: RuntimeWarning: Error importing Gtk module: No module named gi; GTK+ drawing will not work.
  warnings.warn(msg, RuntimeWarning)
vertex list file path: vertexlist_5.txt
edge list file path: edgelist_5.txt
graph size: 6051
node 1 (degree): 5
node 1 (in degree): 0
node 2 (degree): 0
node 100 (degree): 10
degrees for nodes[0,1,2,4,10,1000,355]: [8 5 0 0 1 5 1]
average local clustering coefficient: (0.21586354082146397, 0.0062300623184292662)
global clustering coefficient: (0.28308408747209485, 0.03247345914276247)
average path length: 4055755007.77
/home/jzhang/anaconda/lib/python2.7/site-packages/matplotlib/collections.py:571: FutureWarning: elementwise comparison failed; returning scalar instead, but in the future will perform elementwise comparison
  if self._edgecolors == str('face'):
Min degree: 0 Node: 2

Max degree: 88 Node: 375


===================
Issues
===================

----------------
Issue 1
----------------
1) Duplicate author last names

Two different authors but same last name (one vertex node but multiple edges to self)
['zhang', 'zhang']
