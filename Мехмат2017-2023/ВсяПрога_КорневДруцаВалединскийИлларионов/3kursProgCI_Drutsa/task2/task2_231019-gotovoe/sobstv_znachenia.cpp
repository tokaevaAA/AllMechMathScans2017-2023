#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include "Algoritm.h"



#define sobstv_chisla(i) sobstv_chisla[i-1]
#define a(i,j) a[(i-1)*n+(j-1)]
#define b(i,j) b[(i-1)*n+(j-1)]
#define c(i,j) c[(i-1)*n+(j-1)]
#define matrL(i,j) matrL[(i-1)*n+(j-1)]
#define matrU(i,j) matrU[(i-1)*n+(j-1)]

#define L(i) L[(i-1)]
#define U(i) U[(i-1)]
#define LM(i) LM[(i-1)]



int minim(int a, int b){
    return (a<b)?a:b;

}

double special_func(int n, int i, int j){
    double otv=0;
    if (i<n && j<n && i==j) return 1;
    if (i==n) return j;
    if(j==n) return i;
    return otv;

}

double func (int i, int j){
	double otv=0;
	//otv= 1.0/(1+i+j);
	
	otv=fabs(i+j);
	
	//if (i<n && j<n && i==j) return 1;
	//if (i==n) return j;
	//if(j==n) return i;
	return otv;

}

void pechat_matrix(int n, double* a){
    //if (n>15) return;
    //printf("\nStart Pechat matrix:\n");
    for (int i=0; i<(minim(n,5)); i=i+1){
	for (int j=0; j<minim(n,5); j=j+1){
	    printf("%f ",a[i*n+j]);
	}
	printf("\n");
    }
    //printf("End Pechat matrix\n");
}


void pechat_vector(int n, double* b){
    //if (n>15) return;
    //printf("\nStart Pechat vector:\n");
    for (int i=0; i<minim(n,10); i=i+1){
	
	    printf("%f ",b[i]);
	
    }
    printf("\n");
    //printf("End Pechat vector\n");
}




int get_matrix_from_file(int n, double* a,FILE*f){
    int n0; int k;
    k=fscanf(f,"%d",&n0);
    if (k!=1) return -1;
    printf("n0=%d\n",n0);
    if (n0 != n){printf("Matrix size does not match; Program terminates;\n"); return -1;}

    for (int i=1; i<n+1; i=i+1){
	for (int j=1; j<n+1; j=j+1){
	    k=fscanf(f,"%lf ",&a(i,j));
	    if(k!=1) return -1;    
        }
        	
    }
    return 0;
    
}

int get_matrix_po_formule(int n, double*a){
    //printf("get po formule\n");
    for (int i=1; i<n+1; i=i+1){
	for (int j=1; j<n+1; j=j+1){
	    a(i,j)=func(i,j);
	    //a(i,j)=special_func(n,i,j); 
        }
        
    }
    //pechat_matrix(n,a);
    return 0;

}


int get_matrix(int n, double* a,  int argv, char** argc ){
    int otv=0;
    if (argv==3){
    	FILE*f;
    	f=fopen(argc[2],"r"); if (f==0){printf("Cannot open %s\n",argc[2]);return -1;}
	otv= get_matrix_from_file(n,a,f);
        fclose(f);
	}

    else if (argv ==2){
    otv= get_matrix_po_formule(n,a);

    }
    return otv;
	
	
}


/*
void to_3diag_vid_Tij(double* a, int n, int i, int j,int k){
    int stolb; int stroka; double x; double y; double s;

    s =sqrt(a(i,k)*a(i,k) + a(j,k)*a(j,k));
    if (s<0.0000000000000001) {
    //printf("in to_3diag_vid: x^2 +y^2==0 i=%d j=%d\n",i,j);
    }
    
    else{
    double cosinus=a(i,k)/s;
    double sinus=-a(j,k)/s;
    //printf(" cosinus=%f sinus=%f \n",cosinus,sinus);
   
    for (stolb=k; stolb<n+1; stolb=stolb+1){
	x= a(i,stolb);
        y= a(j,stolb);
	a(i,stolb)=x*cosinus - y*sinus;
        a(j,stolb)=x*sinus + y*cosinus;
    }
   
    for (stroka=k; stroka<n+1; stroka=stroka+1){
	x= a(stroka,i);
        y= a(stroka,j);
	a(stroka,i)=x*cosinus - y*sinus;
        a(stroka,j)=x*sinus + y*cosinus;
    }
    }

}

void to_3diag_vid(double* a, int n){
    for (int k=1; k<n-1 ; k=k+1){
        for (int p=k+2; p<n+1; p=p+1){
            to_3diag_vid_Tij(a,n,k+1,p,k);    
        }
        
    }

}

void matrix_mult(int n, double* a, double* b, double* c){
    double s;
    for (int i=1; i<n+1; i=i+1){
        for(int j=1; j<n+1; j=j+1){
	    s=0;
	    for(int k=1; k<n+1; k=k+1){
		    s=s+a(i,k)*b(k,j);
		    		}
	    c(i,j)=s;
	    	
	}

    }

}

void count_L_LM_U(double* a, int n,  double lamda){
    //for (int i=1; i<n+1; i=i+1){a(i,i)=a(i,i)-lamda;}
    
    double* L=(double*)malloc(n*sizeof(double));
    double* U=(double*)malloc((n-1)*sizeof(double));
    double* LM=(double*)malloc((n-1)*sizeof(double));

    L(1)=a(1,1)-lamda; U(1)=a(1,2)/L(1);
    for (int i=1; i<n-1; i=i+1){
	LM(i)=a(i+1,i);
	L(i+1)=(a(i+1,i+1)-lamda)-LM(i)*U(i);
	U(i+1)=a(i+1,i+2)/L(i+1); 
    }
    LM(n-1)=a(n,n-1); 
    L(n)=(a(n,n)-lamda)-LM(n-1)*U(n-1);

    //for (int i=1; i<n+1; i=i+1){a(i,i)=a(i,i)-lamda;}

    printf("L:\n" ); pechat_vector(n,L);
    printf("LM:\n" ); pechat_vector(n-1,LM);
    printf("U:\n" ); pechat_vector(n-1,U);

    double* matrL=(double*)malloc(n*n*sizeof(double));
    double* matrU=(double*)malloc(n*n*sizeof(double));
    double* matrLU=(double*)malloc(n*n*sizeof(double));

    for (int i=1; i<n+1; i=i+1){
	for (int j=1; j<n+1; j=j+1){
	     matrL(i,j)=0; 
	     matrU(i,j)=0;
	}
    }

    matrL(1,1)=L(1);
    for(int i=2; i<n+1;i=i+1){
	matrL(i,i)=L(i);
        matrL(i,i-1)=LM(i-1);
        

    }

    for(int i=1; i<n;i=i+1){
	
        matrU(i,i)=1;
	matrU(i,i+1)=U(i);

    }
    matrU(n,n)=1;


    printf("matrL:\n" ); pechat_matrix(n, matrL);
    printf("matrU:\n" ); pechat_matrix(n, matrU);

    matrix_mult(n, matrL, matrU, matrLU);
    printf("matrLU:\n" ); pechat_matrix(n, matrLU);
    
    free(L);
    free(LM);
    free(U);
    free(matrL);
    free(matrU);
    free(matrLU);
        




}

int indicate_peremena_znaka(double a, double b){
    if (a*b < 0) return 1;
    return 0;
}

int signum(double x){
    if (x<0) return -1;
    return 1;

}

int get_chislo_peremen_znaka(double* a, int n,  double lamda ){
    //printf("in get_chislo_peremen_znaka\n");
    
    //count_L_LM_U(a,n,lamda);

    double u=a(1,2)/(a(1,1)-lamda);
    double l=(a(1,1)-lamda); 
    
    //double newl;
    int otv=0; int d=1;

    //printf("lii: ");
    //printf("%f ",l);
    otv=otv+indicate_peremena_znaka(d,d*signum(l));
    d=signum(d*l);
    
    
    
    for (int i=2; i<n+1; i=i+1){
	l=(a(i,i)-lamda)-a(i,i-1)*u;
        otv=otv+indicate_peremena_znaka(d,d*signum(l));
	d=signum(d*l);
        //printf("l=%f \n",l);
        if (i!=n) u=a(i,i+1)/l;
        
    }
    
    //printf("\n");
    //printf("chislo_peremen_znaka=%d\n",otv);
    
    return otv;

}

double norma_matrix(double* a, int n){
    double tmp=0; 
    double tekmax=0;

    for (int j=1; j<n+1; j=j+1){
	tmp=0;
	for (int i=1; i<n+1; i=i+1){
            tmp=tmp+fabs(a(i,j));
	}
        //printf("tmp= %f\n",tmp);
	if (tmp>tekmax) tekmax=tmp;
    }
    return tekmax;

}


int  find_sobstv_znach_nomer_k(double* matrix, int n, double norma, int k,  double eps, int needed_amount,double* sobstv_chisla ){
    //printf("step %d\n",k);
    double a=-norma;
    double b=norma;
    double c;
    while(b-a >eps){
	c=0.5*(a+b);
	if (get_chislo_peremen_znaka(matrix,n,c) <k){a=c;}
	else {b=c;}
	//printf("hhhh\n");
    }
    double otv=0.5*(a+b);
    //printf("sobstv znach number %d =%f\n",k,otv);
    
    int kratnost=get_chislo_peremen_znaka(matrix,n,b) - get_chislo_peremen_znaka(matrix,n,a);
    printf("kratnost=%d\n",kratnost);
    
    //printf("needed_amount=%d\n", needed_amount);
    for(int i=0; i<kratnost; i=i+1){
	sobstv_chisla(k+i)=otv;
    }
    return needed_amount-kratnost;
    

}

void algoritm(double* a, int n, double* sobstv_chisla, double eps){
    to_3diag_vid(a,n);

    printf("3diag vid of matrA:\n" );
    pechat_matrix(n,a);

    

    //int chislo_peremen_znaka; 
    double norma;

    norma=norma_matrix(a,n);
    printf("norma=%f\n",norma);
    
    //double lamda=norma+0.5;
    //chislo_peremen_znaka=get_chislo_peremen_znaka(a,n,lamda);
    //printf("chislo_peremen_znaka(%f)=%d\n",lamda,chislo_peremen_znaka);

    int needed_amount=n;
    //for (int k=1; k<n+1; k=k+1){
    while (needed_amount >0){
	needed_amount=find_sobstv_znach_nomer_k(a, n, norma+0.5,n-needed_amount+1,  eps,needed_amount,sobstv_chisla );
	printf("needed_amount=%d\n", needed_amount);
        
    }
    //pechat_vector(n, sobstv_chisla);	


}

*/



double get_nevazka_sleda(int n,double* a,double* sobstv_chisla){
    double sum_lambd_my=0;
    for (int i=0; i<n; i=i+1){sum_lambd_my=sum_lambd_my+sobstv_chisla[i];}
    //printf("sum_lambd_my =%f\n",sum_lambd_my);
    
    double sum_lambd_ist=0;
    for (int i=0; i<n; i=i+1){sum_lambd_ist=sum_lambd_ist+a(i+1,i+1);}
    //printf("sum_lambd_ist =%f\n",sum_lambd_ist);
    
    return fabs(sum_lambd_my-sum_lambd_ist);

}

double get_nevazka_matrix(int n,double* a,double* sobstv_chisla){
    double norm_my=0;
    for (int i=0; i<n; i=i+1){norm_my=norm_my+(sobstv_chisla[i])*(sobstv_chisla[i]);}
    norm_my= sqrt(norm_my);
    //printf("norm_my =%f\n",norm_my);
    
    double norm_ist=0;
    for (int i=1; i<n+1; i=i+1){
	for (int j=1; j<n+1; j=j+1){
	    norm_ist=norm_ist+(a(i,j))*(a(i,j));
	    }
    }
    norm_ist= sqrt(norm_ist);
    //printf("norm_ist =%f\n",norm_ist);
    return fabs(norm_ist-norm_my);
    
    

}




int main(int argv,char** argc){
    printf("Hello\n");
    //printf("minim(3,2)=%d\n",minim(3,2));
    //printf("argv=%d argc[0]= %s argc[1]= %s \n",argv,argc[0],argc[1]);
    if (argv==1){printf("Invalid input; you had to enter n.\n"); return 0;}
    
    int n=atoi(argc[1]);
    printf("n=%d\n",n);

    
    
    
    double* a=(double*)malloc(n*n*sizeof(double));
    double* sobstv_chisla=(double*)malloc(n*sizeof(double));
    
    
    int smogli_prochitat=get_matrix(n,a,argv,argc);
    printf("smogli_prochitat=%d\n",smogli_prochitat);
    if (smogli_prochitat== -1){ printf("Problems with reading the matrix\n"); free(a);free(sobstv_chisla);return -1;}

    printf("matrA:\n" );
    pechat_matrix(n,a);

    double eps=0.0000001;

    double t= clock();
    algoritm(a,n,sobstv_chisla,eps);
    t=(clock()-t)/CLOCKS_PER_SEC;
    printf("time needed:= %f\n",t);
    
    printf("vector sobstv_chisel: ");
    pechat_vector(n, sobstv_chisla);
    
    get_matrix(n,a,argv,argc);
    
    double nev_sleda =get_nevazka_sleda(n,a,sobstv_chisla);
    printf("nevazka_sleda=%le\n",nev_sleda);
    
    double nev_matrix =get_nevazka_matrix(n,a,sobstv_chisla);
    printf("nevazka_matrix=%le\n",nev_matrix);
    
    
    


    


    free(a);
    free(sobstv_chisla);
       
    printf("Goodbuy\n");
   
    
    return 0;
    


}