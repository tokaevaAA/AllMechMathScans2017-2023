#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
	
	double a=sqrt(74);
	double b=sqrt(53);
	double c=sqrt(29);
	double p=(a+b+c)/2;
	printf("p=%f\n",p);

	double gg=(p*(p-a)*(p-b)*(p-c));
	printf("gg=%f\n",gg);

	double area=sqrt(gg);
	printf("area=%f\n",area);

	
	
	printf("Hello world\n");

	return 0;
}