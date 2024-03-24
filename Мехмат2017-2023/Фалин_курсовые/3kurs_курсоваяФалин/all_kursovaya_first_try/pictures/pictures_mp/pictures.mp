
verbatimtex \input chert etex;


beginfig(1);

draw fullcircle scaled 30 withcolor red;
draw fullcircle scaled 40 withcolor blue;
draw fullcircle scaled 50 withcolor green;

numeric u; u:=2mm;
numeric my_infinity; infinity:=-100mm;

%drawarrow (-50mm,u)--(0,u)--(0,0)--(50u,0)  withpen pencircle scaled 0.4u;



def phi(expr x, s) = s*mexp (-(s**2)*(x**2))/(sqrt (3.14))  enddef;


def phip(expr x, sigm) = mexp (-(x**2) /(2*sigm**2))/(sigm*sqrt (2*3.14))  enddef;
 

numeric ux, uy, yshift;
path p[];
ux = 2mm; uy = 25mm;
yshift = 0.8mm;
k = 1;
 
drawarrow (-40ux,0)--(40ux,0);
drawarrow (0,0)--(0,25ux);

 
for i=1.5 upto 4.5:
 p[i] = (0,(phi(k*10*0,i))*uy){right}
for j=1 upto 9: ..((1*j/10)*ux, (phi(k*j/10,i))*uy) endfor
for j=1 upto 30: ..(1*j*ux, (phi(k*j,i))*uy) endfor;
endfor;
 
for i=1.5 upto 1.5:
   %draw p[i] reflectedabout ((0,-1),(0,1));
   %draw p[i];
endfor;

numeric start; start=0; 
numeric step; step = 1; 
numeric stop; stop =50; 

numeric gg; gg=0.4;

path q;
q:=  (start*ux , phip(start, gg )*uy ).. ((start + step)*ux, phip(start + step, gg)*uy ).. ((start + 2*step)*ux, phip(start + 2*step, gg)*uy )..
 ((start + 3*step)*ux, phip(start + 3*step, gg)*uy )..((start + 4*step)*ux, phip(start + 4*step, gg)*uy )..((start + 5*step)*ux, phip(start + 5*step, gg)*uy )..
 ((start + 6*step)*ux, phip(start + 6*step, gg)*uy )..((start + 7*step)*ux, phip(start + 7*step, gg)*uy )..((start + 8*step)*ux, phip(start + 8*step, gg)*uy )..
 
 ((start + 9*step)*ux, phip(start + 9*step, gg)*uy )..((start + 9*step)*ux, phip(start + 9*step, gg)*uy )..((start + 10*step)*ux, phip(start + 10*step, gg)*uy )..
 ((start + 11*step)*ux, phip(start + 11*step, gg)*uy )..((start + 12*step)*ux, phip(start + 12*step, gg)*uy )..((start + 13*step)*ux, phip(start + 13*step, gg)*uy )..
  ((start + 14*step)*ux, phip(start + 14*step, gg)*uy )..((start + 15*step)*ux, phip(start + 15*step, gg)*uy )..((start + 16*step)*ux, phip(start + 16*step, gg)*uy )..
 ((start + 17*step)*ux, phip(start + 17*step, gg)*uy )..((start + 18*step)*ux, phip(start + 18*step, gg)*uy )..((start + 19*step)*ux, phip(start + 19*step, gg)*uy )..
 ((start + 20*step)*ux, phip(start + 20*step, gg)*uy )..((start + 21*step)*ux, phip(start + 21*step, gg)*uy )..((start + 22*step)*ux, phip(start + 22*step, gg)*uy )..
 ((start + 23*step)*ux, phip(start + 23*step, gg)*uy ).. ((start + 24*step)*ux, phip(start + 24*step, gg)*uy )..((start + 25*step)*ux, phip(start + 25*step, gg)*uy )..
 ((start + 26*step)*ux, phip(start + 26*step, gg)*uy )..((start + 27*step)*ux, phip(start + 27*step, gg)*uy )..((start + 28*step)*ux, phip(start + 28*step, gg)*uy )..
 ((start + 29*step)*ux, phip(start + 29*step, gg)*uy )..((start + 30*step)*ux, phip(start + 30*step, gg)*uy )..((start + 31*step)*ux, phip(start + 31*step, gg)*uy )..
 ((start + 32*step)*ux, phip(start + 32*step, gg)*uy ) ..((start + 33*step)*ux, phip(start + 33*step, gg)*uy )..((start + 34*step)*ux, phip(start + 34*step, gg)*uy );
 
 path qq;
 
 qq:= ( (start + 32*step)*ux ,0)--((start + 8*step)*ux,0)-- ((start + 8*step)*ux, phip(start + 8*step, gg)*uy )..
 ((start + 9*step)*ux, phip(start + 9*step, gg)*uy )..((start + 9*step)*ux, phip(start + 9*step, gg)*uy )..((start + 10*step)*ux, phip(start + 10*step, gg)*uy )..
 ((start + 11*step)*ux, phip(start + 11*step, gg)*uy )..((start + 12*step)*ux, phip(start + 12*step, gg)*uy )..((start + 13*step)*ux, phip(start + 13*step, gg)*uy )..
  ((start + 14*step)*ux, phip(start + 14*step, gg)*uy )..((start + 15*step)*ux, phip(start + 15*step, gg)*uy )..((start + 16*step)*ux, phip(start + 16*step, gg)*uy )..
 ((start + 17*step)*ux, phip(start + 17*step, gg)*uy )..((start + 18*step)*ux, phip(start + 18*step, gg)*uy )..((start + 19*step)*ux, phip(start + 19*step, gg)*uy )..
 ((start + 20*step)*ux, phip(start + 20*step, gg)*uy )..((start + 21*step)*ux, phip(start + 21*step, gg)*uy )..((start + 22*step)*ux, phip(start + 22*step, gg)*uy )..
 ((start + 23*step)*ux, phip(start + 23*step, gg)*uy ).. ((start + 24*step)*ux, phip(start + 24*step, gg)*uy )..((start + 25*step)*ux, phip(start + 25*step, gg)*uy )..
 ((start + 26*step)*ux, phip(start + 26*step, gg)*uy )..((start + 27*step)*ux, phip(start + 27*step, gg)*uy )..((start + 28*step)*ux, phip(start + 28*step, gg)*uy )..
 ((start + 29*step)*ux, phip(start + 29*step, gg)*uy )..((start + 30*step)*ux, phip(start + 30*step, gg)*uy )..((start + 31*step)*ux, phip(start + 31*step, gg)*uy )..
 ((start + 32*step)*ux, phip(start + 32*step, gg)*uy ) ..((start + 33*step)*ux, phip(start + 33*step, gg)*uy )..((start + 34*step)*ux, phip(start + 34*step, gg)*uy )--cycle;

 

draw q;
draw q reflectedabout ((0,-1),(0,1));

fill qq withcolor  0.5(0,151,10) +0.5white ;


z1=((start + 8*step)*ux,0);

draw fullcircle scaled 5 shifted z1 withcolor  red;
%label.bot(btex $i_1$ etex, (10,10) );


endfig;




vardef prug(expr A,B,C,s)=(unitvector(A-B)--unitvector(A-B)+unitvector(C-B)--unitvector(C-B)) scaled s shifted B enddef;

beginfig(2);
numeric u; u = 4cm;
z.a = (0,0);
z.b = u*dir 60;
z.c = (u,0);
z.b1 = z.b reflectedabout(z.a,z.c);
z.k = 1/2[z.b,z.b1];

z.o1 = z.a + whatever*(unitvector(z.b-z.a)+unitvector(z.c-z.a));
z.o1 = z.k + whatever*(unitvector(z.b-z.k)+unitvector(z.a-z.k));

z.o2 = z.k + whatever*(unitvector(z.b-z.k)+unitvector(z.c-z.k));
z.o2 = z.c + whatever*(unitvector(z.k-z.c)+unitvector(z.b-z.c));

z.h1 = 1/2[z.o1,z.o1 reflectedabout(z.a,z.c)];
z.h2 = 1/2[z.o2,z.o2 reflectedabout(z.a,z.c)];

z.f = whatever[z.a,z.b];
(z.f-z.o1) dotprod (z.a-z.b)= 0;

z.g = whatever[z.b,z.k];
(z.g-z.o2) dotprod (z.b-z.k)= 0;

z.h = whatever[z.b,z.c];
(z.h-z.o2) dotprod (z.b-z.c)= 0;


z.p1 = (x.o1,y.o1 + length(z.o1-z.h1));
z.p2 = (x.o2,y.o2 + length(z.o2-z.h2));
z.p1 = 1/2[z.p3,z.p2];
z.p2 = 1/2[z.p1,z.p4];

z.o1 = 1/2[z.h1,z.h3];
z.o2 = 1/2[z.h2,z.h4];


z.l=whatever[z.b,z.a]=whatever[z.p1,z.p2];
z.n=whatever[z.b,z.c]=whatever[z.p1,z.p2];
z.m = 1/2[z.p1,z.p2];

draw z.a--z.b--z.c--cycle;
draw z.b--z.k;
draw prug(z.b,z.k,z.c,5);
draw fullcircle scaled 2length(z.o1-z.h1) shifted z.o1;
draw fullcircle scaled 2length(z.o2-z.h2) shifted z.o2;
draw z.p3--z.p1--z.p2--z.p4;



fill fullcircle scaled 3 shifted z.a;
fill fullcircle scaled 3 shifted z.b;
fill fullcircle scaled 3 shifted z.c;
fill fullcircle scaled 3 shifted z.k;
fill fullcircle scaled 3 shifted z.o1;
fill fullcircle scaled 3 shifted z.o2;
fill fullcircle scaled 3 shifted z.f;
fill fullcircle scaled 3 shifted z.g;
fill fullcircle scaled 3 shifted z.h;
fill fullcircle scaled 3 shifted z.h1;
fill fullcircle scaled 3 shifted z.h2;
fill fullcircle scaled 3 shifted z.h3;
fill fullcircle scaled 3 shifted z.h4;
fill fullcircle scaled 3 shifted z.l;
fill fullcircle scaled 3 shifted z.m;
fill fullcircle scaled 3 shifted z.n;




label.bot(btex$A$etex,z.a);
label.top(btex$B$etex,z.b);
label.bot(btex$C$etex,z.c);
label.bot(btex$K$etex,z.k);
label.bot(btex$O\mkern-1mu_1$etex,z.o1);
label.bot(btex$O\mkern-1mu_2$etex,z.o2);
label.ulft(btex$L$etex,z.l);
label.urt(btex$M$etex,z.m);
label.urt(btex$N$etex,z.n);

label.bot(btex$a$etex,1/2[z.a,z.c] + (0,-7));
label.top(btex$a$etex,origin) rotated angle(z.b-z.a) shifted 0.6[z.a,z.b];
label.top(btex$a$etex,origin) rotated (angle(z.b-z.c)-180) shifted 0.4[z.b,z.c]  ;





endfig;


end.