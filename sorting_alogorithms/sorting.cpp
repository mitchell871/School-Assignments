/*
    Comparing QuickSort to MergeSort
    Cs2040 assignment 2
    Mitchell VanderHoek
*/

#include "sorting.hpp"

/*
    Merges subsets of array[]. 
    First is array[begin..middle]
    Second is array[middle+1..end]

    @param int[] Array to sort.
    @param int Begin.
    @param int Middle.
    @param int End.
*/
void MergeSorter::merge(int array[], int const left, int const middle, int const right){
    auto const subsetArray0 = middle - left + 1;  
    auto const subsetArray1 = right - middle;

    // Temporary arrays
    auto *leftArray = new int[subsetArray0],
         *rightArray= new int[subsetArray1];
    
    // Copy the data to the temporary arrays
    for(auto i = 0; i < subsetArray0; i++)
        leftArray[i] = array[left + i];
    for(auto j = 0; j < subsetArray1; j++)
        rightArray[j] = array[middle + 1 + j];
    
    // Initial indices. 
    auto indexsubsetArray0 = 0,     
         indexsubsetArray1 = 0;     
    int  indexMergedArray  = left;

    // Merge the temporary arrays back into one array[left...right]
    while(indexsubsetArray0 < subsetArray0 && indexsubsetArray1 < subsetArray1){
        (leftArray[indexsubsetArray0] <= rightArray[indexsubsetArray1])?
            array[indexMergedArray] = leftArray[indexsubsetArray0++] : array[indexMergedArray] = rightArray[indexsubsetArray1++];
        indexMergedArray++;
        countOfComparisons++;            
    }

    // If there are elements, copy the remaining elements of the left/right arrays.
    // Indices are incremented on same line.
    while(indexsubsetArray0 < subsetArray0)
        array[indexMergedArray++] = leftArray[indexsubsetArray0++]; 
    while(indexsubsetArray1 < subsetArray1)
        array[indexMergedArray++] = rightArray[indexsubsetArray1++];

    // Free memory. I forgot to do this and it used 28GB of memory before a sigkill was sent by the OS.
    delete leftArray;
    delete rightArray;
}

/*
    Recursively divides the elements then merges the elements back into one array.

    @param int[] The array to be sorted.
    @param int Left index.
    @param int Right index of subarray of array to be sorted.
*/
void MergeSorter::mergeSort(int array[], int const begin, int const end){
    if(begin >= end)
        return;
    
    auto middle = begin + (end - begin) / 2;
    mergeSort(array, begin, middle);
    mergeSort(array, middle + 1, end);
    merge(array, begin, middle, end); // Put everything back together.
}

/*
    Start sorting the array. Array[L..R]

    @param int[] Array to sort.
    @param int Left.
    @param int Right.
*/
void MergeSorter::startSorting(int array[], int left, int right){
    countOfComparisons = 0; // Start at 0
    mergeSort(array, left, right);
}

/*
    Swaps two values.

    @param int*
    @param int*
*/
void QuickSorter::swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
    The function takes the last element as pivot, places the pivot element at its correct position
    in the sorted array. It then places all elements smaller than the pivot to the left of the pivot, 
    and all greater elements to the right.

    @param int[]
    @param int Low.
    @param int High.
*/
int QuickSorter::partition(int array[], int low, int high){
    int pivot = array[high];
    int i = (low - 1);

    for(int j = low; j <= high - 1; j++){
        if(array[j] <= pivot){
            i++;
            swap(&array[i], &array[j]);
        }
        countOfComparisons++;
    }

    swap(&array[i + 1], &array[high]);

    return (i + 1);
}

/*
    @param int[] Array to sort.
    @param int Starting index.
    @param int Ending index.
*/
void QuickSorter::quickSort(int array[], int low, int high){
    
    if(low < high){
        // Pivot
        int partitionIndex = partition(array, low, high);

        quickSort(array, low, partitionIndex - 1);
        quickSort(array, partitionIndex + 1, high);
    }
}

/*
    This starts the sorting of the elements.
    
    @param int[] The array to sort.
    @param int Low value.
    @param int High value.
*/
void QuickSorter::startSorting(int array[], int low, int high){
    countOfComparisons = 0; // Start at 0
    quickSort(array, low, high);
}
