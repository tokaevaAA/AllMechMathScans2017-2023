#include<stdio.h>
#include<stdlib.h>

void reverse_string(){
    char c;
    scanf("%c",&c);
    if (c=='.'){return;}
    else{reverse_string(); printf("%c",c);}
}

int main(void){
    
    reverse_string();
	
    return 0;
}
