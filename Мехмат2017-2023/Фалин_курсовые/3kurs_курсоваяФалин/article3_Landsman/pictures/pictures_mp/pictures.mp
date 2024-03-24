
verbatimtex
\documentclass{article}
\usepackage{palatino,concmath,ccfonts}
\begin{document}
etex

beginfig(1);

draw fullcircle scaled 30 withcolor red;
draw fullcircle scaled 40 withcolor blue;
draw fullcircle scaled 50 withcolor green;

numeric u; u:=2mm;
numeric my_infinity; infinity:=-100mm;

drawarrow (-50mm,u)--(0,u)--(0,0)--(50u,0)  withpen pencircle scaled 0.4u;



def phi(expr x, s) = s*mexp (-(s**2)*(x**2))/(sqrt (3.14))  enddef;
 
ahangle:=25;  
ahlength:=6bp;
 

numeric ux, uy, yshift;
path p[];
ux = 1mm; uy = 15mm;
yshift = .5mm;
k = 1;
 
drawarrow (-40ux,-yshift)--(40ux,-yshift);
drawarrow (0,-yshift)--(0,45ux);

 
for i=1 upto 4:
  p[i] = (0,(phi(k*10*0,i))*uy){right}
  for j=1 upto 9: ..((1*j/10)*ux, (phi(k*j/10,i))*uy) endfor
  for j=1 upto 30: ..(1*j*ux, (phi(k*j,i))*uy) endfor;
endfor;
 
for i=1 upto 4:
   draw p[i] reflectedabout ((0,-1),(0,1));
   draw p[i];
endfor;

endfig;

verbatimtex
\end{document}
etex

end.