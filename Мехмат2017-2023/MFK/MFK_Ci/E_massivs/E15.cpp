#include <stdio.h>
#include <stdlib.h>


int main(void){
    
    
    int storage1[10];
    int storage2[10];
    int i1=0;
    int i2=0;
    
    for (int i=0; i<10; i=i+1){
        storage1[i]=0;
        storage2[i]=0;
    }
    for (int i=0; i<10; i=i+1){
        int a;
        scanf("%d",&a);
        if (a>0){storage1[i1]=a; i1+=1;}
        if (a<0){storage2[i2]=a; i2+=1;}
        
    }
    
    for (int i=0; i<10; i=i+1){
        if (storage1[i]==0){break;}
        printf("%d ",storage1[i]);
    }
    for (int i=0; i<10; i=i+1){
        if (storage2[i]==0){break;}
        printf("%d ",storage2[i]);
    }
    printf("\n");
    
	
    return 0;
}
