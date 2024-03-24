#include<stdio.h>
#include<stdlib.h>

void pechat(int* mas, int n){
int i=0; int j=0;
printf("\n");
for (i=0;i<n;i=i+1){for (j=0; j<n; j=j+1){printf("%d ",mas[i*n+j]);}
			    printf("\n");

		    }
}

int main(){
	int n; int m; int flag=0;
	FILE*f;
	f=fopen("input.txt","r");
	if (f==0) return 0;
	
	flag=fscanf(f,"%d %d",&n,&m);
	if (flag!=2) return 0;
	
	
	int* mas=(int*)malloc(n*n*sizeof(int));
	int i=0; int j=0; int k=0;
	for (i=0;i<n*n;i=i+1){mas[i]=0;}
	int x; int y;

	for (i=0; i<m; i=i+1){ flag=0; 
				flag=fscanf(f,"%d %d",&x,&y);
				if (flag!=2) return 0;

				
				//printf("x=%d y=%d\n",x,y);

				mas[y-1+(x-1)*n]=1;
				

				for (k=0; k<n; k=k+1){mas[(x-1)*n+k]=1;}
				for (k=0; k<n; k=k+1){mas[(y-1)+k*n]=1;}
				//pechat(mas,n);
					
				//for (k=0; k<n; k=k+1){ printf("x-k=%d y+k=%d \n",x-k,y+k); 
				//		      if (((x-k) >5)||((x-k) <0)||((y+k) >5)||((y+k) <0)) printf("k=%d\n",k);}

				for (k=0; k<n; k=k+1){  if (((x-k) >5)||((x-k) <0)||((y+k) >5)||((y+k) <0)) break;
							mas[((x-1-k)*n +(y-1+k))]=1;
						      }
				for (k=0; k<n; k=k+1){  if (((x+k) >5)||((x+k) <0)||((y-k) >5)||((y-k) <0)) break;
							mas[((x-1+k)*n +(y-1-k))]=1;
						      }
				for (k=0; k<n; k=k+1){  if (((x+k) >5)||((x+k) <0)||((y+k) >5)||((y+k) <0)) break;
							mas[((x-1+k)*n +(y-1+k))]=1;
						      }
				for (k=0; k<n; k=k+1){  if (((x-k) >5)||((x-k) <0)||((y-k) >5)||((y-k) <0)) break;
							mas[((x-1-k)*n +(y-1-k))]=1;
						      }

			
				//pechat(mas,n);
				

			      }


	//pechat(mas,n);
	int cnt=0;
	for (i=0; i<n*n; i=i+1){if (mas[i]==0)cnt=cnt+1;}
	printf("%d\n",cnt);
	
	free(mas);
	fclose(f);
	
	

	return 0;
}