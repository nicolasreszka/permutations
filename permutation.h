#ifndef _PERMUTATION_H
#define _PERMUTATION_H
#define MAX 50

typedef struct permutation{
	int n; /* n < MAX*/
	int t[MAX];
	int decomp; /* booléen pour savoir si la permuation est décomposé en cycles ou pas */
	int num; /*rang de la permutation dans l'ordre léxicographique */
} permutation;


permutation Scanf(void);
permutation Ident(int n);
permutation Comp(permutation p,permutation q);
permutation Pow(permutation p,long int alpha);
permutation Inv(permutation p);
void Print(permutation p);
void Decomp(permutation * p);
void Recomp(permutation * p);
permutation  Next(permutation p);
int Egal(permutation p,permutation q);
int Ordre(permutation p);
permutation ** Table(int n);
void PrintGroup(permutation ** G,int n);
#endif

