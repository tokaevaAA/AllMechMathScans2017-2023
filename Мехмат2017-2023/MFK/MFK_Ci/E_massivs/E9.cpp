#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void){
    int mas[10];
    for (int i=0; i<10; i=i+1){
        scanf("%d",&mas[i]);
    }
    
    
    printf("%d ",mas[9]);
    for (int i=0; i<=8; i=i+1){
        printf("%d ",mas[i]);
    }
    printf("\n");
    
	
    return 0;
}
