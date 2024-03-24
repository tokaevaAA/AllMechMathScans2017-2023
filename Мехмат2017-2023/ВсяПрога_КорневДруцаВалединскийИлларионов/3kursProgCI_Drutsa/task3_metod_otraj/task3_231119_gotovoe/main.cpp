#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctime>
#include <math.h>
#include "matrices.h"
#include "Algoritm.h"
#include "ARGS.h"
#include "get_time.h"
#include "synchronize.h"

#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>

#define matrix(i,j) matrix[(i-1)*n +j-1]
#define obr_matrix(i,j) obr_matrix[(i-1)*n +j-1]
#define stolb(i) stolb[(i-1)]

#define a(i,j) a[(i-1)*n+(j-1)]
#define anew(i,j) anew[(i-1)*n+(j-1)]
#define e(i,j) e[(i-1)*n+(j-1)]


static long int threads_total_time = 0;
static pthread_mutex_t threads_total_time_mutex = PTHREAD_MUTEX_INITIALIZER;


void* func_for_thread (void* pa)
{
  
  ARGS* pargs = (ARGS*)pa;
  double  t;
  double t_full_astr_in_thread=0;
  

  printf ("Thread %d started;\n", pargs->thread_num);
  t = get_cpu_time ();
  
  synchronize(pargs->total_threads);
  t_full_astr_in_thread = get_full_time ();
  
  

  metod_otraj_not_threaded(pargs);

 

  synchronize(pargs->total_threads);
  t_full_astr_in_thread = get_full_time ()-t_full_astr_in_thread ;
  if (pargs->thread_num ==1) {*pargs->t_full_astr=t_full_astr_in_thread;}

  
  t = get_cpu_time () - t;
  pthread_mutex_lock (&threads_total_time_mutex);
  threads_total_time += t;
  pthread_mutex_unlock (&threads_total_time_mutex);


  printf ("Thread %d finished, time(get_cpu_time) needed = %f\n",pargs->thread_num, t);

  return 0;
}


double* matrix_mult(int n,  double* a, double* e , double* anew){
    double tek_sum;
    int i; int j; int l;



    for (i=1; i<n+1; i=i+1){
        for ( j=1; j<n+1; j=j+1){
            tek_sum=0;
            for(l=1; l<n+1;l=l+1){tek_sum=tek_sum+a(i, l)*e(l,j); }
            anew(i,j)=tek_sum;
        }
    }

    printf("a*e=\n");
    print_matrix(anew,n);
    return anew;

}

double count_norma(int n, double* a){
    double tek_sum=0;
    double tekmax=0;

    for (int i=1; i<n+1; i=i+1){
        tek_sum=0;
        for (int j=1; j<n+1; j=j+1){
            tek_sum=tek_sum+fabs(a(i,j));
        }
        if (tek_sum>tekmax) tekmax=tek_sum;
    }
    return tekmax;


}


double count_nevazka(int n, double* a, double* e){

    double* anew=(double*)malloc(n*n*sizeof(double));

    anew=matrix_mult(n,a,e,anew);

    for (int i=1; i<n+1; i=i+1){anew(i,i)=anew(i,i)-1;}
    
    double norma=count_norma(n,anew);

    free(anew);
    return norma;



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
  int has_obr_matrix=1; 
  double  t_full_astron;
  double   t_full_cpu_clock;
  double t_full_astr;

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
                             udalenie(threads, args, matrix, obr_matrix, stolb);
 			     return -1;
			    }

  
  init_vector (stolb, n);
  
  double norma=count_norma(n, matrix);  

  printf ("Matrix(norma=%le):\n",norma);
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


 
 
  for (i = 0; i < nthreads; i++){
      args[i].matrix = matrix;
      args[i].obr_matrix =obr_matrix;
      args[i].n = n;
      args[i].thread_num = i+1;
      args[i].total_threads = nthreads;
      args[i].stolb=stolb;
      args[i].has_obr_matrix=&has_obr_matrix;
      args[i].t_full_astr=&t_full_astr;
      args[i].norma=norma;
      
    }

  
  
  t_full_cpu_clock=clock();
  t_full_astron = get_full_time ();
  
  for (i = 0; i < nthreads; i++){
      if (pthread_create (&threads[i], 0,func_for_thread,&args[i])){
          fprintf (stderr, "cannot create thread #%d!\n",i);
          for (int j=0; j<i; j=j+1){pthread_kill (threads[j], 0);}
          udalenie(threads, args, matrix, obr_matrix, stolb);
          return 10;
        }
    }

  for (i = 0; i < nthreads; i++){
      if (pthread_join (threads[i], 0)) fprintf (stderr, "cannot wait thread #%d!\n", i);
    }

      
    
  t_full_cpu_clock=(clock()-t_full_cpu_clock)/CLOCKS_PER_SEC;
  t_full_astron = get_full_time () - t_full_astron;
   
  printf("time_clock=%f\n",t_full_cpu_clock);
  printf("time_astron=%f\n",t_full_astron);
  printf("time_astr_counted_in_func_for_thread=%f\n",t_full_astr);
  
  
  printf("has_obr_matrix=%d\n",has_obr_matrix);
  
  if (t_full_astron<0.000000000000001) t_full_astron=1;
  
  if (has_obr_matrix != 1){printf("NET OBRATNOY!!!!\n");}
  
  if (has_obr_matrix==1){
      printf ("Obr_Matrix:\n");
      print_matrix(obr_matrix,n);
      get_matrix(matrix,n,argc,argv);
      double nevazka=count_nevazka(n,matrix,obr_matrix);
      printf("nevazka= %le\n",nevazka);

  }

 
  free (threads);
  free (args);
  free (matrix);
  free (obr_matrix);
  free(stolb);

  
  printf ("Total full astron time = %f, total threads time = %ld (%f%%), per thread = %ld\n",    t_full_astron, threads_total_time,(threads_total_time * 100) / t_full_astron,threads_total_time / nthreads);

  //1 3000 381.338995
  //2 3000 203.285796
  //4 3000 114.980344
  

  return 0;
}

