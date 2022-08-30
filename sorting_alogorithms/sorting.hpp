/*
    Comparing QuickSort to MergeSort
    Cs2040 assignment 2
    Mitchell VanderHoek
*/
#ifndef sorting_hpp
#define sorting_hpp

class MergeSorter{
    private:
        long long int countOfComparisons; // Keeps track of how many comparisons.
        void merge(int[], int, int, int); 
        void mergeSort(int[], int, int);
    public:
        MergeSorter() : countOfComparisons(0){} // Constructor
        void startSorting(int[], int, int);
        int getCountOfComparisons() const{return countOfComparisons;}
};

class QuickSorter{
    private:
        long long int countOfComparisons; // Keeps track of how many comparisons.
        void swap(int*, int*);
        int partition(int[], int, int);
        void quickSort(int[], int, int);
    public:
        QuickSorter() : countOfComparisons(0){} // Constructor
        void startSorting(int[], int, int);
        int getCountOfComparisons() const{return countOfComparisons;}
};

#endif