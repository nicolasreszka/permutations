#include "permutation.h"

int main(){
	permutation p=Ident(4);
	permutation q;
	while(1){
		Print(p);
		q=Next(p);
		if (Egal(q,p)) break;
		p=q;
	}
}
