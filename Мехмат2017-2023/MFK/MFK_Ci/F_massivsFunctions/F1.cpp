#include <stdio.h>
#include <stdlib.h>


void sort_array(int size, int a[]){
    for (int i=size-2; i>=0; i=i-1){
        for (int j=i; j<=size-2; j=j+1){
            if (a[j]>a[j+1]){
                int tmp=a[j];
                a[j]=a[j+1];
                a[j+1]=tmp;
            }
        }
        printf("\n");
    }
    
}



//int main(void){
//    int mas[10];
//    for (int i=0; i<10; i=i+1){
//        scanf("%d",&mas[i]);
//    }
//    
//
//    
//    sort_array(10, mas);
//    
//    for (int i=0; i<=9; i=i+1){
//        printf("%d ",mas[i]);
//    }
//    printf("\n");
//    
//    
//    return 0;
//}

