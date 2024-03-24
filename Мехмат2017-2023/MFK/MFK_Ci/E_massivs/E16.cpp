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
    
    int cnt_max=0;
    int max_znach;
    for (int i=0; i<1000; i=i+1){
        if (storage[i]>cnt_max){cnt_max=storage[i]; max_znach=i;};
    }
    printf("%d\n",max_znach);
    
	
    return 0;
}
