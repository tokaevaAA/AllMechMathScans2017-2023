#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	FILE*f;
	f=fopen("input.txt","r");
	char buf[128];
	fgets(buf,128,f);
	fclose(f);
	int i=0;
	for(i=0;i<128;i=i+1){if(buf[i]=='0') {printf("i=%d\n",i);break;} 					     printf("%c",buf[i]);}

	printf("ggggg\n");
	char* pos=strstr(buf,"from");
	int a=0; 
	char tekslovo[20];
	sscanf(pos+4,"%d",&a);

	int sdvig=0;
	for(i=0; i<a; i=i+1){
	sscanf(pos+6+sdvig,"%s  ",tekslovo);printf("tekslovo=%s\n",tekslovo);
	sdvig=sdvig+int(strlen(tekslovo))+1;
	}

	pos=strstr(buf,"Rocket");
	if (pos==0)printf("no such string \n");

	pos=strstr(buf,tekslovo);
	sscanf(pos,"%s ",tekslovo);printf("tekslovo=%s\n",tekslovo);



	printf("cnt=%d\n",a);


	
   

	return 0;
	

}
 