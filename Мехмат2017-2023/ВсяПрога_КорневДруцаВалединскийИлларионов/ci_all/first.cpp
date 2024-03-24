#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pechat(char** array, int n){
  int i = 0;
  for(i=0; i<n; i = i+1) printf("%s  ", array[i]);
  printf("\n");


}

int main(){
   

  FILE*f;
  f = fopen("input.txt","r");
  if(f==0) { printf("Cannot open input.txt"); return -1;}
  
  //int k;
  //char* str;
  //k = fscanf(f,"%c",str);
  //printf("%d",k);
  //if (k==-1) {printf ("Empty file\n"); return -1;}
  int k;
  char** array = (char**)malloc(0);
  
  
  int words =0;
  char slovo[255];
  k = fscanf(f, "%s",slovo);
  printf("%c",slovo[200]);
 
  
  while (k == 1){
  printf("slovo %s\n",slovo);
  words = words + 1;
  array = (char**)realloc(array,words);
  printf("555");pechat(array,words);
  array[words-1] = (char*)malloc(255*sizeof(char));
  array[words-1] = slovo;
  printf("arr %s\n", array[words-1]);
  k = fscanf(f,"%s",slovo);
  printf("%d\n",words);
  pechat(array,words);

}
  printf("%s\n",array[2]); 




  printf("Hello\n");
  fclose(f);
  return 0;

}
