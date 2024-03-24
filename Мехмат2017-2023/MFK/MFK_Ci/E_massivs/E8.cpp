#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void){
    int mas[12];
    for (int i=0; i<12; i=i+1){
        scanf("%d",&mas[i]);
    }
    
    int dlina=12;
    
    
    for (int i=0; i<dlina/6; i=i+1){
        int tmp=mas[i];
        mas[i]=mas[dlina/3-1-i];
        mas[dlina/3-1-i]=tmp;
    
    }
    
    
    
    for (int i=dlina/3; i< dlina/3+dlina/6; i=i+1){
        
        int tmp=mas[i];
        mas[i]=mas[2*dlina/3-1-(i-dlina/3)];
        mas[2*dlina/3-1-(i-dlina/3)]=tmp;

    }
    
    
    
    for (int i=2*dlina/3; i<2*dlina/3+dlina/6; i=i+1){
        int tmp=mas[i];
        mas[i]=mas[(dlina-1)-(i-2*dlina/3)];
        mas[(dlina-1)-(i-2*dlina/3)]=tmp;
    }
    
    for (int i=0; i<=11; i=i+1){
        printf("%d ",mas[i]);
    }
    printf("\n");
    
	
    return 0;
}
