#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <new>
#include"AVL-tree.h"


using namespace std;

class Double{
	private:
		double db;
	public:
		Double(){}
		Double(double d0){db=d0;}
		Double(const Double& dd){db=dd.db;}
		~Double(){}
		void pechat()const{ printf("%0.2f\n",db); }
		int operator<  (const Double& x)const {return db<x.db;}
		int operator>  (const Double& x)const {return db>x.db;}
		
		const Double& operator=(const Double& x){db=x.db; return *this;}

	
	

};

class Int{
	private:
		int db;
	public:
		Int(){}
		Int(int d0){db=d0;}
		Int(const Int& dd){db=dd.db;}
		~Int(){}
		void pechat()const{ printf("%d\n",db); }
		int operator<  (const Int& x)const {return db<x.db;}
		int operator>  (const Int& x)const {return db>x.db;}
		
		const Int& operator=(const Int& x){db=x.db; return *this;}

	
	

};






struct  Str{
    char* stroka;
    Str(){stroka=0;}
    Str(const char* a){stroka=new char[strlen(a)+1]; strcpy(stroka,a);}
    ~Str(){delete []stroka;}
    bool operator<(const Str &x)const{return strcmp(stroka,x.stroka)<0;}
    bool operator>(const Str &x)const{return strcmp(stroka,x.stroka)>0;}
    bool operator==(const Str &x)const{return strcmp(stroka,x.stroka)==0;}
    const Str&  operator=(const Str &x){if (stroka) delete []stroka; stroka=new char[strlen(x.stroka)+1]; strcpy(stroka,x.stroka); return *this;}
    void pechat()const {printf("%s \n",stroka);}





};


void dobavlenie_udalenie_small_tree(){
    
	
	Tree<Double> Myderevo;
    	
	FILE*f;
	f=fopen("input.txt","r");
	double elem;
	int k=fscanf(f,"%lf",&elem);
	while(k==1){
	Myderevo.Push(Double(elem));
	k=fscanf(f,"%lf",&elem);
	Myderevo.pechat();
	}
	Myderevo.pechat();
	Myderevo.klevelpechat(4);
	
	printf("depth= %d \n",Myderevo.Depth());
	Myderevo.Withdraw(Double(10));
	Myderevo.Withdraw(Double(4));
	Myderevo.Withdraw(Double(1));
	Myderevo.Withdraw(Double(3.5));
	Myderevo.pechat();
	printf("depth= %d \n",Myderevo.Depth());
	
	Myderevo.klevelpechat(7);
	Myderevo.klevelpechat(3);

	fclose(f);




}



void very_big_tree(){

	FILE*g;
	g=fopen("100strok.txt","w");
	int j=0;
	for(j=0; j<1000000; j=j+1){ fprintf(g,"%d \n",rand() % 1000000);}
	//for(j=0; j<1048576; j=j+1){ fprintf(g,"%d \n",j);}
	
	fclose(g);


	FILE*h;
	h=fopen("100strok.txt","r");
	if (h==0) {printf("Cannot open\n");}
	
	Tree<Double> Bigderevo;

	double element;
	int s=fscanf(h,"%lf",&element);
	//printf("prochitali= %d \n",s);
	//printf("element=%f \n",element);
	while(s==1){
	Bigderevo.Push(Double(element));
	s=fscanf(h,"%lf",&element);
	}
	//Bigderevo.pechat();
	printf("depth= %d \n",Bigderevo.Depth());
	Bigderevo.Test();

	fclose(h);

}




void not_long_stroki(){

	Tree<Str> Derevostrok;
	Derevostrok.Push(Str("abc"));
	Derevostrok.Push(Str("abcd"));
	Derevostrok.Push(Str("kl"));

	printf("sravnenie=%d %d \n", strcmp("abcd","abc"),Str("abcd")<Str("abc"));
	Derevostrok.pechat();
	//printf("razmer Bigderevo= %d \n",Bigderevo.Size());
	printf("razmer Derevostrok= %d \n",Derevostrok.Size());	
}	








void long_text(){

	FILE*m;
	m=fopen("stroki.txt","r");
	if (m==0) {printf("Cannot open\n");}
	
	Tree<Str> Strokiderevo;
	
	char mas[256];
	//char mas1[256];
	
	int t=0; 
	int q;
	q=fscanf(m,"%s",mas);
	
	
	while(q==1){
	Str(mas).pechat();

	for (t=0; t<256;t=t+1){if ((mas[t] == ',')||(mas[t]=='.')||(mas[t]==';')) { mas[t]=0;  }}
	

	 Strokiderevo.Push(Str(mas));
	
	
	q=fscanf(m,"%s",mas);
	printf("razmer= %d \n",Strokiderevo.Size());
	//Strokiderevo.pechat();
	}
	Strokiderevo.pechat();
	
}












int main(){
	printf("Hello\n");
	
	dobavlenie_udalenie_small_tree();
	
	//very_big_tree();  
	
	//not_long_stroki();  
	
	//long_text();
	
    	printf("Goodbye\n");
	

    

    return 0;

}
