#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void){
    int mas[5];
    for (int i=0; i<5; i=i+1){
        scanf("%d",&mas[i]);
    }
    int otv=mas[0];
    for (int i=1; i<5; i=i+1){
        if (mas[i]<otv){otv=mas[i];};
    }

    printf("%d\n",otv);
	
    return 0;
}
