
verbatimtex \input chert etex;


beginfig(1);




numeric ux, uy;

ux = 2mm; uy = 25mm;

numeric zz; zz=20mm;

 
drawarrow (-40ux,0)--(40ux,0);
drawarrow (0,0)--(0,25ux);

 
draw (-40ux,1zz)--(0,1zz)--(1zz,0)--(40ux,0)  withpen pencircle scaled 0.4ux withcolor blue;

draw (-40ux,1zz)--(0.25zz,1zz)--(0.5zz,0)--(40ux,0) withcolor red;





endfig;






end.