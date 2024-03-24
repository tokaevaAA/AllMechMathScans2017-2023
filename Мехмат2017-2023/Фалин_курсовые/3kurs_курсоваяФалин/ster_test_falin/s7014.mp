verbatimtex \input chert etex;
numeric Cr; Cr=3;
vardef CA(expr P,Q)=P cutafter Q cutafter (fullcircle scaled 2Cr shifted (P intersectionpoint Q)) enddef;
vardef CB(expr P,Q)=P cutbefore Q cutbefore (fullcircle scaled 2Cr shifted (P intersectionpoint Q)) enddef;
vardef CC(expr P)(text T)=image(path _prev; 
for p=T: if not known _prev: 
if arclength(P cutafter p)>Cr: draw CA(P)(p); fi; else: 
if arclength(P cutafter p cutbefore _prev)>2Cr: draw CB(CA(P)(p))(_prev); fi; fi; _prev:=p; endfor;
if arclength(P cutbefore _prev)>Cr: draw CB(P)(_prev); fi;) enddef;

numeric grad_a; grad_a=40;
vardef grad(expr P,_c,c_)=picture _tmp; _tmp=image(fill P rotated -grad_a;);
numeric _x,x_,_y,y_; (_x,_y)=llcorner _tmp; (x_,y_)=urcorner _tmp;
picture _tmp; _tmp=image(for x=floor _x upto x_: fill (x,_y-1)--(x+2,_y-1)--
(x+2,y_+1)--(x,y_+1)--cycle withcolor ((x-_x)/(x_-_x))[_c,c_]; endfor;)
rotated grad_a; clip _tmp to P; _tmp enddef;

vardef _ks(expr A,B,C)=save _a,_b,_c,_p; numeric _a[],_b[],_c[],_p[];
_a1=Length(A-B); _a2=length(dr A-dr B); _b1=Length(C-B); _b2=length(dr C-dr B);
_c1=Length(A-C); _c2=length(dr A-dr C); 2_p1=_a1+_b1+_c1; 2_p2=_a2+_b2+_c2;
sqrt(_p2/_p1*(_p2-_a2)/(_p1-_a1)*(_p2-_b2)/(_p1-_b1)*(_p2-_c2)/(_p1-_c1)) enddef;

primarydef P scalarprod Q = 
redpart P*redpart Q+greenpart P*greenpart Q+bluepart P*bluepart Q enddef;

vardef Length primary T=redpart T++greenpart T++bluepart T enddef;
vardef Unitvector primary T=T/Length T enddef;
vardef pr primary T = redpart T*ux + greenpart T*uy + bluepart T*uz enddef;
vardef dr primary T = redpart T*ux + greenpart T*uy + bluepart T*uz enddef;

def gra(expr n)(text T)=
numeric _n; _n=0; color tt[];
path g; g=forsuffixes $=T: begingroup tt[incr _n]=t$; dt$ endgroup-- endfor cycle;
numeric _o; _o=_ks(tt1,tt2,tt3);
draw grad(g,_o[.5C[n],C[n]],(sqrt _o)[.5white,1/7[white,C[n]] ]);
enddef;

vardef Prug(expr A,B,C,s)=(dr(Unitvector(A-B))--
dr(Unitvector(A-B))+dr(Unitvector(C-B))--dr(Unitvector(C-B)))
scaled s shifted dr(B) enddef;




beginfig(1);
save x,y,z; numeric x[],y[],z[];
vardef t@#=(x@#,y@#,z@#) enddef;
vardef xy@#=(x@#,y@#) enddef;
vardef dt@#=pr(t@#) enddef;
pair ux,uy,uz;
numeric elevation,rotation; rotation=-25; elevation=17;
uz=(0,cosd elevation);
ux=dir rotation yscaled sind elevation;
uy=dir (rotation+90) yscaled sind elevation;
vardef pr primary T = redpart T*ux + greenpart T*uy + bluepart T*uz enddef;




def next_layer=
setbounds currentpicture to bb; 
shipit; picture qqqq; qqqq=currentpicture; clearit; 
charcode:=charcode+1;
draw qqqq withcolor black; shipit; clearit;
charcode:=charcode+1;
enddef;

path bb; bb=(-3,-27)--(191,97)--cycle;



numeric a ; a = 5 cm; h =  a/1.5;
numeric c; c=2.5 cm;
numeric d; d = sqrt(2c*c + 0.25*h*h);
numeric xx; xx=0.15*h*h/(4*d);
numeric fr; fr = 0.2727272727272727;


color C[];
C1=white-(1,2,4)/10;
C2=1/2[white-red,blue];
C3=.7green;
C4=red;

C11=(white-(0,.72,1))*.55;
C12=.7C2;
C13=.4green;
C14=.7red;




t.a = (0,0,0);
t.b= (a,0,0);
t.c=(0,-a,0);
t.d=(0,0,a);



t.k1=(0,-c,0.5h);
t.l1=(c,0,h);
t.m1=(0,c,h);
t.n1=(-c,0,0.5h);

t.p=( 0.5*c , 0.5*c ,0);
t.p1=( 0.5*c , 0.5*c ,h);
t.q1=t.p1 +  d*Unitvector (t.k1-t.l1);

t.h= t.q1+fr* (t.l1-t.k1);
t.h1= t.q1+(fr+0.05)* (t.l1-t.k1);



drawarrow dt.a--dt.b;
drawarrow dt.a--dt.c;
drawarrow dt.a--dt.d;

draw dt.k1--dt.l1--dt.m1--dt.n1--dt.k1;
drawarrow   dt.a--dt.h withcolor blue  withpen pencircle scaled 0.9;

draw Prug(t.a,t.h,t.h1,5);
draw dt.h--dt.h1;
drawarrow dt.a -- (0.3dt.l1 + 0.5dt.m1);
drawarrow dt.a -- 0.5(dt.n1+dt.h);
drawarrow dt.p1--(dt.p1+0.5(dt.h-dt.a));


fill fullcircle scaled 3 shifted dt.a ;




label.bot(btex$O$etex,dt.a);
label.bot(btex$x$etex,dt.b);
label.bot(btex$y$etex,dt.c);
label.top(btex$z$etex,dt.d);
label.top(btex$H$etex,dt.h);
label.rt(btex$X$etex,0.5(dt.a+dt.h));
label.rt(btex$n=Y$etex,dt.p1+ 0.5(dt.h-dt.a));




endfig;



end