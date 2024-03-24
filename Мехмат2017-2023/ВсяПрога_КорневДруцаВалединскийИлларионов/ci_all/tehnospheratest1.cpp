#include <iostream>
#include <string>

void pechat(int v){
	std::cout << "it is int\n";

}

void pechat(bool v){
	std::cout << "it is bool\n";

}

void pechat(std::string v){
	std::cout << "it is std::string\n";

}

int main(void){
	
		
	pechat("Hello world\n");

	return 0;
}