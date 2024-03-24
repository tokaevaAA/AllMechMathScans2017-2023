#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>







class Point{
    private:
	double x;
	double y;
    public:
    Point(){}
    Point(double x_0, double y_0){x=x_0; y=y_0;}
    ~Point(){}
    double get_x(){return x;}
    double get_y(){return y;}
    void pechat(){printf("%f %f", x, y);}
    void pechat_v_file(FILE*f){fprintf(f,"%f %f ", x, y);}
    Point operator+(Point p){return Point(0.5*(x+p.get_x()), 0.5*(y+p.get_y()));}

  
};

class Triangle{
    private:
	Point A;
	Point B;
	Point C;
    public:
    Triangle(){}
    Triangle(Point A_0, Point B_0, Point C_0){A=A_0; B=B_0; C=C_0; }
    ~Triangle(){}

    Point get_A(){return A;} 
    Point get_B(){return B;} 
    Point get_C(){return C;}    

    double get_s(){
	double a=sqrt((C.get_x()-B.get_x())*(C.get_x()-B.get_x())+(C.get_y()-B.get_y())*(C.get_y()-B.get_y()));
	double b=sqrt((A.get_x()-C.get_x())*(A.get_x()-C.get_x())+(A.get_y()-C.get_y())*(A.get_y()-C.get_y()));
	double c=sqrt((A.get_x()-B.get_x())*(A.get_x()-B.get_x())+(A.get_y()-B.get_y())*(A.get_y()-B.get_y()));
        //printf("%f %f %f\n", a, b, c);
  	double p=0.5*(a+b+c);
        return sqrt(p*(p-a)*(p-b)*(p-c));
    }
    void pechat(){A.pechat(); B.pechat(); C.pechat(); printf("\n");}
    void pechat_v_file(FILE*f){
	A.pechat_v_file(f); B.pechat_v_file(f); C.pechat_v_file(f); fprintf(f,"\n");
	}

};

double func(Point A){
    double x=A.get_x();
    double y=A.get_y();
    //return 12*x*sin(2*x)*y*y;
    return 3*sqrt(x)*exp(y);
   

}

double process(Triangle T){
    double otv=func(T.get_A()+T.get_B())+func(T.get_A()+T.get_C())+func(T.get_C()+T.get_B());
    otv=otv*T.get_s();
    otv=otv/3.0;
    return otv;
}
//---------------------------------------------------------------------------------------------


int main(int argc, char** argv){
    printf("Hello!\n ");
    
    if (argc != 7) {printf("Usage: ./a.out a_x b_x a_y b_y N_x N_y  \n"); return -1;}
    
    double a_x = atof(argv[1]);
    double b_x = atof(argv[2]);
    double a_y = atof(argv[3]);
    double b_y = atof(argv[4]);
    int N_x = atoi(argv[5]);
    int N_y = atoi(argv[6]);
    printf("a_x=%f b_x=%f a_y=%f b_y=%f N_x=%d N_y=%d \n", a_x, b_x, a_y, b_y, N_x,N_y);

    
    FILE* file_of_triangles;
    file_of_triangles=fopen("file_of_triangles.txt","w");
    if (file_of_triangles==NULL){printf("Cannot open file_of_triangles.txt!\n"); return -1;}
    fprintf(file_of_triangles, "%d\n", 4*N_x*N_y);
    

    FILE* file_for_find_p;
    file_for_find_p=fopen("file_for_find_p.txt","a");
    if (file_for_find_p==NULL){printf("Cannot open file_for_find_p.txt!\n"); return -1;}
    
    double h_x=(b_x-a_x)/N_x;
    double h_y=(b_y-a_y)/N_y;
    double otv=0;
    for (double i=0; i<=b_x-h_x; i=i+h_x){
	for(double j=0; j<=b_y-h_y; j=j+h_y){
	
	Triangle T1(Point(i,j),Point(i,j+h_y),Point(i+0.5*h_x, j+0.5*h_y));
	Triangle T2(Point(i,j+h_y),Point(i+h_x,j+h_y),Point(i+0.5*h_x, j+0.5*h_y));
	Triangle T3(Point(i+h_x,j),Point(i+h_x,j+h_y),Point(i+0.5*h_x, j+0.5*h_y));
	Triangle T4(Point(i,j),Point(i+h_x,j),Point(i+0.5*h_x, j+0.5*h_y));
	T1.pechat_v_file(file_of_triangles);
	T2.pechat_v_file(file_of_triangles);
	T3.pechat_v_file(file_of_triangles);
	T4.pechat_v_file(file_of_triangles);

	otv=otv+process(T1)+process(T2)+process(T3)+process(T4);
	
	}

    }


    double otv2=0;
    for (double i=0; i<=b_x; i=i+h_x){
	for(double j=0.5*h_y; j<=b_y-0.5*h_y; j=j+0.5*h_y){
	otv2=otv2+func(Point(i,j));
	
	}
    }
    for (double i=0.5*h_x; i<=b_x-0.5*h_x; i=i+h_x){
	for(double j=0; j<=b_y; j=j+0.5*h_y){
	otv2=otv2+func(Point(i,j));
	
	}
    }
    

    //double err=abs(otv-(sin(2)-2*cos(2)));
    double err=abs(otv-2*(exp(1)-1));
    printf("otv=%f err=%le \n", otv,err);
    fprintf(file_for_find_p, "%d %d  %f %f\n", N_x, N_y, log(N_x*N_y),log(1/err) );
    
    fclose(file_of_triangles);
        
    printf("Goodbuy!\n");
    
    return 0;

}
