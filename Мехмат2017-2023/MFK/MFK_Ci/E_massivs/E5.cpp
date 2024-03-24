#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void){
    int mas[10];
    for (int i=0; i<10; i=i+1){
        scanf("%d",&mas[i]);
    }
    int otv=0;
    for (int i=0; i<10; i=i+1){
        if (mas[i]>0){otv+=mas[i];}
    }

    printf("%d\n",otv);
	
    return 0;
}
