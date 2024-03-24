#include<stdio.h>
#include<stdlib.h>

int main(void){
    
    double x1;
    double y1;
    double x2;
    double y2;
    scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);

    double k=(y2-y1)/(x2-x1);
    double b=y1-k*x1;

    printf("%0.2f %0.2f\n",k,b);
    
	
    return 0;
}