#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void recurs_power(int n, int p, int* otv){
    if (p!=0 && p%2==0){ recurs_power(n,p/2,otv); *otv=(*otv)*(*otv); }
    else if (p!=0) { recurs_power(n,p/2,otv);*otv=(*otv)*(*otv)*n;}
}
int main(void){
    int n;
    int p;
    int otv=1;
    scanf("%d%d",&n,&p);
    recurs_power(n,p,&otv);
    printf("%d\n",otv);
	
    return 0;
}
