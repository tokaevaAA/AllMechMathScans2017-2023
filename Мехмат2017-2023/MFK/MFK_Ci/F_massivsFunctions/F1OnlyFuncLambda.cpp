#include <stdio.h>
#include <stdlib.h>


void sort_array(int size, int a[]){
    int(*my_func)(const void*, const void*) = [](const void* a, const void* b){
        return (*(int*)a)%10-(*(int*)b)%10;
    };
    
    qsort(a,size,sizeof(int), my_func);
    
}


