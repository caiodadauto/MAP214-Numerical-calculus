#include <stdio.h>
#include <math.h>
#define EPS 0.0001

void   imprime (FILE *saida, double a, int k);
double erro_relativo (double a, double b);
double derivada (double x);
double funcao (double x);
double phi (double x);


double erro_relativo (double a, double b) {
	if (a - b < 0)
		return (b - a) / b;
	return (a - b) / b;
}

double phi (double x) {
	return x - (x * x * x - cos (x * x)) /
	(3 *x * x + 2 *x * sin (x * x));
}

double derivada (double x) {
	return 3 *x * x + 2 *x * sin (x * x);
}

double funcao (double x) {
	return x * x * x - cos (x * x);
}

void imprime (FILE *saida, double a, int k) {
	fprintf (saida, "%d & %.4f & %.4f & %.4f\\\\\n",
	k, a, funcao (a), derivada (a));
	fprintf (saida, "\\midrule\n");
}

int main () {
	FILE
		*arquivo;
	int
		k = 1;
	double
		x = 1,
		x_1;

	arquivo = fopen ("new.tex", "w");
	x_1 = phi (x);
	while (erro_relativo(x_1, x) > EPS) {
		imprime (arquivo, x_1, k);
		x = x_1;
		x_1 = phi (x);
		++ k;
	}
	fprintf (arquivo, "\\multicolumn{4}{c}{\\n{Raiz}}\\\\\n");
	fprintf (arquivo, "\\toprule[0.11em]\n");
	fprintf (arquivo, "\\multicolumn{4}{c}{%.4f}\\\\\n", x_1);
	fclose (arquivo);
	return 0;
}
