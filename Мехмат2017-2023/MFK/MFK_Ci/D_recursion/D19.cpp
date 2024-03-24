#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void cnt_a(int* otv){
    char c;
    if (scanf("%c",&c)==1 && c!='.'){
        int k=(c=='a')?1:0;
        *otv=*otv+k;
        cnt_a(otv);
    }
}
int main(void){
    int otv=0;
    cnt_a(&otv);
    printf("%d\n",otv);
	
    return 0;
}
