/*
    Comparing QuickSort to MergeSort
    Cs2040 assignment 2
    Mitchell VanderHoek
*/

#include <stdlib.h>
#include <time.h>
#include "sorting.hpp"
#include <iostream>

int main(){
    const int size = 10000000; // There's 10 million here. 
    int* array0 = new int[size]; // Array for merge sort.
    int* array1 = new int[size]; // Array for quick sort.
    MergeSorter merging;
    QuickSorter quickly;

    srand(time(NULL)); // Generate a seed.
    
    // A random array of ten million elements is generated then it's sorted using a different
    // algorithm for the same data. This is done 100 times.
    for(int i = 0; i < 100; i++ ){
        // Create random array of ten thousand values.
        for(int j = 0, tmp; j < size; j++){
            tmp = (rand() % 10000000) + 1;  // This isn't necessary.
            array0[j] = tmp;
            array1[j] = tmp;
        }
        
        // Perform merge sort then display number of comparisons.
        merging.startSorting(array0, 0, size - 1);
        printf("\nMergesort %d number of comparisons: %d\n", (i+1), merging.getCountOfComparisons());

        // Perform quick sort then display number of comparisons.
        quickly.startSorting(array1, 0, size - 1);
        printf("\nQuicksort %d number of comparisons: %d\n", (i+1), quickly.getCountOfComparisons());
    }
    delete array0;
    delete array1;

    return 0;
}