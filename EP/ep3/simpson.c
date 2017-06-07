#include <stdio.h>
#include <math.h>

float erro (float integral) {
	if (integral - 7 < 0)
		return 7 - integral;
	return integral - 7;
}

void imprime (int p, FILE *saida, float integral) {
	fprintf (saida, "%d & %8.f & %f & %f\\\\\n",
	p, pow (2, p), integral, erro (integral));
	fprintf (saida, "\\midrule\n");
}

float funcao (float a) {
	return 8 - (5 * pow (a, 4));
}

void simpson (int p, float *integral) {
	long
		j;
	float
		soma_par = 0,
		soma_impar = 0,
		n_particao = pow (2, p),
		particao = 1 / pow (2, p);

/* soma_par ou _impar refere-se a particao par ou impar. */
/* O que difere do valor de j, o qual assume valores impares */
/* para particoes pares e valores pares para particoes impares. */
	for (j = 1; j < n_particao; j += 2) {
		soma_par +=  funcao (particao * j);
	}
	soma_par *= 4;
	for (j = 2; j < n_particao - 1; j += 2) {
		soma_impar += funcao (particao * j);
	}
	soma_impar *= 2;
	*integral += soma_par + soma_impar;
	*integral *= (particao / 3);
}

int main () {
	FILE
		*arquivo;
	int
		p;
	float
		integral;

	arquivo = fopen ("simpson.tex", "w");
	for (p = 1; p <= 25; ++ p) {
		integral = funcao( 0 ) + funcao( 1 );
		simpson (p, &integral);
		imprime (p, arquivo, integral);
	}
	fclose (arquivo);
	return 0;
}
