/***********
* Artiom Berengard
* ass06
***********/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sorting.h"

/******************
* Function Name: quicksort
* Input: An array of persons, start and stop point, generic person swap function and comparison functions.
* Output: The array of persons sorted as chosen by the main function.
* Function Operation: The quicksort function as studied in the course.
******************/
void quicksort(void* arr, int start, int stop, void(*swap)(void*, int, int), int(*compare)(void*, int, int)) {
    if (start >= stop - 1) {
        return;
    }

    int pivot = start;
    int j = start;
    for (int i = start + 1; i < stop; i++) {

        if ((compare(arr,i,pivot))>0){
            j++;
            if (i != j){
                swap(arr,i,j);
            }
        }

    }
    swap(arr, start, j);
    quicksort(arr, start, j,swap,compare);
    quicksort(arr, j + 1, stop,swap,compare);
}
