#include "permutation.h"
#include <stdio.h>

int main(){
	permutation p = Scanf();
	printf("Permutation :\t");
	Print(p);
	printf("Ordre : %d\n",Ordre(p));
	printf("Inverse : ");
	Print(Inv(p));
	Decomp(&p);
	printf("Décomposition :\t");
	Print(p);
}
