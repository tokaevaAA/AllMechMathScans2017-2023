#include <stdio.h>
#include <stdlib.h>


int comparator1(const void* a, const void* b){
    return (*(int*)a)-(*(int*)b);
}

int comparator2(const void* a, const void* b){
    return -(*(int*)a)+(*(int*)b);
}

int main(void){
    int mas[10];
    for (int i=0; i<10; i=i+1){
        scanf("%d",&mas[i]);
    }
    
    qsort(mas,5,sizeof(int),comparator1);
    qsort(mas+5,5,sizeof(int),comparator2);
    for (int i=0; i<=9; i=i+1){
        printf("%d ",mas[i]);
    }
    printf("\n");
    
	
    return 0;
}
