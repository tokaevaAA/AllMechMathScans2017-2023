#include <stdio.h>
#include <stdlib.h>


int find_max_array(int size, int a[]){
    int otv=a[0];
    for (int i=1; i<size; i=i+1){
        if (a[i]>otv){otv=a[i];}
    }
    return otv;
}


