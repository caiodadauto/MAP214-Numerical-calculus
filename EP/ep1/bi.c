#include <stdio.h>
#include <math.h>
#define EPS 0.0001

void   impime (FILE *saida, double a, double b, double x_m, int k);
double erro_relativo (double a, double b);
double funcao (double x);

double erro_relativo (double a, double b) {
	if (a - b < 0)
		return (b - a) / ((a + b) / 2);
	return (a - b) / ((a + b) / 2);
}

double funcao (double x) {
	return x * x * x - cos (x * x);
}

void imprime (FILE *saida, double a, double b, double x_m, int k) {
	fprintf (saida, "%d & %.4f & %.4f & %.4f & %.4f & %.4f & %.4f\\\\\n",
	k, a, b, x_m, funcao (a), funcao (b), funcao(x_m));
	fprintf (saida, "\\midrule\n");
}

int main () {
	int
		k = 1;
	FILE
		*arquivo;
	double
		x_m,
		a = 0,
		b = 1.26;

	arquivo = fopen ("bi.tex", "w");
	while ( erro_absoluto (a, b) > EPS) {
		x_m = (a + b) / 2;
		imprime (arquivo, a, b, x_m, k);
		if (funcao (x_m) * funcao (a) > 0)
			a = x_m;
		else
			b = x_m;
		++ k;
	}
	fprintf (arquivo, "\\multicolumn{7}{c}{\\n{Raiz}}\\\\\n");
	fprintf (arquivo, "\\multicolumn{7}{c}{%.4f}\\\\\n", x_m);
	fclose (arquivo);
	return 0;
}
