#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



class SobstvFunc{
  private:
	int m_n;
	int m_N;
	double m_a;
	double m_b;
	double m_h;
	double m_lambd;
	double* m_mas;
  public:
	SobstvFunc(int a_n, int a_N, double a_a, double  a_b):
                m_n(a_n),
                m_N(a_N),
                m_a(a_a),
                m_b(a_b),
                m_h((m_b-m_a)/(m_N-0.5)),
                m_lambd(4*sin(0.5*M_PI*(m_n-0.5)*m_h)*sin(0.5*M_PI*(m_n-0.5)*m_h)/(m_h*m_h)),
                m_mas(static_cast<double*>(malloc((static_cast<size_t>(m_N+1))*sizeof(double))))
                {
			    //printf("Allocated %p for n=%d\n",m_mas,m_n);
			    m_mas[0]=0.0;
			    //printf("n=%d N=%d  h=%f a=%f\n",m_n,m_N,m_h,m_a);
			    for (int k=1; k<=m_N-1; k=k+1){m_mas[k]=sin(M_PI*(m_n-0.5)*(m_a+k*m_h));}
			    m_mas[m_N]=m_mas[m_N-1];
			    }
	~SobstvFunc(){/*printf("Start deleting%p for n=%d\n",m_mas,m_n);*/
                  free(m_mas); 
                  /*printf("End deleting\n");*/
                }

	SobstvFunc(const SobstvFunc& sf):m_n(sf.m_n),
                                     m_N(sf.m_N),
                                     m_a(sf.m_a),
                                     m_b(sf.m_b),
                                     m_h(sf.m_h),
                                     m_lambd(sf.m_lambd),
                                     m_mas(static_cast<double* >(malloc((static_cast<size_t>(m_N+1))*sizeof(double))))
                                    {
                                     for (int k=0; k<=m_N; k=k+1){m_mas[k]=sf.m_mas[k];}
                                    }
	SobstvFunc& operator=(const SobstvFunc& sf){ m_n=sf.m_n;
                                                 m_N=sf.m_N;
                                                 m_a=sf.m_a;
                                                 m_b=sf.m_b;
                                                 m_h=sf.m_h;
                                                 m_lambd=sf.m_lambd;
                                                 m_mas=static_cast<double* >(malloc((static_cast<size_t>(m_N+1))*sizeof(double)));
                                                 for (int k=0; k<=m_N; k=k+1){m_mas[k]=sf.m_mas[k];}
                                                 return *this;
                                                }

	void pechat(){
		     for (int k=0; k<=std::min<int>(m_N,10); k=k+1){printf("%f ",m_mas[k]);}
    		     printf("\n");
		     }
	double scal_proizv(SobstvFunc& sf){double otv=0.0;
					  for (int k=1; k<=m_N-1; k=k+1){ 
						otv=otv+sin(M_PI*(m_n-0.5)*(m_a+k*m_h))*sin(M_PI*(sf.m_n-0.5)*(sf.m_a+k*sf.m_h));
						}
					  return m_h*otv;

					  }
	double* Ay(double* dop_mas){dop_mas[0]=0;
				   dop_mas[1]=2*m_mas[1]/(m_h*m_h)-m_mas[2]/(m_h*m_h)-m_lambd*m_mas[1];
			           for(int k=2; k<=m_N-2; k=k+1){dop_mas[k]=-m_mas[k-1]/(m_h*m_h)+2*m_mas[k]/(m_h*m_h)-m_mas[k+1]/(m_h*m_h)-m_lambd*m_mas[k];}
				   dop_mas[m_N-1]=-m_mas[m_N-2]/(m_h*m_h)+m_mas[m_N-1]/(m_h*m_h)-m_lambd*m_mas[m_N-1];
				   dop_mas[m_N]=dop_mas[m_N-1];
				   return dop_mas;
				   }
				




};


double get_norma(int N, double* mas){
    double otv=0.0;
    for (int k=0; k<=N; k=k+1){otv=otv+mas[k]*mas[k];}
    otv=sqrt(otv);
    return otv;
}

int main(int argc, char** argv){
    printf("Hello!\n ");
    
    if (argc != 4) {printf("Usage: ./a.out a b N_points\n"); return -1;}
    
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int N = atoi(argv[3]);
    //double h=(b-a)/(N-0.5);
   
    printf("a=%f b=%f N=%d\n", a,b,N);

    double max_err=0.0;
    int i0=1;
    int j0=1;
    for (int i=1; i<=N-1; i=i+1){
	for (int j=i+1; j<=N-1; j=j+1){ 
				      SobstvFunc sf1=SobstvFunc(i,N,a,b);
				      SobstvFunc sf2=SobstvFunc(j,N,a,b);
				      double tek_err=sf1.scal_proizv(sf2);
				      if (std::abs(tek_err)>max_err){max_err=tek_err; i0=i; j0=j;}
				     }
    }
    printf("Worst ortogonal:%e;  i0=%d, j0=%d\n",max_err,i0,j0);

    double* dop_mas=static_cast<double*>(malloc((static_cast<size_t>(N+1))*sizeof(double)));
    double tek_norma=0.0;
    double max_norma=0.0;
    int n0=1;

    for (int n=1; n<=N-1; n=n+1){SobstvFunc sf=SobstvFunc(n,N,a,b);
				dop_mas=sf.Ay(dop_mas);
				tek_norma=get_norma(N,dop_mas);
				//printf("n=%d norma=%e\n",n,tek_norma);
				if (std::abs(tek_norma)>max_norma){max_norma=tek_norma; n0=n;}
				}

    printf("Worst nevyazka:%e;  n0=%d\n",max_norma,n0);
    printf("Goodbuy!\n");
    free(dop_mas);
    
    return 0;

}
