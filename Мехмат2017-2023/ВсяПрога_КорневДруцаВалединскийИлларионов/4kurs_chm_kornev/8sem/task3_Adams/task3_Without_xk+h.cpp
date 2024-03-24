#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>


class My_vector3D{
private:
    double m_u;
    double m_v;
    double m_w;
public:
    My_vector3D():m_u(0),m_v(0),m_w(0){}
    My_vector3D(double a_u, double a_v, double a_w):m_u(a_u),m_v(a_v),m_w(a_w){}
    ~My_vector3D(){}
    
    double get_u()const {return m_u;}
    double get_v()const {return m_v;}
    double get_w()const {return m_w;}
    
    double get_norma(){double otv=fmax(abs(m_u),abs(m_v)); return fmax(otv,abs(m_w));}
    
   
    My_vector3D& operator+(const My_vector3D& dopVect) {
        m_u += dopVect.get_u();
        m_v += dopVect.get_v();
        m_w += dopVect.get_w();
        return *this;
    }
    My_vector3D& operator-(const My_vector3D& dopVect) {
        m_u -= dopVect.get_u();
        m_v -= dopVect.get_v();
        m_w -= dopVect.get_w();
        return *this;
    }
    
    My_vector3D& operator*(double h) {
        m_u *= h;
        m_v *= h;
        m_w *= h;
        return *this;
    }
    
    My_vector3D& operator/(double h) {
        m_u /= h;
        m_v /= h;
        m_w /= h;
        return *this;
    }
    
    void pechat(){printf("%f %f %f\n", m_u,m_v,m_w);}
};


My_vector3D tochnoe_reshenie(double x_tek) {
    return My_vector3D(exp(2*x_tek), 2*exp(x_tek)-2*exp(2*x_tek), -2*exp(x_tek)+2*exp(2*x_tek));
}


My_vector3D f(double x_k, My_vector3D y_k){
    
    return My_vector3D(2*y_k.get_u()+y_k.get_v()+y_k.get_w(),
                       -2*y_k.get_u()-y_k.get_w(),
                       2*y_k.get_u()+y_k.get_v()+2*y_k.get_w()) ;
}



double get_err_at_point(double x_tek, My_vector3D y_tek){
    return My_vector3D(tochnoe_reshenie(x_tek)-y_tek).get_norma();
    
}


My_vector3D get_y_kp1_Adams_notAvtom(double x_k, double x_km1, double x_km2, double x_km3, My_vector3D y_k, My_vector3D y_km1, My_vector3D y_km2, My_vector3D y_km3, double h){
    
    My_vector3D otv=f(x_k,y_k)*(55.0/24)-f(x_km1,y_km1)*(59.0/24)+f(x_km2,y_km2)*(37.0/24)-f(x_km3,y_km3)*(9.0/24);
    otv=y_k+otv*h;
    return otv;
}







double process_segment(double a, double b, int n_steps, double eps=-1){
    double h=(b-a)/n_steps;
    double x_km3=a;
    double x_km2=a+h;
    double x_km1=a+2*h;
    double x_k=a+3*h;
    
    
    My_vector3D y_km3=tochnoe_reshenie(x_km3);
    My_vector3D y_km2=tochnoe_reshenie(x_km2);
    My_vector3D y_km1=tochnoe_reshenie(x_km1);
    My_vector3D y_k=tochnoe_reshenie(x_k);
    My_vector3D y_kp1_h;
    
    
    
    double max_err=0.0;
    double tek_err=0.0;
    double M;
    
    int cnt_steps = 3;
    while (x_k<=b){
        x_k = a + cnt_steps * h;
        x_km1 = a + (cnt_steps - 1) * h;
        x_km2 = a + (cnt_steps - 2) * h;
        x_km3 = a + (cnt_steps - 3) * h;
        y_kp1_h=get_y_kp1_Adams_notAvtom(x_k,x_km1,x_km2,x_km3,y_k,y_km1,y_km2, y_km3, h);
                    
        
        
        tek_err=get_err_at_point(a+(cnt_steps+1)*h,y_kp1_h);
        
        if (x_k+h<=b){max_err=fmax(tek_err,max_err);}
        
        //x_km3=x_km2;
        //x_km2=x_km1;
        //x_km1=x_k;
        //x_k=x_k+h;
        y_km3=y_km2;
        y_km2=y_km1;
        y_km1=y_k;
        y_k=y_kp1_h;
        ++cnt_steps;
    }
    
    return max_err;
    
    
    
}





   
//===================================================================================================================

int main(int argc, char** argv){
    printf("Hello!\n");
    
    if (argc != 4) {printf("Usage: ./a.out a b eps\n"); return -1;}
    
    double a=atof(argv[1]);
    double b=atof(argv[2]);
    double eps=atof(argv[3]);
    printf("a=%f b=%f\n",a,b);
   
    
    FILE* fout;
    fout=fopen("fout.txt","w");
    if (fout==NULL) {printf("Cannot open fout.txt"); return -1;}
    
    auto prev = process_segment(a, b, 100);
    
    for (int n_steps=100; n_steps<=10000; n_steps=n_steps*2){
        auto err = process_segment(a, b, n_steps);
        printf("n_steps=%d p=%le\n", n_steps,log2(prev / err));
        prev = err;
    }
    
    
    /*
    printf("Now avtom step:\n");
    for (double n_steps=10; n_steps<=10; n_steps=n_steps*10){
        printf("max_err=%le\n",process_segment(a, b, n_steps,eps));

    }
    
    */
    
    


    

    fclose(fout);
    printf("Goodbuy!\n");
        
    return 0;

}
