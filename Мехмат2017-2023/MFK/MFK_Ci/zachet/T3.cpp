#include<stdio.h>
#include<stdlib.h>

int big_count(){
    char c;
    if (scanf("%c",&c)==1 &&  c!='.'){
        if ('A'<=c && c<= 'Z'){return 1+big_count();}
        else {return big_count();}
    }
    
    else {return 0;}
}
int main(void){
    int otv=big_count();
    printf("%d\n",otv);
	
    return 0;
}
