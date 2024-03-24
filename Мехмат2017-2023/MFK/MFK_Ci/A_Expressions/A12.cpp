#include<stdio.h>
#include<stdlib.h>

int main(void){
    
    int a;
    scanf("%d",&a);

    int sum=0;
    for(int i=0; i<3; i=i+1){sum+=a%10; a=a/10;}

    printf("%d\n",sum);
    
	
    return 0;
}