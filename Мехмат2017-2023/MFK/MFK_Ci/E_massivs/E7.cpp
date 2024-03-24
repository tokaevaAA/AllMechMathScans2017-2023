#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void){
    int mas[10];
    for (int i=0; i<10; i=i+1){
        scanf("%d",&mas[i]);
    }
    
    int dlina=10;
    
    for (int i=0; i<=dlina/4; i=i+1){
        //printf("%d %d\n", mas[i],mas[int(dlina/2)-1-i]);
        int tmp=mas[i];
        mas[i]=mas[dlina/2-1-i];
        mas[dlina/2-1-i]=tmp;
        //printf("%d %d\n", mas[i],mas[int(dlina/2)-1-i]);
    }
    
    
    for (int i=dlina/2; i<=dlina/2+dlina/4; i=i+1){
        int tmp=mas[i];
        mas[i]=mas[(dlina-1)-(i-dlina/2)];
        mas[(dlina-1)-(i-dlina/2)]=tmp;
    }
    
    for (int i=0; i<=9; i=i+1){
        printf("%d ",mas[i]);
    }
    printf("\n");
    
	
    return 0;
}
