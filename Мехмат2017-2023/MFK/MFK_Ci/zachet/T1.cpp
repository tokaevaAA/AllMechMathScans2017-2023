#include<stdio.h>
#include<stdlib.h>

int is_array_down(int a[], int size){
    int otv=1;
    int prev=a[0];
    for (int i=1; i<size; i=i+1){
        if (a[i]>=prev){otv=0; break;}
        prev=a[i];
    }
    return otv;
}

int main(void){
    int dlina=30;
    int* mas = (int*)malloc(dlina*sizeof(int));
    for (int i=0; i<dlina; i=i+1){
        scanf("%d",&mas[i]);
    }
    
    int otv=is_array_down(mas, dlina);
    
    if (otv==1){printf("YES\n");}
    else {printf("NO\n");}
    free(mas);
	
    return 0;
}
