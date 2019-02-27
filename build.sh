#!/bin/sh
if [ ! -d ./binaries ]; then
   mkdir ./binaries
fi
g++ main_MaxMinAlgo.cpp -o ./binaries/max_min_algo
g++ main_SecondLargest.cpp -std=c++0x -o ./binaries/second_largest
g++ main_Segmented_Sieve.cpp -o ./binaries/segmented_sieve
g++ main_NPTELAlgoAssg2_Sorting.cpp -o ./binaries/siruseri_singing_championship_Sorting
g++ main_NPTELAlgoAssg3_Graph.cpp -o ./binaries/prisoner_escape_Graph
