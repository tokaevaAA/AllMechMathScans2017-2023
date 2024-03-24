#include<stdio.h>
#include<stdlib.h>


void pechat_nech(){
    int a;
    if (scanf("%d",&a)==1 && a!=0){
        if (a%2==1 || a%2==-1){printf("%d ",a);}
        pechat_nech();
    }
}

int main(void){
    
    pechat_nech();
    printf("\n");
	
    return 0;
}
