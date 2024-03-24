#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <tuple>


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
    
    My_vector3D operator+(const My_vector3D& dopVect){return My_vector3D(m_u+dopVect.get_u(), m_v+dopVect.get_v(), m_w+dopVect.get_w());}
    
    My_vector3D operator-(const My_vector3D& dopVect){return My_vector3D(m_u-dopVect.get_u(), m_v-dopVect.get_v(), m_w-dopVect.get_w());}
    
    My_vector3D operator*(double h){return My_vector3D(m_u*h, m_v*h, m_w*h);}
    My_vector3D operator/(double h){return My_vector3D(m_u/h, m_v/h, m_w/h);}
    
    void pechat(){printf("%f %f %f\n", m_u,m_v,m_w);}
};


double get_err_at_point(double x_tek, My_vector3D y_tek){
    double a=exp(2*x_tek)-y_tek.get_u();
    double b=2*exp(x_tek)-2*exp(2*x_tek)-y_tek.get_v();
    double c=-2*exp(x_tek)+2*exp(2*x_tek)-y_tek.get_w();
    double otv=fmax(fmax(abs(a),abs(b)),abs(c));
    //printf("tek_err=%f\n",otv);
    return otv;
    
}


My_vector3D f(double x_k, My_vector3D y_k){
    
    return My_vector3D(2*y_k.get_u()+y_k.get_v()+y_k.get_w(),
                       -2*y_k.get_u()-y_k.get_w(),
                       2*y_k.get_u()+y_k.get_v()+2*y_k.get_w()) ;
}



My_vector3D get_y123_Euler(double x_k, My_vector3D y_k, double h){
    
    return y_k+f(x_k, y_k)*h;
}

My_vector3D get_y_kp1_Adams_notAvtom(double x_k, double x_km1, double x_km2, double x_km3, My_vector3D y_k, My_vector3D y_km1, My_vector3D y_km2, My_vector3D y_km3, double h){
    
    My_vector3D otv=f(x_k,y_k)*55-f(x_km1,y_km1)*59+f(x_km2,y_km2)*37-f(x_km3,y_km3)*9;
    otv=y_k+otv*h/24;
    return otv;
}



std::tuple <My_vector3D,double> get_y_kp1_Adams_Avtom(double x_k, double x_km1, double x_km2, double x_km3, My_vector3D y_k, My_vector3D y_km1, My_vector3D y_km2, My_vector3D y_km3, double h, double eps){
    
    //printf("Open:h=%f\n",h);
    
    double p=4;
    My_vector3D y_kp1_h;
    My_vector3D y_kp1_mid;
    My_vector3D y_kp1_hd2;
    double M;
    double Mhp;
    while (1){
        y_kp1_h=get_y_kp1_Adams_notAvtom(x_k,x_km1,x_km2,x_km3,y_k,y_km1,y_km2, y_km3, h);
        y_kp1_mid=get_y_kp1_Adams_notAvtom(x_k,x_km1,x_km2,x_km3,y_k,y_km1,y_km2, y_km3, h*0.5);
        y_kp1_hd2=get_y_kp1_Adams_notAvtom(x_k+0.5*h,x_k,x_km1,x_km2,y_kp1_mid,y_k,y_km1, y_km2, h*0.5);
        printf("tek_err_h=%le\n", get_err_at_point(x_k+h, y_kp1_h));
        printf("tek_err_hd2=%le\n", get_err_at_point(x_k+h, y_kp1_hd2));
        
        M = (y_kp1_hd2-y_kp1_h).get_norma()/(pow(h,p)-pow(0.5*h,p));
        //printf("M=%le d1=%f %f\n",M, M*pow(h,p),eps);
        printf("M=%le\n",M);
        Mhp=(y_kp1_hd2-y_kp1_h).get_norma()/(1-pow(0.5,p));
        printf("Mhp=%le %f\n", Mhp,eps);
        if (Mhp < eps) {break;}
        else {h=h*0.5;}
            }
    
    
    while (1){
        y_kp1_h=get_y_kp1_Adams_notAvtom(x_k,x_km1,x_km2,x_km3,y_k,y_km1,y_km2, y_km3, h);
        y_kp1_mid=get_y_kp1_Adams_notAvtom(x_k,x_km1,x_km2,x_km3,y_k,y_km1,y_km2, y_km3, h*0.5);
        y_kp1_hd2=get_y_kp1_Adams_notAvtom(x_k+0.5*h,x_k,x_km1,x_km2,y_kp1_mid,y_k,y_km1, y_km2, h*0.5);
        
        //M = (y_kp1_hd2-y_kp1_h).get_norma()/(pow(h,p)-pow(0.5*h,p));
        //printf("d2=%f %f\n",M*pow(h,p),eps);
        Mhp=(y_kp1_hd2-y_kp1_h).get_norma()/(1-pow(0.5,p));
        if (Mhp > eps/2.0) {break;}
        else {h=h*2;}
            }
     
    //printf("Close:h=%f\n",h);
    return std::make_tuple(y_kp1_h, h);
}



double get_err_at_all_segment(double a, double b, int n_steps, double eps=-1){
    
    double h=(b-a)/n_steps;
    double x_km3=a;
    double x_km2=a+h;
    double x_km1=a+2*h;
    double x_k=a+3*h;
    
    My_vector3D y_km3=My_vector3D(exp(2*a),2*exp(a)-2*exp(2*a),-2*exp(a)+2*exp(2*a));
    My_vector3D y_km2=My_vector3D(exp(2*x_km2),2*exp(x_km2)-2*exp(2*x_km2),-2*exp(x_km2)+2*exp(2*x_km2));
    My_vector3D y_km1=My_vector3D(exp(2*x_km1),2*exp(x_km1)-2*exp(2*x_km1),-2*exp(x_km1)+2*exp(2*x_km1));
    My_vector3D y_k=My_vector3D(exp(2*x_k),2*exp(x_k)-2*exp(2*x_k),-2*exp(x_k)+2*exp(2*x_k));
    My_vector3D y_kp1;
    
    
    
    double max_err=0.0;
    double tek_err=0.0;
    int cnt_steps=0;
    while (x_k<=b){
        cnt_steps+=1;
        if (eps<0){y_kp1=get_y_kp1_Adams_notAvtom(x_k,x_km1,x_km2,x_km3,y_k,y_km1,y_km2, y_km3, h);
                    }
        else {auto res=get_y_kp1_Adams_Avtom(x_k,x_km1,x_km2,x_km3,y_k,y_km1,y_km2, y_km3, h, eps);
                   y_kp1=std::get<0>(res);
                    h=std::get<1>(res);
                    }
        tek_err=get_err_at_point(x_k+h,y_kp1);
        //printf("\n\n\n%f\n\n\n",tek_err);
        if (x_k+h <=b){max_err=fmax(tek_err,max_err);}
        x_km3=x_km2;
        x_km2=x_km1;
        x_km1=x_k;
        x_k=x_k+h;
        y_km3=y_km2;
        y_km2=y_km1;
        y_km1=y_k;
        y_k=y_kp1;
    }
    if (eps>0) {printf("cnt_steps=%d ? %d\n",cnt_steps, n_steps);}
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
    
    
    for (double n_steps=10; n_steps<=1000000; n_steps=n_steps*10){
        printf("max_err=%le\n",get_err_at_all_segment(a, b, n_steps));
    }
    
    printf("Now automatical step:\n");
    
    for (double n_steps=10; n_steps<=10000; n_steps=n_steps*10){
        printf("max_err=%le\n",get_err_at_all_segment(a, b, n_steps, eps));
    }
    
    
    My_vector3D v1(1,0,0);
    My_vector3D v2(2,0,0);
    My_vector3D v3(3,0,0);
    (v1+v2+v3).pechat();
    printf("Goodbuy!\n");
        
    return 0;

}
