# Data Structures And Algorithms

## Problem condition

Solve the problem of graph theory:<br>
"Find the length of the longest simple path from city A to city B in a given system of one-way roads."

## Initial problem data

<ul>
  <li><code>S</code> is a road system, <code>S = {(name_1[i], name_2[i], weight[i]) | name_1[i], name_2[i] ∈ <сity>, weight[i] ∈ R+, i ∈ N}</code></li>
  <li><code><сity> ::= {g[j] | g[j] ∈ {subset of Russian and Latin letters} ∪ N, j ∈ N}</code></li>
  <li><code>name_1[i]</code> is the city specifying the beginning of the road</li>
  <li><code>name_2[i]</code> is the city specifying the end of the road</li>
  <li><code>weight[i]</code> is the length of the road between cities <code>name_1[i]</code> and <code>name_2[i]</code></li>
</ul>

## Result

<ul>
  <li><code>max ∈ R+</code></li>
  <li><code>Road = {a[i] | a[i] ∈ <city>, i > 1, i ∈ N} || {the message that the desired road does not exist}</code></li>
</ul>

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

## Internal representation of the road system

<ul>
  <li>Since in this problem we work with a system of roads, in most cases the graph will be sparse, i.e. the set of edges will be much smaller than the set of vertices. So the adjacency matrix and incident matrix of the graph will consist mostly of zeros, which leads to unnecessary waste of memory.</li>
  <li>The inconvenience of the list of graph edges is the large number of steps needed to get the set of vertices to which the edges lead from the given vertex.</li>
  <li>So we represent the original road system by its adjacency list, since it gives a compact representation for sparse graphs.</li>
  <li>In order not to complicate the lists of adjacency we mark the vertex by a number instead of the name of the city. The vertices of the graph will be numbered starting from zero.</li>
  <li>List of adjacent vertices shall be a linear one-way list. This will not impose restrictions on the number of roads from each city.</li>
  <li>City names will be represented by a vector of strings, and the adjacency list of the graph by a vector of structures, which allows to make no restriction on the number of cities in the road system.</li>
</ul>

– adjacency structure (lists of adjacent vertices of the graph):

`struct wtable`<br>
`{`<br>
`   int top;`<br>
`   double weight;`<br>
`   wtable *next;`<br>
`};`<br>
`vector<wtable*> wmas;`

– list of city names:

`vector<string> cities;`

## External output representation

`max ∈ R+, which is the length of the longest simple path || {the message that the desired road does not exist}`<br>
`Road = <sequence of cities>`<br>
`<city sequence> ::= <city> {space} {"—"} {space} <city sequence> | <city> {space} {"—"} {space} <city>`

## Mathematical model

<ul>
  <li>The mathematical model of a one-way road system is an oriented, weighted, labeled, cyclic, not necessarily connected, multi- and pseudograph <code>G&nbsp;=&nbsp;(V,&nbsp;E)</code> with weight function <code>w:&nbsp;E&nbsp;→&nbsp;R</code>, where <code>w(u,&nbsp;v)&nbsp;≥&nbsp;0</code> for all <code>(u,&nbsp;v)&nbsp;∈&nbsp;E</code>.</li>
  <li>To solve problem, it is not necessary to keep loops, roads to the departure city, roads from the destination city, and from multiples only the longest road needs to be kept. On this basis, the mathematical model of this one-way road system can be simplified, so that the mathematical model is a oriented, weighted, labeled, cyclic, not necessarily connected graph <code>G&nbsp;=&nbsp;(V,&nbsp;E)</code> with weight function <code>w:&nbsp;E&nbsp;→&nbsp;R</code>, where <code>w(u,&nbsp;v)&nbsp;≥&nbsp;0</code> for all <code>(u,&nbsp;v)&nbsp;∈&nbsp;E</code>.</li>
  <li>The vertices correspond to cities and the arcs to one-way roads. </li>
  <li>The label of a vertex is the name of a city. </li>
  <li>The arc <code>(u,&nbsp;v)</code> leads from the vertex <code>u</code> corresponding to the starting city to the vertex <code>v</code> corresponding to the city that is the end of the road.</li>
  <li>The weight of the arc is the length of the road.</li>
  <li>A path is a sequence of vertices of the graph.</li>
  <li>A simple path is a path in which no vertex and no edge are repeated.</li>
  <li>The length of a path connecting vertex <code>u</code> and any of other vertices is the sum of lengths of roads of this path, i.e. the sum of weights of graph arcs.</li>
  <li>To find the maximal length of a path from a given city <code>u</code> to city <code>v</code> in a given road system <code>S</code>, we first have to make sure that at least one path exists from city <code>u</code> to city <code>v</code>. If such a path exists, then to find the maximum length of the path you need to determine the lengths of roads. We will sequentially look through the vertices of graph <code>G</code> starting from vertex <code>u</code> and look for paths (by calculating their lengths) from the starting vertex to vertex <code>v</code> until all paths leading to vertex <code>v</code> have been looked through. If vertex <code>v</code> is not reachable from vertex <code>u</code>, then there is no maximal path from <code>u</code> to <code>v</code>. To keep the found path simple, we will memorize the traversed vertices in the current path.</li>
  <li>There can be several paths that satisfy the problem condition. To answer the question what is the maximal length of the path between two cities <code>A</code> and <code>B</code>, it is sufficient to find any of such paths (the last detected in the sequential order) and specify its length. </li>
</ul>

## Formal problem statement

<ul>
  <li>In a weighted, labeled, cyclic, not necessarily connected graph find the length of the longest simple path between two vertices.</li>
  <li>If the road system consists of several connectivity components, then the desired path between two given cities will not exist if both given cities are in different connectivity components.</li>
  <li>If a one-way road system contains only one city, or no departure and/or destination city, or the departure city is the same as the destination city, then there is no path to be sought.</li>
  <li>If the one-way road system contains only two cities (departure and destination), then the problem is reduced to finding the longest road from the departure city to the destination city. Since in this problem it makes sense to save only the maximum of multiples of the road, the saved road will be the desired path.</li>
  <li>If the system of one-way roads has more than two cities, then to find the maximum length of the path between the given cities we will look through the graph in depth, starting from the top of <code>start</code> (the beginning of the path). We will mark the vertices with labels as they pass through. The label will tell us if the vertex has been viewed before. We will return when every vertex adjacent to the current vertex is tagged or is the end of the path. The search ends when all paths from vertex <code>start</code> to vertex <code>finish</code> have been viewed.</li>
  <li>The solution to this problem is to look at all paths from the next vertex adjacent to the start-city vertex to the destination-city vertex, which provides finding the path of maximal length.</li>
</ul>

## An algorithm for solving the problem

`{`<br>
`   max ← 0, Road ← ∅;`<br>
`   switch (enter information about the road system and create a graph adjacencies structure)`<br>
`   {`<br>
`      case 0:`<br>
`         if (there are no simple ways out of the departure city)`<br>
`            output "There are no simple ways out of the departure city";`<br>
`         else`<br>
`            if (number of cities == 2)`<br>
`            {`<br>
`               max ← the length of the road from the departure city to the destination city;`<br>
`               Road ← road from the departure city to the destination city;`<br>
`               output max, Road;`<br>
`            }`<br>
`            else`<br>
`            {`<br>
`               Road ← search for the maximum simple path between the given cities;`<br>
`               max ← length of Road;`<br>
`               if (max = 0)`<br>
`                  output "There is no way from the departure city to the destination city";`<br>
`               else`<br>
`                  output max, Road;`<br>
`               clearing the memory allocated for path storage;`<br>
`            }`<br>
`         break;`<br>
`      case -1:`<br>
`         output "The file with information about the road system was not found";`<br>
`         break;`<br>
`      case -2:`<br>
`         output "The file with information about the road system is empty";`<br>
`         break;`<br>
`      case -3:`<br>
`         output "The departure city is the same as the destination city";`<br>
`         break;`<br>
`     case -4:`<br>
`         output "Departure city and/or destination city not found in the way";`<br>
`         break;`<br>
`   }`<br>
   
`   clearing the memory allocated for storing the list of cities and the list of adjacencies;`<br>
`}`<br>

## An algorithm for finding the maximal path from vertex `start` to vertex `finish`

<ul>
  <li><code>S</code> is a stack. An element of the stack is a vertex, its distance and a pointer to the list of viewed vertices reachable from it.</li>
  <li><code>Road</code> is the path found.</li>
  <li><code>w</code> is the current distance.</li>
</ul>

`{`<br>
`   S ← ∅; Road ← ∅;`<br>
`   start ← start of the road;`<br>
`   finish ← end of the road;`<br>
`   x ← an unseen top adjacent to the start;`<br>
`   while (∃x)`<br>
`   {`<br>
`      if (x == finish)`<br> 
`      {`<br>
`         if (w > max)`<br>
`         {`<br>
`            clear the path already saved;`<br>
`            max ← w;`<br>
`         }`<br>
`         if (∃ other unseen vertices adjacent to the start)`<br> 
`            x ← adjacent vertex;`<br>
`         else`<br> 
`            mark x as a viewed vertex;`<br>
`      }`<br>
`      in_stack (S, x, w);`<br>
`      while (S is not empty)`<br> 
`      {`<br>
`         x ← the first element of S;`<br>
`         y ← unseen vertex adjacent to x;`<br>
`         if (y is not exist)`<br> 
`            from_stack(S);`<br>
`         else`<br>
`            if (y == finish) `<br>
`            {`<br>
`               if (distance from start to y > max)`<br> 
`               {`<br>
`                  max ← distance from start to y;`<br>
`                  Road ← road from start to y;`<br>
`               }`<br>
`               from_stack(S);`<br>
`            }`<br>
`            else`<br>
`            {`<br>
`               mark y as a viewed vertex;`<br> 
`               in_stack (S, y, distance from start to y);`<br>
`            }`<br>
`      }`<br>
`      x ← unseen vertex adjacent to start;`<br>
`   }`<br>
`   return Road;`<br>
`}`

## Road system input algorithm

<ul>
  <li><code>BR</code> is the beginning of the road.</li>
  <li><code>ER</code> is the end of the road.</li>
  <li><code>start</code> is the index of the departure city in the list of cities.</li>
  <li><code>finish</code> is the index of the destination city in the list of cities.</li>
</ul>

`{`<br> 
`   if (the file did not open) return -1;`<br>
`   if (could not read the departure city) return -2;`<br>
`   enter the departure city and the destination city;`<br>
`   if (departure city == destination city) return -3;`<br>
`   while (not end of file)`<br>
`   {`<br>
`      input of BR;`<br>
`      if (BR is not on the list of cities)`<br>
`         add BR to the list of cities;`<br>
`      input of ER;`<br>
`      if (ER is not on the list of cities)`<br>
`         add ER to the list of cities;`<br>
`      input of the road length from BR to ER;`<br>
`      if (the road is not a loop && does not go to the departure city && does not go from the destination city)`<br>
`         if (the road from BR to ER is not on the list of adjacencies)`<br> 
`            add the road from BR to ER to the list of adjacencies;`<br>
`         else`<br>
`            if (current road length > the length of the existing road from the BR to the ER)`<br>
`              the length of the existing road from the BR to the ER ← current road length;`<br>
`   }`<br>
`   for (i ← 0; i < number of cities && count != 2; i++)`<br>
`      if (cities[i] == departure city)`<br>
`      {`<br>
`         start = i;`<br>
`         count++;`<br>
`      }`<br>
`      else`<br> 
`         if (cities[i] == destination city)`<br>
`         {`<br>
`            finish = i;`<br>
`            count++;`<br>
`         }`<br>
`   if (count != 2) return -4;`<br>
`   return 0;`<br>
`}`<br>

## Test 1
`Purpose:` The file with information about the road system was not found.<br>
`Input:`

`Result:`<br>
The file with information about the road system was not found

## Test 2
`Purpose:` The file with information about the road system is empty.<br>
`Input:`

`Result:`<br>
The file with information about the road system is empty

## Test 3
`Purpose:` There are no simple ways out of the departure city.<br>
`Input:`<br>
НСК<br>
ЕКБ<br>
ЕКБ ЕКБ 10<br>
НСК НСК 10<br>

![image](https://user-images.githubusercontent.com/54866075/126880547-a9234033-1827-4c4a-8684-8f8c74d114ab.png)

`Result:`<br>
There are no simple ways out of the НСК

## Test 4
`Purpose:` There is no way from the departure city to the destination city.<br>
`Input:`<br>
НСК<br>
ЕКБ<br>
НСК ТУЛА 10<br>
ТУЛА ПИТЕР 10<br>
ПЕРМЬ ЕКБ 10<br>

![image](https://user-images.githubusercontent.com/54866075/126880671-924df094-667b-4014-8dbc-278094ce08fa.png)

`Result:`<br>
There is no way from the НСК to the ЕКБ

## Test 5
`Purpose:` The departure city is the same as the destination city.<br>
`Input:`<br>
НСК<br>
НСК<br>
НСК ТУЛА 10<br>
ТУЛА ПИТЕР 10<br>
ПИТЕР ЕКБ 10<br>

![image](https://user-images.githubusercontent.com/54866075/126880705-ec486e75-aa65-4265-8fd9-974d5956d083.png)

`Result:`<br>
The departure city is the same as the destination city

## Test 6
`Purpose:` Destination city is not on the way.<br>
`Input:`<br>
НСК<br>
ЕКБ<br>
НСК ТУЛА 10<br>
ТУЛА ПИТЕР 10<br>
ПЕРМЬ УФА 10<br>

![image](https://user-images.githubusercontent.com/54866075/126880730-4be9e7e1-a80d-463c-9511-cb92987f74d8.png)

`Result:`<br>
Departure city and/or destination city not found in the way

## Test 7
`Purpose:` There are multiple roads of different lengths between the two cities in the road system.<br>
`Input:`<br>
НСК<br>
ЕКБ<br>
НСК ЕКБ 80<br>
НСК ЕКБ 100<br>
НСК ЕКБ 50<br>

![image](https://user-images.githubusercontent.com/54866075/126880781-40749f3e-de53-42ab-aeed-08713bab8837.png)

`Result:`<br>
The length of the maximum simple path from НСК to ЕКБ is 100<br>
The longest simple path from НСК to ЕКБ: НСК — ЕКБ

## Test 8
`Purpose:` All paths between the departure and destination cities are the same length.<br>
`Input:`<br>
НСК<br>
ЕКБ<br>
НСК ЕКБ 30<br>
НСК ТУЛА 15<br>
ТУЛА ЕКБ 15<br>
НСК ПЕРМЬ 10<br>
ПЕРМЬ ПИТЕР 10<br>
ПИТЕР ЕКБ 10<br>

![image](https://user-images.githubusercontent.com/54866075/126880842-90356c25-607f-4e1d-81cd-9a2687edba6a.png)

`Result:`<br>
The length of the maximum simple path from НСК to ЕКБ is 30<br>
The longest simple path from НСК to ЕКБ: НСК — ПЕРМЬ — ПИТЕР — ЕКБ

## Test 9
`Purpose:` The road system consists of several connectivity components.<br>
`Input:`<br>
НСК<br>
ЕКБ<br>
МСК ПИТЕР 100<br>
ПИТЕР КИЕВ 400<br>
КИЕВ ВОЛОГДА 200<br>
ВОЛОГДА ВОРОНЕЖ 120<br>
ВОРОНЕЖ УФА 300<br>
НСК ПЕРМЬ 10<br>
ПЕРМЬ БАРНАУЛ 20<br>
БАРНАУЛ КАЗАНЬ 30<br>
КАЗАНЬ ЕКБ 40<br>

![image](https://user-images.githubusercontent.com/54866075/126880877-28e50b33-7551-4e50-8c1a-d1bfd9a49620.png)

`Result:`<br>
The length of the maximum simple path from НСК to ЕКБ is 100<br>
The longest simple path from НСК to ЕКБ: НСК — ПЕРМЬ — БАРНАУЛ — КАЗАНЬ — ЕКБ

## Test 10
`Purpose:` The road system has dead-ends.<br>
`Input:`<br>
НСК<br>
ЕКБ<br>
НСК УФА 10<br>
УФА ОМСК 1000<br>
НСК МСК 1000<br>
УФА ТОМСК 10<br>
ТОМСК РЯЗАНЬ 10<br>
РЯЗАНЬ ПЕРМЬ 1000<br>
ПЕРМЬ ПИТЕР 1000<br>
РЯЗАНЬ КИЕВ 10<br>
КИЕВ ВОЛОГДА 1000<br>
КИЕВ ЕКБ 10<br>

![image](https://user-images.githubusercontent.com/54866075/126880906-e8edf45b-ae3d-4517-a0cc-7a6626bcc172.png)

`Result:`<br>
The length of the maximum simple path from НСК to ЕКБ is 50<br>
The longest simple path from НСК to ЕКБ: НСК — УФА — ТОМСК — РЯЗАНЬ — КИЕВ — ЕКБ

## Test 11
`Purpose:` The road system has loops, roads from the destination city and roads to the departure city.<br>
`Input:`<br>
НСК<br>
ЕКБ<br>
НСК МСК 10<br>
НСК НСК 1000<br>
МСК МСК 1000<br>
ТОМСК ЕКБ 80<br>
МСК ТОМСК 10<br>
ЕКБ ЕКБ 1000<br>
САМАРА НСК 500<br>
ЕКБ КАЗАНЬ 100<br>
ЕКБ БАРНАУЛ 200<br>
БАРНАУЛ УФА 300<br>
УФА САМАРА 400<br>

![image](https://user-images.githubusercontent.com/54866075/126880949-42e848e2-a40a-4d74-94fe-6a3ba4e6e7ea.png)

`Result:`<br>
The length of the maximum simple path from НСК to ЕКБ is 100<br>
The longest simple path from НСК to ЕКБ: НСК — МСК — ТОМСК — ЕКБ

## Test 12
`Purpose:` The road system contains a cycle.<br>
`Input:`<br>
НСК<br>
ЕКБ<br>
НСК ТУЛА 60<br>
ТУЛА ПЕРМЬ 1000<br>
ПЕРМЬ ПИТЕР 1000<br>
УФА ОМСК 1000<br>
ПИТЕР УФА 1000<br>
ОМСК ТУЛА 1000<br>
ТУЛА ЕКБ 40<br>

![image](https://user-images.githubusercontent.com/54866075/126880971-4aa4937e-0996-4a79-bbf0-5de5c2d058eb.png)

`Result:`<br>
The length of the maximum simple path from НСК to ЕКБ is 100<br>
The longest simple path from НСК to ЕКБ: НСК — ТУЛА — ЕКБ

## Test 13
`Purpose:` The road system contains several cycles.<br>
`Input:`<br>
НСК<br>
ЕКБ<br>
НСК ТУЛА 40<br>
ТУЛА ПЕРМЬ 10<br>
ПЕРМЬ ПИТЕР 10<br>
ПИТЕР ТУЛА 1000<br>
ОМСК ТУЛА 1000<br>
ОМСК ПИТЕР 1000<br>
УФА ОМСК 1000<br>
УФА ПЕРМЬ 1000<br>
ПИТЕР УФА 10<br>
УФА КИЕВ 10<br>
БЕЛГОРОД УФА 1000<br>
БЕЛГОРОД ЕКБ 10<br>
КИЕВ БЕЛГОРОД 10<br>

![image](https://user-images.githubusercontent.com/54866075/126880982-ba11d20c-d5c9-4094-b308-ed598b97a3bd.png)

`Result:`<br>
The length of the maximum simple path from НСК to ЕКБ is 100<br>
The longest simple path from НСК to ЕКБ: НСК — ТУЛА — ПЕРМЬ — ПИТЕР — УФА — КИЕВ — БЕЛГОРОД — ЕКБ

## Test 14
`Purpose:` A big test with all possible situations.<br>
`Input:`<br>
\* too large *

![image](https://user-images.githubusercontent.com/54866075/126881173-d4a5c103-2af1-4a25-9ece-9431d8d11e6e.png)

`Result:`<br>
The length of the maximum simple path from 0 to 39 is 2330<br>
The longest simple path from 0 to 39: 0 — 35 — 4 — 5 — 20 — 7 — 10 — 11 — 8 — 18 — 12 — 21 — 43 — 14 — 15 — 16 — 17 — 45 — 41 — 36 — 37 — 38 — 39
