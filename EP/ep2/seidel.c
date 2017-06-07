#include <stdio.h>
# define EPS 1E-4

void imprime (FILE *entrada, double *solucao, double *solucao_k, int k);
void interacao (double matriz[][4], double *solucao, double *solucao_k);
double delta_d (double *solucao, double *solucao_k);
void copia_vetor (double *a, double *b);
double modulo (double a, double b);

void imprime (FILE *entrada, double *solucao, double *solucao_k, int k) {
	int
		i;

	fprintf (entrada, "%d", k);
	for (i = 0; i < 3; ++ i)
		fprintf (entrada, " & %.5f", solucao_k[i]);
	for (i = 0; i < 3; ++ i)
		fprintf (entrada, " & %.5f ", modulo (solucao[i], solucao_k[i]));
	fprintf (entrada, "\\\\\n\\midrule\n");
}

void interacao (double matriz[][4], double *solucao, double *solucao_k) {
	int
		j,
		i;
	double
		aux[3];

	copia_vetor (aux, solucao);
	for (i = 0; i < 3; ++ i) {
		solucao_k[i] = matriz[i][3] / matriz[i][i];
		for (j = 0; j < 3; ++ j) {
			if (i != j)
				solucao_k[i] -= ((aux[j] * matriz[i][j]) / matriz[i][i]);
		}
	aux[i] = solucao_k[i];
	}
}

void copia_vetor (double *a, double *b) {
	int
		i;

	for (i = 0; i < 3; ++ i)
		a[i] = b[i];
}

double modulo (double a, double b) {
	if (a - b < 0)
		return b - a;
	return a - b;
}

double delta_d (double *solucao, double *solucao_k) {
	int
		i;
	double
		max = 0;

	for (i = 0; i < 3; ++ i) {
		if (max < modulo (solucao[i], solucao_k[i]))
			max = modulo (solucao[i], solucao_k[i]);
	}
	return max;
}

int main () {
	FILE
		*arquivo;
	int
		k = 0;
	double
		solucao[3] = {0, 0, 0},
		solucao_k[3] = {1, 1, 1},
		matriz[3][4] = {{12, 0, 2, 15}, {0, 5, -2, 3}, {1, -1, -1, 0}};

	arquivo = fopen ("saida1.tex", "w");
	imprime (arquivo, solucao, solucao_k, k);
	while (delta_d (solucao, solucao_k) >= EPS) {
		copia_vetor (solucao, solucao_k);
		++ k;
		interacao (matriz, solucao, solucao_k);
		imprime (arquivo, solucao, solucao_k, k);
	}
	fclose (arquivo);
	return 0;
}
