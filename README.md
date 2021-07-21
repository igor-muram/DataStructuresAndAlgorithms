# Data Structures And Algorithms

## Problem condition

Solve the problem of graph theory:<br>
"Find the length of the longest simple path from city A to city B in a given system of one-way roads."

## External representation of the one-way road system

<ul>
  <li>An example of the input file and the results of the program for this road system are added to the project.</li>
  <li>The departure city is on the first line of the input file.</li>
  <li>Destination city is on the second line.</li>
  <li>All possible routes between cities are indicated after.</li>
</ul>

`<road system> ::= <departure city> {new line} <destination city> {new line} <road list>`<br>
`<departure city> ::= <city>`<br>
`<destination city> ::= <city>`<br>
`<road list> ::= <road> {new line} <road list> | {empty}`<br>
`<road> ::= <from> {space} <whereto> {space} <road length>`<br>
`<from> ::= <city>`<br>
`<whereto> ::= <city>`<br>
`<city> ∈ R+ `<br>
`<city> ::= {character sequence} | {number}`<br>

Input file example:

![image](https://user-images.githubusercontent.com/54866075/126553280-0432899e-ed85-4d84-aaa9-e2a7cab7f7ac.png)

<ul>
  <li>In the external view of the road system, isolated cities are not displayed.</li>
  <li>Also in the input file we will not specify the number of cities in the road system. It will allow you not to make restrictions on the number of cities in the road system, as well as make it easier for the user to enter the input data. First, there will be no need to count the number of cities before entering the road system, and if you change the road system, there will be no need to recalculate it. Second, the amount of data needed to get a result will be reduced.</li>
</ul>

## Mathematical model

<ul>
  <li>The mathematical model of a one-way road system is an oriented, weighted, labeled, cyclic, not necessarily connected, multi- and pseudograph <code>G = (V, E)</code> with weight function <code>w:&nbsp;E → R</code>, where <code>w(u, v) ≥ 0</code> for all <code>(u, v) ∈ E</code>.</li>
  <li>To solve problem, it is not necessary to keep loops, roads to the departure city, roads from the destination city, and from multiples only the longest road needs to be kept. On this basis, the mathematical model of this one-way road system can be simplified, so that the mathematical model is a weighted, labeled, cyclic, not necessarily connected orgraph <code>G = (V, E)</code> with weight function <code>w:&nbsp;E → R</code>, where <code>w(u, v) ≥ 0</code> for all <code>(u, v) ∈ E</code>.</li>
  <li>The vertices correspond to cities and the arcs to one-way roads. </li>
  <li>The label of a vertex is the name of a city. </li>
  <li>The arc <code>(u, v)</code> leads from the vertex <code>u</code> corresponding to the starting city to the vertex <code>v</code> corresponding to the city that is the end of the road. </li>
  <li>The weight of the arc is the length of the road.</li>
  <li>A path is a sequence of vertices of the graph. </li>
  <li>A simple path is a path in which no vertex and no edge are repeated. </li>
  <li>The length of a path connecting vertex <code>u</code> and any of other vertices is the sum of lengths of roads of this path, i.e. the sum of weights of graph arcs.</li>
  <li>To find the maximal length of a path from a given city <code>u</code> to city <code>v</code> in a given road system <code>S</code>, we first have to make sure that at least one path exists from city <code>u</code> to city <code>v</code>. If such a path exists, then to find the maximum length of the path you need to determine the lengths of roads. We will sequentially look through the vertices of orgraph <code>G</code> starting from vertex <code>u</code> and look for paths (by calculating their lengths) from the starting vertex to vertex <code>v</code> until all paths leading to vertex <code>v</code> have been looked through. If vertex <code>v</code> is not reachable from vertex <code>u</code>, then there is no maximal path from <code>u</code> to <code>v</code>. To keep the found path simple, we will memorize the traversed vertices in the current path.</li>
  <li>There can be several paths that satisfy the problem condition. To answer the question what is the maximal length of the path between two cities <code>A</code> and <code>B</code>, it is sufficient to find any of such paths (the last detected in the sequential order) and specify its length. </li>
</ul>

## Formal problem statement

<ul>
  <li>In a weighted, labeled, cyclic, not necessarily connected orgraph find the length of the longest simple path between two vertices.</li>
  <li>If the road system consists of several connectivity components, then the desired path between two given cities will not exist if both given cities are in different connectivity components.</li>
  <li>If a one-way road system contains only one city, or no departure and/or destination city, or the departure city is the same as the destination city, then there is no path to be sought.</li>
  <li>If the one-way road system contains only two cities (departure and destination), then the problem is reduced to finding the longest road from the departure city to the destination city. Since in this problem it makes sense to save only the maximum of multiples of the road, the saved road will be the desired path.</li>
  <li>If the system of one-way roads has more than two cities, then to find the maximum length of the path between the given cities we will look through the orgraph  in depth, starting from the top of <code>start</code> (the beginning of the path). We will mark the vertices with labels as they pass through. The label will tell us if the vertex has been viewed before. We will return when every vertex adjacent to the current vertex is tagged or is the end of the path. The search ends when all paths from vertex <code>start</code> to vertex <code>finish</code> have been viewed.</li>
  <li>The solution to this problem is to look at all paths from the next vertex adjacent to the start-city vertex to the destination-city vertex, which provides finding the path of maximal length.</li>
</ul>
