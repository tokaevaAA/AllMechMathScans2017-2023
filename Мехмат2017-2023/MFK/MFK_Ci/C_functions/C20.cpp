#include<stdio.h>
#include<stdlib.h>
#include <math.h>




int main(void){
    char c;
    int cnt_opened=0;
    int cnt_closed=0;
    int otv=1;
    while (scanf("%c",&c)==1 && c!='.'){
        if (c=='('){cnt_opened+=1;}
        if (c==')'){cnt_closed+=1;}
        if (cnt_closed>cnt_opened){otv=0; break;}
    }
    if (cnt_opened!=cnt_closed){otv=0;}
    if (otv==1){printf("YES\n");}
    else {printf("NO\n");}
    
    
    
	
    return 0;
}
