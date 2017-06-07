# Genetic Algorithm Demonstration
###### Curteosy of Professor M. Franklin KSU

This program demonstrates the genetic algorithm to maximize our function <code>f(x) = x<sup>2</sup></code>.
We do this in a series of 5 steps:

 1 - Randomly generate candidates
 
 2 - Apply fitness function & sort
 
 3 - Crossover
 
 4 - Mutate
 
 5 - Repeat
 
These steps give us the ability to find optimized solutions to difficult problems when we don’t know the exact answer.
This program uses bitstrings as candidates. Of course we can know by looking that a candidate bitstring of 11111
(given a max bitstring length of 5) would maximize our fitness function <code>f(x) = x<sup>2</sup></code>, because `11111` (31 in decimal) is `f(31) = 961`.
However this program is meant to show the procedure of the GA and provide any reference necessary.
 
