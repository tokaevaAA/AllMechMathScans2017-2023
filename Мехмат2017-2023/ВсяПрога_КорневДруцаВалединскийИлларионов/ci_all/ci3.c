#include <stdio.h>
#include <stdlib.h>

int process(FILE*f);

int main(void)
{ printf("Hello world\n");
  FILE*f;
  f = fopen("input.txt","r");
  if (f==0) {printf("Cannot open input.txt\n"); return -1;}
  process(f);
  fclose(f);
  return 0;

    }

int process(FILE*f){
    int m;
    fscanf(f,"%d\n",&m);
    printf("%d\n",m);
    return 0;
    


    }
