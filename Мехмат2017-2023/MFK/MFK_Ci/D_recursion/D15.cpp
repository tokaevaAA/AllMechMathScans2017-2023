#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max(int m){
    int a;
    if (scanf("%d",&a)==1 && a!=0){
        if (a>m){return find_max(a);}
        else{return find_max(m);}
    }
    else{return m;}
}

int main(void){
    int a;
    if (scanf("%d",&a)==1 && a!=0){
        int otv=find_max(a);
        printf("%d\n",otv);
    }
    return 0;
}
