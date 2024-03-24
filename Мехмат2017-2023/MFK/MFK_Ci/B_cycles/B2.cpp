#include<stdio.h>
#include<stdlib.h>

int main(void){

    int a;
    int b;
    scanf("%d%d",&a,&b);
    for(int i=a; i<=b; i=i+1){printf("%d ",i*i);}
    printf("\n");
	
    return 0;
}