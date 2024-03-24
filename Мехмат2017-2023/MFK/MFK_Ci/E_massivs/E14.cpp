#include <stdio.h>
#include <stdlib.h>


int main(void){
    
    
    int storage[1000];
    for (int i=0; i<1000; i=i+1){
        storage[i]=0;
    }
    for (int i=0; i<10; i=i+1){
        int a;
        scanf("%d",&a);
        storage[a]+=1;
    }
    
    for (int i=0; i<1000; i=i+1){
        if (storage[i]>1){printf("%d ",i);}
    }
    printf("\n");
    
	
    return 0;
}
