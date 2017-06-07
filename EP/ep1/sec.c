#include <stdio.h>
#include <math.h>
#define EPS 0.0001

void   impime (FILE *saida, double a, double b, double x_m, int k);
double erro_relativo (double a, double b);
double funcao (double x);

double erro_relativo (double a, double b) {
	if (a - b < 0)
		return (b - a) / a;
	return (a - b) / a;
}

double phi (double x_1, double x_2) {
	return x_2 - ((funcao (x_2) * (x_2 - x_1)) /
	(funcao (x_2) - funcao (x_1)));
}

double funcao (double x) {
	return -14.4 / (x * x) + (1.38E3 / 0.328) * exp ((-1 * x) / 0.328);
}

void imprime (FILE *saida, double a, int k) {
	fprintf (saida, "%d & %.4f & %.4f\\\\\n",
	k, a, funcao (a));
	fprintf (saida, "\\midrule\n");
}

int main () {
	int
		k = 1;
	FILE
		*arquivo;
	double
		x_1 = 2,
		x_2 = 3,
		x;

	arquivo = fopen ("sec.tex", "w");
	while (erro_relativo (x_1, x_2) > EPS) {
		x = phi (x_1, x_2);
		x_2 = x_1;
		x_1 = x;
		imprime (arquivo, x, k);
		++k;
	}

	fprintf (arquivo, "\\multicolumn{3}{c}{\\n{Raiz (r_{eq})}}\\\\\n");
	fprintf (arquivo, "\\multicolumn{3}{c}{%.4f}\\\\\n", x);
	fclose (arquivo);
	return 0;
}
