#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void){
    int mas[10];
    for (int i=0; i<10; i=i+1){
        scanf("%d",&mas[i]);
    }
    int max_znach=mas[0];
    int min_znach=mas[0];
    int max_i=0;
    int min_i=0;
    for (int i=1; i<10; i=i+1){
        if (mas[i]<min_znach){min_znach=mas[i]; min_i=i;}
        if (mas[i]>max_znach){max_znach=mas[i]; max_i=i;}
    }

    printf("%d %d %d %d\n",max_i+1, max_znach, min_i+1, min_znach);
	
    return 0;
}
