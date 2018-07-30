# ants
This program takes a graph (rooms with un-directed connections) and computes the most efficient way to move N ants from source node to sink node, outputs an animated movement of the ants

This project was done in collaboration with Liam Dehaudt at 42.

## Compiling and running
Run `make`. An executable will compile. Currently only tested on OS X.

Run with `./ants "Filename"`.
A collection of sample ant farms is included in `farms/` folder.

## Algorithm
We re-formulated the problem into a mex-flow problem on a derived directed graph (with more vertices)to apply the Ford–Fulkerson algorithm. Project the resulting parallel paths to the origional network and resolve overlaps. Then we queue the ants in the resulting set of disjoint paths depending on the length of each path. The result garentees optimum solution as long as the number of ants is greater than the sum of lengths of paths from Ford–Fulkerson.

## Steps
* Store the rooms and connections into an undirected graph (Network)
* Build derived graph from Network where each rooms became 2 nodes ("in" node and "out" node, with directed connections between them: in->out and out->in)
* For each Network connection, connect the cooresponding rooms in both ways, always from "out" to "in"
* Apply Ford–Fulkerson algorithm to the new directed graph
* Project the paths to the network, overlaps will occur in particular manners (two ants may travel in opposite direction on the same edge(s)), we resolve such overlap by re-directing the ants and hence shortening the overall length of paths
* Queue the anys at each of the disjoint paths so that the last batch of the ants arrive at the same time

![alt text](https://github.com/conanwu777/ants/blob/master/1.png)
![alt text](https://github.com/conanwu777/ants/blob/master/2.png)
![alt text](https://github.com/conanwu777/ants/blob/master/3.png)
![alt text](https://github.com/conanwu777/ants/blob/master/4.png)
![alt text](https://github.com/conanwu777/ants/blob/master/5.png)
