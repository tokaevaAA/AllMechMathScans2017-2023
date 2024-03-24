#include<stdio.h>
#include<stdlib.h>

int main(void){
    
    int a;
    scanf("%d",&a);

    if (a==12 || a==1 || a==2){printf("winter\n");}  
    else if (a==3 || a==4 || a==5){printf("spring\n");}  
    else if (a==6 || a==7 || a==8){printf("summer\n");}  
    else if (a==9 || a==10 || a==11){printf("autumn\n");}    
	
    return 0;
}