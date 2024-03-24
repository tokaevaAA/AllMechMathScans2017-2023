#include<stdio.h>
#include<stdlib.h>

int get_mean(int a, int b){
    return 0.5*(a+b);
}
int main(void){

    int a;
    int b;
    scanf("%d %d",&a,&b);
    int otv=get_mean(a,b);
    printf("%d\n",otv);
    
	
    return 0;
}
