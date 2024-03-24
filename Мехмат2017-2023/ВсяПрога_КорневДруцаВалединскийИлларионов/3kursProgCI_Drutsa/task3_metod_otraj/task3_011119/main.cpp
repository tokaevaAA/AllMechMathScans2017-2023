#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctime>
#include <math.h>
#include "matrices.h"
//#include "get_time.h"
#include "synchronize.h"

#define matrix(i,j) matrix[(i-1)*n +j-1]
#define obr_matrix(i,j) obr_matrix[(i-1)*n +j-1]
#define stolb(i) stolb[(i-1)]

#define a(i,j) a[(i-1)*n+(j-1)]
#define anew(i,j) anew[(i-1)*n+(j-1)]
#define e(i,j) e[(i-1)*n+(j-1)]


typedef struct _ARGS
{
  double* matrix;      
  double* obr_matrix;
  double* stolb;      
  int n;                
  int thread_num;       
  int total_threads; 
  int* has_obr_matrix;   
} ARGS;


//static long int threads_total_time = 0;
//static pthread_mutex_t threads_total_time_mutex = PTHREAD_MUTEX_INITIALIZER;


int one_step(ARGS* pargs, int k){
    
    double* matrix = pargs->matrix;
    double* obr_matrix = pargs->obr_matrix;
    
    double* stolb=pargs->stolb;
    int thread_num =pargs-> thread_num;
    int total_threads =pargs-> total_threads;
    int n=pargs->n;
   

    
    
    
    //synchronize(total_threads);
    //if(thread_num==total_threads)printf("Stolb in step= %d thread %d :", step, thread_num);
    //synchronize(total_threads);
    //if(thread_num==total_threads) print_vector(stolb,n);

    synchronize(total_threads);
      
    int step=k;
    
    int amount_kuskov = int(step-1)/(int (total_threads));
    int start_stolb=thread_num + amount_kuskov*total_threads;
    int pos_in_kusok=step%total_threads;
    if (step%total_threads==0) pos_in_kusok=total_threads;
    if(pos_in_kusok > thread_num) start_stolb=start_stolb + total_threads;
    //printf("thread_num=%d step=%d  amount_kuskov=%d start_stolb=%d\n", thread_num,step,amount_kuskov,start_stolb);
    
    
        
	double skal_product;
	for(int j=start_stolb; j<=n; j=j+total_threads){
	    skal_product=0;
	    for(int l=k;l<=n;l=l+1){
		    skal_product = skal_product+stolb(l)*matrix(l,j);
		    
		
	    }
            for(int l=k; l<=n; l=l+1){
		    matrix(l,j)=matrix(l,j)-2*skal_product*stolb(l);
		
	    }
	    	    
	}

	for(int j=thread_num;j<=n;j=j+total_threads){
	    skal_product=0;
	    for(int l=k;l<n+1;l=l+1){
		    skal_product = skal_product+stolb(l)*obr_matrix(l,j);
		
	    }
            for(int l=k; l<=n;l=l+1){
		    obr_matrix(l,j)=obr_matrix(l,j)-2*skal_product*stolb(l);
		
	    }
	    	    
	}

    
    
    synchronize(total_threads);
    
  

    return 0;
}

int metod_otraj_not_threaded(ARGS* pargs){
    int n=pargs->n;
    double* matrix = pargs->matrix;
    double* stolb=pargs->stolb;
    int otv;
    //int total_threads=pargs->total_threads;
    
    

    for (int k=1; k<=n-1; k=k+1){
        //synchronize(pargs->total_threads);
	

	double s=0;  
	double skal_product;
        for ( int j=k+1; j<n+1; j=j+1){s=s+(matrix(j,k))*(matrix(j,k));} //printf("s=%f\n",s);

        double norma_ak= sqrt( (matrix(k,k))*(matrix(k,k))+s ); //printf("norma_ak=%f\n",norma_ak);

	for(int j=1; j<k; j=j+1){stolb(j)=0;}
        stolb(k)=matrix(k,k)-norma_ak;
        
    
        double norma_x=sqrt( (stolb(k))*(stolb(k)) +s ); //printf("norma_x=%f\n",norma_x);
    
    	if (norma_x<0.00000000000001){printf("Net obratnoy : norma=0; k=%d.\n",k); return -1;}

	stolb(k)=stolb(k)/norma_x;
	for(int j=k+1; j<n+1; j=j+1){stolb(j)=(matrix(j,k))/norma_x;}

	otv=one_step(pargs,k);
        synchronize(pargs->total_threads);
	if(otv==-1) return -1;
    }
    return 0;
}

void obratny_hod(int n, int k, double* a, double* e);

void* func_for_thread (void* pa)
{
  
  ARGS* pargs = (ARGS*)pa;
  double t=clock();
  

  printf ("Thread %d started\n", pargs->thread_num);


  int otv=metod_otraj_not_threaded(pargs);

  if (otv==-1){printf("Net obratnoy!\n");pargs->has_obr_matrix=0;}
  
  synchronize(pargs->total_threads);

  if(otv!=-1){if(pargs->thread_num==pargs->total_threads)
  	      for (int k=pargs->n; k>0; k=k-1){obratny_hod(pargs->n,k,pargs->matrix,pargs->obr_matrix);}
  	      }

  printf ("Thread %d finished, time needed = %f\n",pargs->thread_num, t/CLOCKS_PER_SEC);

  return 0;
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


void nevazka_matrix_mult(int n,  double* a, double* e , double* anew){
    double tmp;
    int i; int j; int l;



    for (i=1; i<n+1; i=i+1){
        for ( j=1; j<n+1; j=j+1){
            //printf("i=%d j=%d \n",i,j);
            tmp=0;
            for(l=1; l<n+1;l=l+1){tmp=tmp+a(i, l)*e(l,j); }
            anew(i,j)=tmp;
        }
    }

    for (i=1; i<n+1; i=i+1){
        for (j=1; j<n+1; j=j+1){
            e(i,j)=anew(i,j);
        }
    }
    //printf("a*e=\n");
    //print_matrix(anew,n);

}



double nevazka(int n, double* a, double* e){

    double* anew=(double*)malloc(n*n*sizeof(double));

    nevazka_matrix_mult(n,a,e,anew);

    for (int i=1; i<n+1; i=i+1){e(i,i)=e(i,i)-1;}


    double tmp=0;
    double tekmax=0;

    for (int i=1; i<n+1; i=i+1){
        tmp=0;
        for (int j=1; j<n+1; j=j+1){
            tmp=tmp+fabs(e(i,j));
        }
        if (tmp>tekmax) tekmax=tmp;
    }
    free(anew);
    return tekmax;



}

void udalenie(pthread_t* threads, ARGS* args, double* matrix, double* obr_matrix, double* stolb){
	if(threads) free (threads);
	if(args) free (args);
	if(matrix) free (matrix);
	if(obr_matrix) free (obr_matrix);
	if(stolb) free(stolb);


}



int main (int argc, char * argv[])
{
  pthread_t* threads=0;
  ARGS* args=0;
  int nthreads;
  double t_full;

  int n;                
  double* matrix=0;       
  double* obr_matrix=0;
  double* stolb=0;       
  int i;

  if (!(argc == 3 || argc==4) || !(nthreads = atoi (argv[1])) || !(n = atoi (argv[2]))){
      printf ("Usage: %s nthreads n\n", argv[0]);
      udalenie(threads, args, matrix, obr_matrix, stolb);
      return 1;
    }

  if (!(threads = (pthread_t*)malloc (nthreads * sizeof (pthread_t)))){
      fprintf (stderr, "Not enough memory!\n");
      udalenie(threads, args, matrix, obr_matrix, stolb);
      return 1;
    }
  if (!(args = (ARGS*) malloc (nthreads * sizeof (ARGS)))){
      fprintf (stderr, "Not enough memory!\n");
      udalenie(threads, args, matrix, obr_matrix, stolb);
      return 2;
    }

  if (!(matrix = (double*)malloc (n * n * sizeof (double)))){
      fprintf (stderr, "Not enough memory!\n");
      udalenie(threads, args, matrix, obr_matrix, stolb);
      return 3;
    }
    
  if (!(obr_matrix = (double*) malloc (n*n * sizeof (double)))){
      fprintf (stderr, "Not enough memory!\n");
      udalenie(threads, args, matrix, obr_matrix, stolb);
      return 4;
    }


 if (!(stolb = (double*) malloc (n * sizeof (double)))){
      fprintf (stderr, "Not enough memory!\n");
      udalenie(threads, args, matrix, obr_matrix, stolb);
      return 5;
    }
 


  
  int smogli_prochitat=get_matrix (matrix, n, argc, argv);
  if (smogli_prochitat ==-1){printf("Cannot read matrix; program terminates.\n"); 
                            free (threads);free (args);free (matrix);free (obr_matrix);free(stolb);
 			    return -1;}

  init_vector (stolb, n);
  
    
  printf ("Matrix:\n");
  print_matrix (matrix, n);
  printf ("Stolb:\n");
  print_vector (stolb, n);
  
  
  for(int i=1; i<=n; i=i+1){
    for(int j=1; j<=n; j=j+1){
	if(i==j)obr_matrix(i,j)=1;
	else obr_matrix(i,j)=0;
    }
  }
  printf ("Obr_Matrix:\n");
  print_matrix(obr_matrix,n);

  int has_obr_matrix=1;
 
 
  for (i = 0; i < nthreads; i++){
      args[i].matrix = matrix;
      args[i].obr_matrix =obr_matrix;
      args[i].n = n;
      args[i].thread_num = i+1;
      args[i].total_threads = nthreads;
      args[i].stolb=stolb;
      args[i].has_obr_matrix=&has_obr_matrix;
    }

  
  
  t_full=clock();
  
  for (i = 0; i < nthreads; i++){
      if (pthread_create (&threads[i], 0,func_for_thread,&args[i])){
          fprintf (stderr, "cannot create thread #%d!\n",i);
          return 10;
        }
    }

  for (i = 0; i < nthreads; i++){
      if (pthread_join (threads[i], 0)) fprintf (stderr, "cannot wait thread #%d!\n", i);
    }


  //if (has_obr_matrix==1){for (int k=n; k>0; k=k-1){obratny_hod(n,k,matrix,obr_matrix);}}
    
  t_full=(clock()-t_full)/CLOCKS_PER_SEC;
  printf("time=%f\n",t_full);
  
  
  if (has_obr_matrix==1){
      printf ("Obr_Matrix:\n");
      print_matrix(obr_matrix,n);
  
  

  get_matrix(matrix,n,argc,argv);
  double nev=nevazka(n,matrix,obr_matrix);
  printf("nevazka= %le\n",nev);
  }

 
  free (threads);
  free (args);
  free (matrix);
  free (obr_matrix);
  free(stolb);


  

  return 0;
}

