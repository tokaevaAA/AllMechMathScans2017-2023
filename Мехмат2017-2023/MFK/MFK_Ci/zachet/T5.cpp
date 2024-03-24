#include<stdio.h>
#include<stdlib.h>

void print_rare_symbol(char s[], int size){
    int mas[27];
    for (int i=0; i<27; i=i+1){
        mas[i]=0;
    }
    for (int i=0; i<size; i=i+1){
        if ('a'<=s[i] && s[i]<='z'){
            mas[s[i]-'a']+=1;
        }
    }
    int min_cnt=0;
    
    for (int i=0; i<27; i=i+1){
        if (min_cnt==0 && mas[i]>0 ){min_cnt=mas[i];}
        if (min_cnt >0 && mas[i]!=0 && mas[i]<min_cnt){min_cnt=mas[i];}
    }
    for (int i=0; i<27; i=i+1){
        if (mas[i]==min_cnt ){printf("%c %d\n",i+'a',mas[i]); break;}
        
    }
    
}


int main(void){
    char mas[1001];
    int i=0;
    char c;
    while (scanf("%c",&c)==1 && c!='\n' ){
        mas[i]=c;
        i=i+1;
    }
    print_rare_symbol(mas,i);
    
	
    return 0;
}
