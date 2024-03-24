#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void){
    int mas[5];
    double otv=0;
    for (int i=0; i<5; i=i+1){
        scanf("%d",&mas[i]);
    }
    for (int i=0; i<5; i=i+1){
        otv+=mas[i];
    }
    otv/=5;
    printf("%0.3f\n",otv);
	
    return 0;
}
