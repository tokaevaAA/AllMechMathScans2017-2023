#include <stdio.h>
#include <stdlib.h>
#include <string.h>





char*  vvod(int* n){
    char c ;
    //int n=0;
    char* a=0;
    while(((c=getchar())!='\n')){
	if((c>='0') && (c<= '9')){
	    a = (char*)realloc(a,*n+1);
	    a[*n] = c;
	    *n = *n+1;

	}
	
    }
    //printf("%c\n", a[0]);
    return a;
}


void pechat(char*a, int n){
    //printf("nachalo\n");
    int i=0;
    for (i=0; i< n; i=i+1) printf("%c", a[i]);
    printf("\n");



}


char* addition(char* a, char* b, int n, int m,int* k){
    char* c = 0;
    *k=0;
    int  sum;
    int  p=0;
    while ((n>0)||(m>0)) {
	sum = (n ? int(a[n-1]-'0'):0) + (m ? int(b[m-1]-'0'):0)+ p;
	//printf("sum=%d\n", sum); 
        //printf ("%d %d\n", n , m);
	c = (char*)realloc(c, *k+1);
	c[*k] = char(int('0') + sum%10);
	p = sum/10;
	*k = *k+1;
	if(n>=1) n = n-1;
	if (m>=1) m = m-1;
    }
    printf("p=%d\n",p);
    
    if (p==1){
	c = (char*)realloc(c, *k +1);
	c[*k] = char(49);
	*k = *k +1;
    
    }
    
    char cmp;
    int i=0;
    for(i = 0; i < *k/2; i = i+1){cmp = c[*k-i-1]; c[*k-i-1] = c[i]; c[i] = cmp;}
    
    return c;


}


char* difference(char* a, char* b, int n, int m, int *k){
    char*  d = 0;
    *k = 0;
    int dif;
    int p = 0;
    while ((n > 0)||(m>0)){
	dif = (n ? int(a[n-1] - '0'):0) - (m ? int(b[m - 1] - '0'):0) + p;
        //printf("dif=%d %d %d %d \n", dif,p, n, m);
	d = (char*)realloc(d, *k + 1);
	if (dif>=0) {d[*k] =char(int('0') + dif%10); p = dif/10;}
	if (dif <0) {d[*k] = char(int('0') + dif%10 + 10); p = -1;}
	*k = *k + 1;
	if (n>=1) n= n-1;;
	if (m>=1) m= m-1;;
	
    }
    
    //if (p == 1){
         // printf("ggg");
        
	//d = (char*)realloc(d, *k+1);
	//d[*k] = char(49);
	//*k =*k + 1;
	
    //}
    //pechat(d,*k);  
    //printf("kkkk=%d\n",*k);  

    char cmp;
    int i = 0;
    for(i = 0; i < *k/2; i++){cmp = d[*k - i - 1]; d[*k - i - 1] = d[i]; d[i] = cmp;}
    
    //pechat(d,*k);
    
    //printf("kkk=%d\n",*k);

    if (d[0] == '0') {
        //printf("yyy");
        int cnt = 0;
        int j=0;
        while ( (j< *k) && (d[j]== '0')){ j=j+1;cnt = cnt +1;}
       for (j=0; j< cnt; j=j+1){
	for (i=0; i<(*k-1); i=i+1) d[i] = d[i+1];
	d = (char*)realloc(d,*k-1);
	*k= *k-1;}
    }
    //printf("kk=%d\n",*k);    

    return d;
}



int sravn(char* a, char*b, int n, int m){
    if (n > m) {return 1;}
    if (n<m) return 2;
    //printf("fffff");
    int i=0;
    //for (i=0; i<n; i= i+1) { if (a[i] < b[i]) {return 2;}}
    while (a[i]==b[i]) i=i+1;
    if ((i<n)&& (a[i] <b[i])) return 2;
    return 1;
    


}


int nepchast(char* a, char* b, int n, int m ){
    //printf("%d %d\n", n ,m);
    int k = 0;
    if (n < m) return 0;
    if ((n==m)&& (n==1)) {if (a[0]<b[0]) return 0; else return (int(a[0])/int(b[0]));}
    char* c = difference(a,b,n,m,&k);
    //pechat(c,k);
    //printf("k=%d ",k);
    int t=1;
    while(sravn(c,b,k,m) == 1 ) { t= t+1;  c = difference(c,b,k,m,&k);}
    
    return t;




}


char* otvet(char*a, char*b, int n, int m, int* length){
    *length = 0;
    int koef = 0;
    char* quotient = 0;
    char* dop =0;
    int dlindop = 0;
    int prosesedln = m;
    int tekln = m;
    char* tekdiv = (char*)malloc(m*sizeof(char));
    int i=0;
    for (i=0; i<m;i=i+1) tekdiv[i] = a[i];
    if (n<m){*length = 1; quotient = (char*)realloc(quotient,*length);quotient[*length-1] = '0'; return quotient;}

    int flag=0;
    int itisostatok=0;
    


    while (prosesedln <=n){
        flag=0;
	printf ("tekln=%d prosesed=%d\n", tekln, prosesedln);
        pechat(tekdiv, tekln);
        pechat(quotient,*length);



    if((sravn(tekdiv,b,tekln,m) == 2)&&(flag==0)) {flag=1;prosesedln = prosesedln +1; tekln = tekln +1; tekdiv = (char*)realloc(tekdiv,tekln); tekdiv[tekln-1] = a[prosesedln-1]; 
                                      *length = *length +1; if (((prosesedln <= n)&&(itisostatok==0))||((tekln==1)&&(sravn(tekdiv,b,tekln,m)==2))) {quotient= (char*)realloc(quotient,*length); quotient[*length-1] = '0';} 
                                     itisostatok=0;}



    
    if((sravn(tekdiv,b,tekln,m) == 1)&&(flag==0)) {itisostatok=1;flag=1;koef = nepchast(tekdiv,b,tekln,m); printf ("koef=%d\n",koef); *length = *length +1; 
                                       quotient = (char*)realloc(quotient,*length); quotient[*length-1] = ('0' + char(koef));
                                        for (i=0; i<koef; i=i+1) tekdiv = difference(tekdiv,b,tekln,m,&tekln); }
                //dop = b; dlindop = m; for( i=0; i< koef; i=i+1) dop=addition(dop,b,dlindop,m,&dlindop); tekdiv = difference(tekdiv,dop,tekln,dlindop,&tekln); }

   

     }



    if (quotient[0] == '0') {
        //printf("yyy");
	for (i=0; i<(*length-1); i=i+1) quotient[i] = quotient[i+1];
	quotient = (char*)realloc(quotient,*length-1);
	*length= *length-1;
    }



    return quotient;

}

int main(void){
    int n =0; int m=0;
    char* a = vvod(&n);
    char* b = vvod(&m);
    
    int sr;
    
    //printf("n=%d\n",n);
    //pechat(a,n);
    //pechat(b,m);
    //printf("dddd %d\n", int((a[0] + a[1]-'0' - '0')));
    int l=0;
    //char* c = difference(a,b,n,m,&l);
    //printf("l=%d\n", l);
    //pechat(c,l);

    
    //sr=nepchast(a,b,n,m);
    //printf("sr=%d\n", sr);

    char* c = otvet(a,b,n,m,&l);
    printf("the answer is ");
    pechat(c,l);
    
    free(a);
    free(b);
    free(c);
    


    return 0;

}