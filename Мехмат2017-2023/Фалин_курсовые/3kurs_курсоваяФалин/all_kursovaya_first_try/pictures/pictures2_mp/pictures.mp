verbatimtex \input chert etex;

%input frac; input rad-sk;
%input ar-gamma;
ahlength:=2ahlength;
ahangle:=.3ahangle;

vardef prug(expr A,B,C,s)=(unitvector(A-B)--unitvector(A-B)+unitvector(C-B)--unitvector(C-B)) scaled s shifted B enddef;

beginfig(1);
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

draw z.a--z.b--z.c--cycle withpen pencircle scaled 3/2;
draw z.b--z.k;
draw prug(z.b,z.k,z.c,4);
draw prug(z.b,z.m,z.n,4);
draw fullcircle scaled 2length(z.o1-z.h1) shifted z.o1;
draw fullcircle scaled 2length(z.o2-z.h2) shifted z.o2;
%draw z.p3--z.p1--z.p2--z.p4;

draw (z.a+10left--z.c+10right) shifted (0,0);
draw (z.a+4right--z.c+10right) shifted (0,y.m) withpen pencircle;
draw (z.a+10left--z.c+10right) shifted (0,y.b);

drawdblarrow (-5,y.a)--(-5,y.b); 
%label.lft(frac(list(btex$a$etex,RAD(btex3etex)))(btex2etex),(-4,1/2[y.a,y.b]));
drawdblarrow ((x.c+5,y.a)--(x.c+5,y.m));
%picture q; q=frac(list(btex$a$etex,RAD(btex3etex)))(btex2etex);
%label.rt(list(q,btex${}-2r$etex),(x.c+4-15,1/2[y.m,y.b]));
drawdblarrow ((x.c+5,y.b)--(x.c+5,y.m)) shifted 15left;;
label.rt(btex$2r$etex,(x.c+4,1/2[y.c,y.m]));

draw z.h1--z.h3;
draw z.h2--z.h4;

forsuffixes $=a,b,c,k,l,m,n,o1,o2:
fill fullcircle scaled 3 shifted z$; endfor;

forsuffixes $=f,g,h,h1,h2,h3,h4:
fill fullcircle scaled 2.3 shifted z$; endfor;

label.rt(btex$r$etex,left+1/2[z.o1,z.h1]);
label.rt(btex$r$etex,left+1/2[z.o1,z.h3]);
draw prug(z.o1,z.h1,z.a,4);
draw prug(z.o1,z.h3,z.l,4);
label.lft(btex$r$etex,right+1/2[z.o2,z.h2]);
label.lft(btex$r$etex,right+1/2[z.o2,z.h4]);
draw prug(z.o2,z.h2,z.c,4);
draw prug(z.o2,z.h4,z.n,4);

label.bot(btex$A$etex,z.a);
label.top(btex$B$etex,z.b);
label.bot(btex$C$etex,z.c);
label.bot(btex$K$etex,z.k);
label.lft(btex$O\mkern-1mu_1$etex,z.o1);
label.rt(btex$O\mkern-1mu_2$etex,z.o2);
label.ulft(btex$L$etex,z.l);
label.ulft(btex$M$etex,z.m);
label.urt(btex$N$etex,z.n);

label.bot(frac(btex$a$etex,btex2etex),1/2[z.a,z.k]);
label.bot(frac(btex$a$etex,btex2etex),1/2[z.c,z.k]);
%label.top(btex$a$etex,origin) rotated angle(z.b-z.a) shifted 0.6[z.a,z.b];
%label.top(btex$a$etex,origin) rotated (angle(z.b-z.c)-180) shifted 0.4[z.b,z.c]  ;





endfig;
end