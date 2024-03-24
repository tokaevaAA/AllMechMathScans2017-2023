#include <stdio.h>
#include <stdlib.h>


void sort_array(int size, int a[]){
    for (int i=size-2; i>=0; i=i-1){
        for (int j=i; j<=size-2; j=j+1){
            if ((a[j]%2==1 || a[j]%2==-1) && (a[j+1]%2==0)){
                int tmp=a[j];
                a[j]=a[j+1];
                a[j+1]=tmp;
            }
        }
    }
    
}



int main(void){
    int mas[20];
    for (int i=0; i<20; i=i+1){
        scanf("%d",&mas[i]);
    }



    sort_array(20, mas);

    for (int i=0; i<=19; i=i+1){
        printf("%d ",mas[i]);
    }
    printf("\n");


    return 0;
}

