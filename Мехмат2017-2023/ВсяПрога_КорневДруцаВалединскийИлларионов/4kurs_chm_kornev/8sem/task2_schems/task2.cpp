#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using GetNextFunc = double (*)(double h, double A, double y_k, double y_km1, char* scheme_name);
using Gety0y1Func = std::tuple<double, double> (*)(double h, double A);




double get_y_kp1(double h, double A, double y_k, double y_km1, char* scheme_name){
    double otv=0.0;
    if (strcmp(scheme_name,"Scheme1")==0){otv=y_k*(1.0-h*A)+y_km1*0.0;}
    else if (strcmp(scheme_name,"Scheme2")==0){otv=y_k/(1.0+h*A)+y_km1*0.0;}
    else if (strcmp(scheme_name,"Scheme3")==0){otv=y_k*(1.0-h*A*0.5)/(1.0+h*A*0.5)+y_km1*0.0;}
    else if (strcmp(scheme_name,"Scheme4")==0){otv=y_k*(-2*h*A)+y_km1*1.0;}
    else if (strcmp(scheme_name,"Scheme5")==0){otv=y_k*2/1.5+y_km1*(-0.5-A*h)/1.5;}
    else {printf("Bad scheme_name in get_y_kp1\n");}
    return otv;

}

std::tuple<double,double> get_y0y1(double h, double A, char* scheme_name){
    double y0=1.0;
    double y1=0.0;
    if (strcmp(scheme_name,"Scheme1")==0){y1=y0*(1.0-h*A);}
    else if (strcmp(scheme_name,"Scheme2")==0){y1=y0/(1.0+h*A);}
    else if (strcmp(scheme_name,"Scheme3")==0){y1=y0*(1.0-h*A*0.5)/(1.0+h*A*0.5);}
    else if (strcmp(scheme_name,"Scheme4")==0){y1=1.0-A*h;}
    else if (strcmp(scheme_name,"Scheme5")==0){y1=1-A*h;}
    else {printf("Bad scheme_name in get_y0y1\n");}
    return std::make_tuple(y0,y1);

}





double get_err(double y0, double y1, double a, double b, double A, double h, GetNextFunc getnextfunc,char* scheme_name,FILE* ferr){
	double y_tek;
	double x_tek;
        double y_prevprev=y0;
	double y_prev=y1;
	double tek_err;
        double max_err=abs(y0-exp(-A*a));
	max_err=std::max<double>(max_err,abs(y1-exp(-A*(a+h))));

	for (int i=2; i<=(b-a)/h; i=i+1){x_tek=a+h*i;
					 fprintf(ferr,"h=%f x_tek=%f A*x_tek=%f exp=%e\n",h,x_tek,A*x_tek,exp(-A*x_tek));
					 y_tek=getnextfunc(h,A,y_prev,y_prevprev,scheme_name);
					 tek_err=abs(y_tek-exp(-A*x_tek));	
				  	 max_err=std::max<double>(max_err,tek_err);
					 y_prevprev=y_prev;
					 y_prev=y_tek;				
					 }
	return max_err;
}


//===================================================================================================================

int main(int argc, char** argv){
    printf("Hello! e^(-1000)=%e\n ",exp(-1000.0));
    
    if (argc != 2) {printf("Usage: ./a.out Scheme1/Scheme2/Scheme3/Scheme4/Scheme5 \n"); return -1;}
    
    double a = 0.0;
    double b = 1.0;
    char* scheme_name=argv[1];

    
    
    GetNextFunc getnextfunc=get_y_kp1;
    

    char* output_name =(char*)malloc(50*(sizeof(char)));
    output_name=strcpy(output_name,scheme_name);
    output_name=strcat(output_name,".txt");
    FILE*f=fopen(output_name,"w");
    free(output_name);
    double err=0.0;
    double prev_err=0.0;
    double h=0.0;
    double h_prev=0.0;
    int j_last=7;
    double p;
    double masA[3]={1000.0,1000.0,1000.0};
    FILE*ferr=fopen("FERR","w");
    for (int i=0; i<3; i=i+1){
	double A=masA[i];
	printf("A=%f\n",A);
	h=1e-1;
    	for (int j=1; j<=j_last; j=j+1){std::tuple<double,double> res=get_y0y1(h,A,scheme_name);
				   double y0=std::get<0>(res);
				   double y1=std::get<1>(res);
 				   //printf("y0=%f y1=%f\n",y0,y1);
				   err=get_err(y0,y1, a, b, A, h, getnextfunc, scheme_name,ferr);
    			           printf("h=%e err=%e\n",h, err);
				   if(i==2 and j>=3){fprintf(f,"%f %f\n",log(1/h),log(1/err));}
				   if (j==5){p=(log(1/err)-log(1/prev_err))/(log(1/h)-log(1/h_prev));}
				   if (j!=j_last){
				   	     prev_err=err;
				             h_prev=h;
				             h=h/10;
					     }
				  }
				  printf("p=%f\n",p);
    }
    fclose(f);
    
    


    
    
    printf("Goodbuy!\n");
        
    return 0;

}
