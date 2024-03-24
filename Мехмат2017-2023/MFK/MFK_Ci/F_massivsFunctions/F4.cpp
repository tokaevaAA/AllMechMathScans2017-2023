#include <stdio.h>
#include <stdlib.h>





int main(void){
    int mas[10];
    for (int i=0; i<10; i=i+1){
        mas[i]=0;
    }

    char a;
    
    int cnt_nuls=0;

    while (scanf("%c",&a)==1 && a!='.'){
        if ('0'<=a && a<='9'){
            int n=a-'0';
            if (n%10==0){cnt_nuls+=1;}
            mas[n%10]+=1;
            n=n/10;
        }
    }

    if (cnt_nuls!=0){
        printf("%d %d\n",0, cnt_nuls);
    }
    for (int i=1; i<10; i=i+1){
        if (mas[i]>0){printf("%d %d\n",i, mas[i]);}
    }
    


    return 0;
}

