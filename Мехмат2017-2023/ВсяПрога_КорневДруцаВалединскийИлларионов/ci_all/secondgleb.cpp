#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
   

  FILE*f;
  f = fopen("input.txt","r");
  if(f==0) { printf("Cannot open input.txt"); return -1;}
  
  long long int a; long long int b;
  fscanf(f,"%ld",a);
  fscanf(f, "%ld", b);
  printf("%lld\n",a);
  printf("%lld\n",b);



  printf("Hello\n");
  fclose(f);
  return 0;

}
