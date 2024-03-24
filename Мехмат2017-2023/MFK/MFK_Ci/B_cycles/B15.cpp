#include<stdio.h>
#include<stdlib.h>

int main(void){

    int cnt_even=0;
    int a;
    while(scanf("%d",&a)==1 && a!=0){if (a%2==0){cnt_even+=1;}}
    printf("%d\n",cnt_even);
    
	
    return 0;
}
