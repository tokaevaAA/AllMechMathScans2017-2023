#include<stdio.h>
#include<stdlib.h>

int main(void){
    
    int a;
    scanf("%d",&a);

    int max_digit=a%10;
    for(int i=0; i<3; i=i+1){if (a%10>max_digit){max_digit=a%10;}; a=a/10;}

    printf("%d\n",max_digit);
    
	
    return 0;
}