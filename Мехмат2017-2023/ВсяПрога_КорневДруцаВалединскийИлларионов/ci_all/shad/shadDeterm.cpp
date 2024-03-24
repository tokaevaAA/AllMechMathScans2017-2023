#include<stdio.h>
#include<stdlib.h>

int main(){
int mas[100];
mas[0]=4;
mas[1]=13;
int i=0;
for(i=2; i<10;i=i+1){mas[i]=4*mas[i-1]-3*mas[i-2];
		      printf("n=%d determ=%d \n",i+1,mas[i]);}



return 0;
}