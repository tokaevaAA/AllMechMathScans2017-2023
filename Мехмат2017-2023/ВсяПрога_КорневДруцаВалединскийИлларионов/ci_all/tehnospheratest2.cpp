#include <stdio.h>
#include <string>

int main(void){
	char ch='A';
	printf("sizeof(ch) = %d\n",sizeof(ch));
	printf("sizeof('A') = %d\n",sizeof('A'));
	printf("sizeof(5) = %d\n",sizeof(5));
	printf("sizeof(3.14f) = %d\n",sizeof(3.14f));
		
	printf("Hello world\n");

	return 0;
}