#include<stdio.h>
#include<stdlib.h>

int main(void){
    
    int a;
    scanf("%d",&a);

    int prod=1;
    for(int i=0; i<3; i=i+1){prod*=a%10; a=a/10;}

    printf("%d\n",prod);
    
	
    return 0;
}