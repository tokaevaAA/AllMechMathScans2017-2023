#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void){
    int mas[12];
    for (int i=0; i<12; i=i+1){
        scanf("%d",&mas[i]);
    }
    double otv=0;
    for (int i=0; i<12; i=i+1){
        otv+=mas[i];
    }

    printf("%0.2f\n",otv/12);
	
    return 0;
}
