MergeSort vs QuickSort: A Comparison of Algorithms
Cs2040 assignment 2040
Mitchell VanderHoek

Description:

    This uses the mergesort and quicksort algorithms to sort 10 million randomly generated integers 100 times. It outputs the
    number of comparisons for each iteration and for each algorithm. Since the elements are "randomly" distributed, it's unlikely
    that quicksort's worst case will be encountered. 

Usage:

    I provided a makefile that allows compilation and a make clean option to delete the .o and .exe.

    After compilation, run the program (./main). The executable produced will be main.exe. After running it, it will take quite 
    a bit of time for it to finish. You may change this yourself in the main.cpp source file, but for a good test, I thought 
    running it on a large sample size would be better.

Compatibility:

    The program was compiled using the GDB compiler in a WSL2.0 running Ubuntu 20.14LTS environment. The header files: stdlib.h, 
    time.h and iostream are used. sorting.hpp is where the class declarations for MergeSorter and QuickSorter are located.
    