#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Algoritm.h"

#define a(i,j) a[(i-1)*n+(j-1)]
#define anew(i,j) anew[(i-1)*n+(j-1)]
#define e(i,j) e[(i-1)*n+(j-1)]
#define x(i) x[i-1]



void one_step(int n, int k, double* a, double* x , double* e){
    printf("STEP =%d\n",k);

    double s=0; int j=0; int l=0; double skal_product;
    for ( j=k+1; j<n+1; j=j+1){s=s+(a(j,k))*(a(j,k));}
    //printf("s=%f\n",s);

    double norma_ak= sqrt( (a(k,k))*(a(k,k))+s );
    //printf("norma_ak=%f\n",norma_ak);

    x(k)=a(k,k)-norma_ak;
    for(j=k+1; j<n+1; j=j+1){x(j)=a(j,k);}
    double norma_x=sqrt( (x(k))*(x(k)) +s );
    //printf("norma_x=%f\n",norma_x);
    
    if (k!=n || ( k==n && norma_ak > a(k,k))){
	for(j=1; j<k; j=j+1){x(j)=0;}

	for(j=k; j<n+1; j=j+1){x(j)=x(j)/norma_x;}
        //pechat_vector(n,x);
	
	for(j=1;j<n+1;j=j+1){
	    skal_product=0;
	    for(l=1;l<n+1;l=l+1){
		    skal_product = skal_product+x(l)*a(l,j);
		
	    }
            for(l=1;l<n+1;l=l+1){
		    a(l,j)=a(l,j)-2*skal_product*x(l);
		
	    }
	    	    
	}

	for(j=1;j<n+1;j=j+1){
	    skal_product=0;
	    for(l=1;l<n+1;l=l+1){
		    skal_product = skal_product+x(l)*e(l,j);
		
	    }
            for(l=1;l<n+1;l=l+1){
		    e(l,j)=e(l,j)-2*skal_product*x(l);
		
	    }
	    	    
	}
    
    }
    
        
    
    
    //pechat_matrix_rasshir(n,a,e);
    
   


}


void obratny_hod(int n, int k, double* a, double* e){
    printf("obratny_hod, k=%d\n",k);
    int i; int j; int l=0; double akk=a(k,k);
    for (i=k;i<n+1;i=i+1){a(k,i)=a(k,i)/akk;}
    for (i=1;i<n+1;i=i+1){e(k,i)=e(k,i)/akk;}
    
    //pechat_matrix_rasshir(n,a,e);

    
    for(j=k-1; j>0; j=j-1){ 
	for (l=1; l<n+1; l=l+1){
		e(j,l)= e(j,l)-a(j,k)*e(k,l);
				}
    }

    for(j=k-1; j>0; j=j-1){a(j,k)=0;}
			  
    //pechat_matrix_rasshir(n,a,e);
    


}


void algoritm(int n, double* a, double* x, double* e){
    for (int k=1; k<n+1; k=k+1){one_step(n,k,a,x,e);}
    for (int k=n; k>0; k=k-1){obratny_hod(n,k,a,e);}

}
