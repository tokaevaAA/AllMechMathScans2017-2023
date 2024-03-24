#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define N 300
#define L0 250000
#define P 1845.712917

class data{
    public:
	int year;
	double Lk;
	double Ik;
	double deltaLk;
	double loanLeft;
    
    data(){year=0; Lk=0; Ik=0; deltaLk=0; loanLeft=0;}
    void pechat(void){printf("%d %f %f %f %f \n", year,Lk,Ik,deltaLk,loanLeft);}
    void pechatFile(FILE*f){
			  fprintf(f,"%d      %f     %f     %f      %f \n",year,Lk,Ik,deltaLk,loanLeft);
			  }

	


};

int main(void){
    printf("Hello\n");
    
    FILE*f;
    f=fopen("output.txt","w");
    fprintf(f,"year  Lk               Ik              deltaLk          loanLeft\n");

    double tmp=pow(12,-1);
    

    double i_1=0.035;
    double i_1_eff=pow(1+i_1,tmp) -1;
    double i_2=0.075;
    double i_2_eff=pow(1+i_2,tmp) -1;
    
    
    printf("i_1_eff=%f\n",i_1_eff);
    printf("i_2_eff=%f\n",i_2_eff);

    double L18=L0*pow(1+i_1_eff,18); 
    printf("L18=%f\n",L18);

    double p1=(1-pow(1+i_1_eff,-18))/i_1_eff;
    printf("p1=%f\n",p1);
    double p2=(1-pow(1+i_2_eff,-264))/i_2_eff;
    printf("p2=%f\n",p2);
    double p3=p2*pow(1+i_1_eff,-18);
    printf("p3=%f\n",p3);

    double price= p1+p3;
    printf("price=%f\n",price);
   
    double month_installment= L18/price;
    printf("month_installment=%f\n",month_installment);





   


    data* mas=(data*)malloc((N+1)*sizeof(data));


    mas[1].year=1;
    mas[1].Lk=L0;
    mas[1].Ik=(i_1_eff)*(mas[1].Lk); 
    mas[1].deltaLk=-mas[1].Ik;
    mas[1].loanLeft=(1+i_1_eff)*mas[1].Lk ;

    for(int i=2; i<=18; i=i+1){ mas[i].year=i;
				mas[i].Lk=mas[i-1].loanLeft;
				mas[i].Ik=(i_1_eff)*(mas[i].Lk); 
    				mas[i].deltaLk=-mas[i].Ik;
    				mas[i].loanLeft=(1+i_1_eff)*mas[i].Lk ;
				}

     for(int i=19; i<=36; i=i+1){ mas[i].year=i;
				mas[i].Lk=mas[i-1].loanLeft;
				mas[i].Ik=(i_1_eff)*(mas[i].Lk); 
    				mas[i].deltaLk=P-mas[i].Ik;
    				mas[i].loanLeft=(1+i_1_eff)*mas[i].Lk -P ;

				}

    for(int i=37; i<=300; i=i+1){ mas[i].year=i;
				mas[i].Lk=mas[i-1].loanLeft;
				mas[i].Ik=(i_2_eff)*(mas[i].Lk); 
    				mas[i].deltaLk=P-mas[i].Ik;
    				mas[i].loanLeft=(1+i_2_eff)*mas[i].Lk -P ;

				}

    if(mas[300].loanLeft <0) mas[300].loanLeft=0;
        
    


    for(int i=1; i<=300; i=i+1) mas[i].pechatFile(f);
    
    fclose(f);
    free(mas);


    return 0;

}
