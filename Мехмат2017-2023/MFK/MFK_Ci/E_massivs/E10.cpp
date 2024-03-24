#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void){
    int mas[12];
    for (int i=0; i<12; i=i+1){
        scanf("%d",&mas[i]);
    }
    
    
    for (int i=12-4; i<12; i=i+1){
        printf("%d ",mas[i]);
    }
    for (int i=0; i<=7; i=i+1){
        printf("%d ",mas[i]);
    }
    printf("\n");
    
	
    return 0;
}
