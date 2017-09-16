/* auteurs : Nicolas Reszka & Guillaume Cau*/

#include "permutation.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static int _fact(int n) {
   	if (n == 0) {
  		return 1; 		
  	} else {
  		return _fact(n-1)*n;
  	}    
}

static int _rang(permutation p) {
	int i, j, n;
	int rang = 1;

	for (i = 0; i < (p.n-1); i++) {
		n = 0;
		for (j = i+1; j < p.n; j++) {
			if (p.t[i] > p.t[j]) {
				n++;
			}
		}

		if (n > 0) {
			rang += (p.n-i-1) * _fact(n);
		}
	}	

	return rang;
}

permutation Scanf(void) {
	permutation p;
	int i = 1;
	int j;
	int count = 0;
	int step = 0;

	char temp[4];
	char text[255];

	/*Lire la permutation sur l'entree standard*/
	fgets(text, 255, stdin);

	while (text[i-1] != ']') { 
		/*Si le caractere itere est une virgule ou un crochet, passer au nombre suivant*/
		if (text[i] == ',' || text[i] == ']') {
			step = 0;
			p.t[count] = atoi(temp);
			count += 1;
			for (j = 0; j < 4; j++) {
				temp[j] = ' ';
			}

		/*Lire le nombre*/
		} else {
			temp[step] = text[i];
			step +=1;
		}
		i++;
	}

	p.n = count;
	p.decomp = 0;
	p.num = _rang(p);

	return p;
}

void Print(permutation p) {
	int i;
	putchar('[');
	for (i = 0; i < p.n; i++) {
		if (i == p.n-1) {
			printf("%d]\n", p.t[i]);
		} else {
			printf("%d, ", p.t[i]);
		}
	}
}

permutation Ident(int n) {
	int i;
	permutation p;

	p.n = n;
	p.decomp = 0;
	p.num = 1;

	for (i = 0; i < n; i++) {
		p.t[i] = i+1;
	}

	return p;
}

void Decomp(permutation * p) {
	permutation id = Ident(p->n);
	permutation tmp = Ident(p->n);
	permutation copy;
	int i;
	int step = 0;
	int orbite;
	int pPosition = 0;

	if (p->decomp) {
		fprintf(stderr,"erreur : permutation deja sous forme de cycles\n");
	} else {
		/*Faire une copie de la permutation*/
		copy.n = p->n;
		for (i = 0; i < p->n; i++) {
			copy.t[i] = p->t[i];
		}	
		i = 0;

		while (id.t[i] != -(p->n)) {
			
			/*Ignorer les elements deja traites*/
			if (id.t[i] > 0) {

				/*Rendre negatifs tous les elements egaux a l'identite*/
				if (p->t[i] == i+1) {
					id.t[i] *= -1;
					copy.t[pPosition] = p->t[i]*(-1);
					pPosition++;
					i++;

				/*Calculer l'orbite*/
				} else {
					orbite = i+1;
					step = 0;
					tmp.t[0] = p->t[(orbite-1)];
					id.t[(tmp.t[0]-1)] *= -1; 
					step++;
					
					while (p->t[(tmp.t[step-1]-1)] != orbite) {
						tmp.t[step] = p->t[(tmp.t[step-1]-1)];
						id.t[(tmp.t[step]-1)] *= -1; 
						step++;
					}
					tmp.t[step] = p->t[(tmp.t[step-1]-1)];
					id.t[(tmp.t[step]-1)] *= -1; 
					tmp.t[step] *= -1; 
					
					/*Copier le cycle dans la copie de p*/
					for (i = 0; i <= step; i++) {
						copy.t[pPosition] = tmp.t[i];
						pPosition++;
					}
					
					i=0;
				}
			} else {
				i++;
			}
		}

		/*Recopier la copie de p dans p*/
		for (i = 0; i < p->n; i++) {
			p->t[i] = copy.t[i];
		}	

		p->decomp = 1;
	}
}

void Recomp(permutation * p) {
	permutation id = Ident(p->n);
	int i;
	int tmp;
	int nextP;

	if (!p->decomp) {
		fprintf(stderr,"erreur : la permutation n'est pas sous forme de cycles\n");
	} else {
		for (i = 0; i < (p->n)-1; i++) {
			/*Verifier si ce n'est pas la fin de l'orbite*/
			if (p->t[i] > 0) {
				/*Effectuer la permutation*/
				nextP = p->t[i+1];
				if (nextP < 0) {
					nextP *= -1;
				}
				nextP -= 1;

				tmp = id.t[p->t[i]-1];
				id.t[p->t[i]-1] = id.t[nextP];
				id.t[nextP] = tmp;
			}
		}

		/*Recopier la permutation*/
		for (i = 0; i < p->n; i++) {
			p->t[i] = id.t[i];
		}

		p->decomp = 0;
	}
}

int Eval(permutation p,int x) {
	if (p.decomp) {
		Recomp(&p);
	}

	return p.t[x-1];
}


int Egal(permutation p,permutation q) {
	int i;

	if (p.decomp) {
		Recomp(&p);
	}

	if (q.decomp) {
		Recomp(&q);
	}

	if (p.n != q.n) {
		return 0;
	}

	for (i = 0; i < p.n; i++) {
		if (p.t[i] != q.t[i]) {
			return 0;
		}
	}

	return 1;
}

permutation Inv(permutation p) {
	int i,j;

	permutation inv = Ident(p.n);

	if (p.decomp) {
		Recomp(&p);
	}

	for(i = 1; i <= p.n; i++){
		for(j = 1; Eval(p,j) != i; j++){
			inv.t[i-1] = j+1;
		}
		if (j == 1) {
			inv.t[i-1] = j;
		}
	}
	return inv;
}

permutation Next(permutation p) {
	int i, j, tmp;

	i = (p.n-1);
	while (p.t[i] <= p.t[i-1]) {
		i--;
		if (i <= 0) {
			return p;
		}
	}

	j = (p.n-1);
	while (p.t[j] <= p.t[i-1]) {
		j--;
	}

	tmp = p.t[i-1];
	p.t[i-1] = p.t[j];
	p.t[j] = tmp;

	j = (p.n-1);
	while (i < j) {
		tmp = p.t[i];
		p.t[i] = p.t[j];
		p.t[j] = tmp;
		i++;
		j--;
	}

	p.num++;
	if (Egal(Ident(p.n),p)) {
		p.num = 1;
	}

	return p;
}

permutation Comp(permutation p,permutation q) {
	int i;
	permutation r;

	if (p.n != q.n) {
		fprintf(stderr,"erreur : la taille des deux permutations doivent etres les memes");
	}

	if (p.decomp) {
		Recomp(&p);
	}

	if (q.decomp) {
		Recomp(&q);
	}
	
	r.n = p.n;
	r.decomp = 0;

	for (i = 0; i < r.n; i++) {
		r.t[i] = p.t[(q.t[i]-1)];
	}

	r.num = _rang(r);
	

	return r;
}

int Ordre(permutation p) {

	permutation id = Ident(p.n);
	permutation tmp = Ident(p.n);
	
	int test = 0;
	int ordre = 0;

	if (p.decomp) {
		Recomp(&p);
	}

	tmp = Comp(tmp,p);

	while (!test) {
		test = Egal(tmp,id);
		tmp = Comp(tmp,p);
		ordre++;
	}

	return ordre;
}

permutation Pow(permutation p,long int alpha) {
	if (alpha == 0) {
		return Ident(p.n);
	} else if (alpha == 1) {
		return p;
	} else if (alpha%2 == 0) {
		return Pow(Comp(p,p),alpha/2);
	} else {
		return Comp(p,Pow(Comp(p,p), (alpha-1)/2));
	}
}

permutation** Table(int n) {
	permutation** G;
	permutation id = Ident(n);
	permutation w = id;
	permutation h;
	int i, j;
	int fact_n = _fact(n); 

	G = (permutation**) malloc( sizeof(permutation*) * fact_n);
	for (i = 0; i < fact_n; i++) {
		G[i] = (permutation*) malloc( sizeof(permutation) * fact_n);
	}

	for (i = 0; i < fact_n; i++) {
		h = id;
		for (j = 0; j < fact_n; j++) {
			G[i][j] = Comp(w,h);
			h = Next(h);
		} 
		w = Next(w);
	}

	return G;
}

void PrintGroup(permutation** G, int n) {
	int fact_n = _fact(n); 
	int i, j;

	printf("     | ");
	for(i = 0; i < fact_n; i++) {
		printf("%3d | ",i+1);
	}
		
	printf("\n");
	for(i = 0; i < fact_n*6 + 6; i++) {
		printf("-");
	}

	printf("\n");
	for(i = 0; i < fact_n; i++){
		printf("%3d  | ",i+1);

		for(j = 0;j < fact_n; j++){
			printf("%3d | ",G[i][j].num);
		}
		printf("\n");

	}
}







