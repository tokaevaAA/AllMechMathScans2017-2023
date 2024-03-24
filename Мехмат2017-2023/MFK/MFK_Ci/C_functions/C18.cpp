#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int is_digit(char c){
    int otv=0;
    if ('0'<=c && c<='9'){otv=1;}
    return otv;
}


int main(void){
    char c;
    int cnt=0;
    while (scanf("%c",&c)==1 && c!='.'){
        cnt+=is_digit(c);
    }
    printf("%d\n",cnt);
    
    
    
	
    return 0;
}
