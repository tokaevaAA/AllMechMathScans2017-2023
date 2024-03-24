#include<stdio.h>
#include<stdlib.h>

int get_modul(int x){
    return (x>=0)?x:-x;
}
int main(void){

    int x;
    scanf("%d",&x);
    x=get_modul(x);
    printf("%d\n",x);
    
	
    return 0;
}
