
verbatimtex \input chert etex;


beginfig(1);




def phi(expr x, sigm) = mexp (-(x**2) /(2*sigm**2))/(sigm*sqrt (2*3.14))  enddef;
 

numeric ux, uy;

ux = 2mm; uy = 25mm;

 
drawarrow (-40ux,0)--(40ux,0);
drawarrow (0,0)--(0,25ux);

 



path f;
numeric gg; gg=0.4;
numeric start; start=0;

f = (0*ux , phi(0, gg )*uy ) {right}
for i=1 upto 34: ..  ((start+ i)*ux, phi(start + i, gg)*uy ) endfor;

path ff;
ff =  ( (start + 32)*ux ,0)--((start + 8)*ux,0){right}
for i=8 upto 34: --  ((start+ i)*ux, phi(start + i, gg)*uy ) endfor
--cycle;



draw f;
draw f reflectedabout ((0,-1),(0,1));
fill ff withcolor  0.5(0,151,10) +0.5white ;

z1=((start + 8)*ux,0);
fill fullcircle scaled 5 shifted z1 withcolor  blue;
draw ((start + 8)*ux,0)--((start+ 8)*ux, phi(0 + 8, gg)*uy )    withcolor blue ;


endfig;






end.