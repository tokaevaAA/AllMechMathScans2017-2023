#include <stdio.h>
#include <stdlib.h>


int main(void){
    
    int mas[10];
    for (int i=0; i<10; i=i+1){
        scanf("%d",&mas[i]);
    }
    
    for (int i=0; i<10; i=i+1){
        int isone=1;
        for (int j=0; j<10; j=j+1){
            if (mas[i]==mas[j] && i!=j){isone=0; break;}
        }
        if (isone){printf("%d ",mas[i]);}
    }
    
    printf("\n");
    
	
    return 0;
}
