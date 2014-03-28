CatsDogs
==============

The puzzle:
* input an integer, the number of test cases, 1 ≤ N ≤ 100
* for each test case, input the number of cats, dogs, and voters
* then for each voter, input the dog/cat to keep and the dog/cat to throw away
* output the max possible number of satisfied voters


C++
---

The problem suggests a naive solution of calculating the number of satisfied voters for each combination of cats
and dogs; however, a more effecient algorithm uses a directed graph.  I initially set up the problem as a bipartite
graph with the nodes representing cats and dogs and directed edges indicating the votes; however, this did not suggest
a solution.

With help from this site:
https://njzk2.wordpress.com/2013/05/31/cats-vs-dogs/
I implemented a bipartite graph with nodes repesenting votes and edges indicating incompatability.  In order to find
the maximum independent set, I implemented Hopcroft-Karp.  While my implementation works for the sample data, Spotify
says the solution calculates the wrong answer.  There is either an error in choosing this algorithm or an error in my
implementation.  Either way, it is difficult to ascertain without the data that generates the wrong answer.

Spotify Status: Wrong Answer

Compile:
g++ cats_and_dogs.cpp -o cats_and_dogs.exe

Run:  
./cats_and_dogs.exe

Run using sample inputs from the Spotify puzzle page:
./cats_and_dogs.exe < ../sample-input1.txt  
