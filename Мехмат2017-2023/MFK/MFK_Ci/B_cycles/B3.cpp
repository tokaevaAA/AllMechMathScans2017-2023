#include<stdio.h>
#include<stdlib.h>

int main(void){

    int a;
    int b;
    scanf("%d%d",&a,&b);
    int sum=0;
    for(int i=a; i<=b; i=i+1){sum=sum+i*i;}
    printf("%d\n",sum);
	
    return 0;
}