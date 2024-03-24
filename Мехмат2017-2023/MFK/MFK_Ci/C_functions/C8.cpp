#include<stdio.h>
#include<stdlib.h>


int main(void){
    char letter;
    while(scanf("%c",&letter)==1 && letter!='.'){
        if (letter >= 'a' && letter <= 'z'){printf("%c",letter+'A'-'a');}
        else{printf("%c", letter);}
        
    }
    printf("\n");
    
    
    
    
	
    return 0;
}
