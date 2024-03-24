#include <stdio.h>
#include <math.h>
#include "matrices.h"
#include "synchronize.h"

#define N_MAX   8

#define a(i,j) a[(i-1)*n+(j-1)]



int minim(int a, int b){
    return (a<b)?a:b;

}

double func (int i, int j){
	double otv;
	otv= 1.0/(1+i+j);
	//otv=fabs(i-j);
	//printf("i+j=%d\n",i+j);
	//otv=0;
	//if (i==999) otv=0;;
	return otv;

}



void print_matrix_rasshir(int n, double* a, double* e){
    if (n>15) return;

    for (int i=0; i<minim(n,7); i=i+1){
	for (int j=0; j<minim(n,7); j=j+1){
	    printf("%f ",a[i*n+j]);
	}
	printf(" | ");
        for (int j=0; j<minim(n,7); j=j+1){
	    printf("%f ",e[i*n+j]);
        }
	printf("\n");
    }
    
}





int get_matrix (double * a, int n, int argc, char** argv){
  int i, j;
  int otv=0;
  int k;

  if(argc==3){
	     for (i = 1; i <= n; i++)
    		for (j = 1; j <= n; j++)
		     a(i,j)=func(i,j);
  	      }

  if (argc==4){
    	FILE*f;
    	f=fopen(argv[3],"r"); if (f==0){printf("Cannot open %s\n",argv[3]);}

	//otv= get_matrix_from_file(n,a,f);

	for (int i=1; i<n+1; i=i+1){
		for (int j=1; j<n+1; j=j+1){
	    		k=fscanf(f,"%lf ",&a(i,j)); 
			if(k!=1){return -1;}
		}
   
        }

        fclose(f);
	}


  return otv;
}




void init_vector (double * vector, int n)
{
  int i;
  double *b = vector;

  for (i = 0; i < n; i++)
    b[i] = 1.;
}



/* Вывод матрицы */
void print_matrix (double * matrix, int n)
{
  int i, j;
  int m = (n > N_MAX ? N_MAX : n);

  for (i = 0; i < m; i++)
    {
      for (j = 0; j < m; j++)
        printf (" %12.6f", matrix[i * n + j]);
      printf ("\n");
    }
}

/* Вывод вектора */
void print_vector (double * vector, int n)
{
  int i;
  int m = (n > N_MAX ? N_MAX : n);

  for (i = 0; i < m; i++)
      printf (" %12.6f", vector[i]);
  printf ("\n");
}


/* Умножить матрицу a на вектор b, c = ab для задачи с
   номером thread_num из общего количества
   total_threads. */
   

void matrix_mult_vector (double *a, double *b, double *c,
                         int n, int thread_num,
                         int total_threads)
{
  int i, j;
  double *p, s;
  int first_row, last_row;

  
  first_row = n * thread_num;
  first_row /= total_threads;
  
  last_row = n * (thread_num + 1);
  last_row = last_row / total_threads - 1;

  for (i = first_row, p = a + i * n; i <= last_row; i++)
    {
      for (s = 0., j = 0; j < n; j++)
        s += *(p++) * b[j];
      c[i] = s;
    }
  synchronize (total_threads);
}


