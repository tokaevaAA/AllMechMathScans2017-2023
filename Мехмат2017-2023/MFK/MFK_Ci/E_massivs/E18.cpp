#include <stdio.h>
#include <stdlib.h>


int main(void){
    
    int n;
    scanf("%d",&n);
    
    int mas[10];
    for (int i=0; i<10; i=i+1){
        mas[i]=0;
    }
    
    for (int i=2; i<=n; i=i+1){
        for (int j=2; j<10; j=j+1){
            if (i%j==0){mas[j]+=1;}
        }
    }
    
    for (int i=2; i<10; i=i+1){
        printf("%d %d\n",i,mas[i]);
    }
    
	
    return 0;
}
