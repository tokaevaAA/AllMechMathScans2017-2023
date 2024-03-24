#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void){
    int mas[10];
    for (int i=0; i<10; i=i+1){
        scanf("%d",&mas[i]);
    }
    int max1=mas[0];
    int max2=mas[1];
    if (max1<max2){max1=mas[1]; max2=mas[0];}
    int flag=0;
    for (int i=2; i<10; i=i+1){
        flag=0;
        if (mas[i]>max1){max2=max1; max1=mas[i]; flag=1;}
        if (mas[i]>max2 && flag==0){max2=mas[i];}
    }

    printf("%d\n",max1+max2);
	
    return 0;
}
