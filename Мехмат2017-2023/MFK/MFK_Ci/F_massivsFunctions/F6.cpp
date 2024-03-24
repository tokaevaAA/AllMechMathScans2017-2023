#include <stdio.h>
#include <stdlib.h>


int main(void){
    int mas[100];
    
    for (int i=0; i<100; i=i+1){
        scanf("%d",&mas[i]);
        
    }

    int otv=0;
    for (int i=0; i<100; i=i+1){
        for (int j=i+1; j<100; j=j+1){
            if (mas[i]==mas[j]){otv=1; break;}
        }
    }
    if (otv==1){printf("YES\n");}
    else{printf("NO\n");}
    


    return 0;
}



