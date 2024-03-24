#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int akkerman(int m, int n){
    if (m==0){return n+1;}
    else if (m>0 && n==0){return akkerman(m-1,1);}
    else {return akkerman(m-1, akkerman(m,n-1));}
}
int main(void){
    int m;
    int n;
    scanf("%d%d",&m,&n);
    int otv=akkerman(m, n);
    printf("%d\n",otv);
	
    return 0;
}
