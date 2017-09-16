#include "permutation.h"
#include <stdio.h>

int main(){
	permutation p,q;
	p=Scanf();
	q=Scanf();
	printf("p : ");
	Print(p);
	printf("q : ");
	Print(q);

	printf("p*q : ");
	Print(Comp(p,q));
	printf("q*p : ");
	Print(Comp(q,p));

	printf("(p*q)^987654321123456789 : ");
	Print(Pow(Comp(p,q),987654321123456789));
}
