#include <stdio.h>
#include <stdlib.h>



int main(void){
    int mas[10];
    for (int i=0; i<10; i=i+1){
        scanf("%d",&mas[i]);
    }
    
    
    for (int i=0; i<=9; i=i+1){
        if ((mas[i]/10)%10==0) { printf("%d ",mas[i]);}
    }
    printf("\n");
    
	
    return 0;
}
