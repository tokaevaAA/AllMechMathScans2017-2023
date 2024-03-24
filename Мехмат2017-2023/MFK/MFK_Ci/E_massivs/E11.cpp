#include <stdio.h>
#include <stdlib.h>


int comparator(const void* a, const void* b){
    return (*(int*)a)%10-(*(int*)b)%10;
}

int main(void){
    int mas[10];
    for (int i=0; i<10; i=i+1){
        scanf("%d",&mas[i]);
    }
    
    qsort(mas,10,sizeof(int),comparator);
    for (int i=0; i<=9; i=i+1){
        printf("%d ",mas[i]);
    }
    printf("\n");
    
	
    return 0;
}
