#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int* Lattice(int *L,int n){
	//neighbours
	float r = (int)rand();
	float t = (int)RAND_MAX;
	int S = n*n*(r/t);
	if(S==n*n){
		S = n*n - 1;
	}
	int y = S%n;
	int x = (S - y)/n;
/*	  3
	2 X 1
	  4
*/
    //printf("\n%d\n",S);
	int *N;
	N=(int*)malloc(5*sizeof(int));
	N[0] = n*x + y;
	N[1] = n*x + (y+1)%n;
	N[2] = n*x + (y-1+n)%n;
	N[3] = n*((x-1+n)%n) + y;
	N[4] = n*((x+1)%n) + y;
	int G;
	float P = (float)rand()/(float)RAND_MAX;
    if(P<0.25){G=1;
	}else if(P<0.50){G=2;
	}else if(P<0.75){G=3;
	}else{G=4;
	}

	//calc like/unlike
	//int like = 0;
	int unlike = 0;
	for(int q=1;q<5;++q){
		//original configuration
		if(L[S]==L[N[q]]){
			//like--;
		}else{
			unlike--;
		}
		//new configuration
		if(L[N[G]]==L[N[q]]){
			//like++;
		}else{
			unlike++;
		}
	}
	int dE = unlike*1; //+ like*0;//new - old

	if(dE<=0){
		L[S]=L[N[G]];
	}else{
		//metropolis
		float p = (float)rand()/(float)RAND_MAX;
		float ex = exp(-dE*10);
		if(p<=ex){
            L[S]=L[N[G]];
		}
	}
	return L;
}

int main(){
	printf("working\n");

	int n = 100;
	int grain = 7;
	int time = 4000;
	int *L;
	L = (int*)malloc(n*n*sizeof(int));

    FILE *F;
    F = fopen("abu_1.csv","w");
	//populate with random
	for(int q=0;q<n*n;++q){
		float y = (int)rand();
		float z = (int)RAND_MAX;
		int R = grain*(y/z);
		//printf("%d\n",R);
		//int R = 15*(int)rand()/(int)RAND_MAX;
		if(R==grain){
			R = grain - 1;
		}
		L[q] = R;
		fprintf(F,"%d,",L[q]);
	}

	//print matrix
	for(int q=0;q<n*n;++q){
		if(q%n!=n-1){
			printf("%d\t",L[q]);
		}else{
			printf("%d\n",L[q]);
		}
	}

    for(int q=0;q<time;++q){//time
        for(int o=0;o<n*n;++o){//selecting every indice
            L = Lattice(L,n);
        }
        fprintf(F,"\n");//space after every array
        for(int u=0;u<n*n;++u){
            fprintf(F,"%d,",L[u]);
        }
		}
    fclose(F);

    /*printf("new matrix from here\n");
	for(int q=0;q<n*n;++q){
		if(q%n!=n-1){
			printf("%d\t",L[q]);
		}else{
			printf("%d\n",L[q]);
		}
	}*/
}
