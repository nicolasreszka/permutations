#include "permutation.h"
#include <stdio.h>

int main(){
	int n=3;
	permutation ** G = Table(n);
	int fact_n = 6; 
	int i,j;
	printf("     | ");
	for(i=0;i<fact_n;i++) printf("%3d | ",i+1);
	printf("\n");
	for(i=0;i<fact_n * 6+6;i++) printf("-");
	printf("\n");
	for(i=0;i<fact_n;i++){
		printf("%3d  | ",i+1);
		for(j=0;j<fact_n;j++){
			printf("%3d | ",G[i][j].num);
		}
		printf("\n");
	}
}
