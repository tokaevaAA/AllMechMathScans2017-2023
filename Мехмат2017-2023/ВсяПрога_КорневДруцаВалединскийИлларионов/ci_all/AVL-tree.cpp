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



class Str{
	public:
		char* stroka;
	public:
		Str(){stroka=(char*)malloc(1*sizeof(char));}
		Str(char* st){stroka=(char*)malloc(strlen(st)*sizeof(char)); strcpy(stroka,st);}
		~Str(){delete stroka;}
		Str(const Str&x){stroka=(char*)malloc(strlen(x.stroka)*sizeof(char)); strcpy(stroka,x.stroka);}
		const Str& operator=(const Str&x){stroka=(char*)malloc(strlen(x.stroka)*sizeof(char)); 
						  	strcpy(stroka,x.stroka);return *this;}
		void pechat()const{printf("%s \n",stroka);}
		int operator<(const Str& x)const {int otv=0; int q= strcmp(stroka,x.stroka); if (q>0) otv= 0; else if (q<0) otv= 1;return otv;}
		int operator>(const Str& x)const {int otv=0; int q= strcmp(stroka,x.stroka); if (q>0) otv= 1; else if (q<0) otv= 0;return otv;}

};


int chitka(FILE*m,char* kudaklast){
		int otv;
		int z=0; int q=0;
		char mas[256];
		z=0;
		q=fscanf(m,"%c",&mas[0]);
		if (q!=1) return -1;
		z=z+1;
		while(((strcmp(&mas[z-1]," ")!=0))&&(q==1)){q=fscanf(m,"%c",&mas[z]); z=z+1;}
		strcpy(kudaklast,mas);
		return 1;

	}


int main(){
	printf("Hello\n");
	        
/*
	Tree<Double> Myderevo;
    	
	FILE*f;
	f=fopen("input.txt","r");
	double elem;
	int k=fscanf(f,"%lf",&elem);
	while(k==1){
	Myderevo.Push(Double(elem));
	k=fscanf(f,"%lf",&elem);
	}
	Myderevo.pechat();
	
	printf("depth= %d \n",Myderevo.Depth());
	Myderevo.Withdraw(Double(10));
	Myderevo.Withdraw(Double(4));
	Myderevo.Withdraw(Double(1));
	Myderevo.Withdraw(Double(3.5));
	Myderevo.pechat();
	printf("depth= %d \n",Myderevo.Depth());

	fclose(f);
*/

//-----------------------------------------------------------------------
	/*
	FILE*g;
	g=fopen("100strok.txt","w");
	int j=0;
	for(j=0; j<1024; j=j+1){ fprintf(g,"%d \n",rand() % 100);}

	fclose(g);


	FILE*h;
	h=fopen("100strok.txt","r");
	if (h==0) {printf("Cannot open\n");}
	
	Tree<Double> Bigderevo;

	double element;
	int s=fscanf(h,"%lf",&element);
	printf("prochitali= %d \n",s);
	printf("element=%f \n",element);
	while(s==1){
	Bigderevo.Push(Double(element));
	s=fscanf(h,"%lf",&element);
	}
	//Bigderevo.pechat();
	printf("depth= %d \n",Bigderevo.Depth());

	fclose(h);
	*/
	
//-------------------------------------------------------------
	/*
	Tree<Str> Derevostrok;
	Derevostrok.Push(Str("abc"));
	Derevostrok.Push(Str("abcd"));
	Derevostrok.Push(Str("kl"));

	printf("sravnenie=%d %d \n", strcmp("abcd","abc"),Str("abcd")<Str("abc"));

	Derevostrok.pechat();
	//printf("razmer Bigderevo= %d \n",Bigderevo.Size());
	printf("razmer Derevostrok= %d \n",Derevostrok.Size());	
	*/
	
//------------------------------------------------------------
	 FILE*m;
	m=fopen("stroki.txt","r");
	if (m==0) {printf("Cannot open\n");}
	
	Tree<Str> Strokiderevo;
	
	char mas[256];
	

	int q;
	q=fscanf(m,"%s",mas);
	
	while(q==1){
	Str(mas).pechat();
	

	Strokiderevo.Push(Str(mas));
	q=fscanf(m,"%s",mas);
	printf("razmer= %d \n",Strokiderevo.Size());
	//Strokiderevo.pechat();
	}
	//Strokiderevo.pechat();
	
	
	
	
	
    	printf("Goodbye\n");
	

    

    return 0;

}
