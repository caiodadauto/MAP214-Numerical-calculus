#include <stdio.h>
#define MAX 100

void resolucao_uper (double matriz[][MAX], int n, double *solucao) {
	int
		i,
		j;

	for (i = 0; i < n; ++ i)
		solucao[i] = matriz[i][n];
	for (i = n - 1; i >= 0; -- i) {
		for (j = n - 1; j >= i; -- j) {
			if (i != j)
				solucao[i] -= matriz[i][j] * solucao[j];
			else
				solucao[i] /= matriz[i][j];
		}
	}
}

void eliminacao (double matriz[][MAX], int n, int ep) {
	int
		i,
		j;
	double
		elimina,
		pivo;

	pivo = matriz[ep][ep];
	for (i = ep + 1; i < n; ++ i) {
		elimina = matriz[i][ep];
		for (j = ep; j <= n; ++ j)
			matriz[i][j] = matriz[i][j] - 
			(matriz[ep][j] * elimina / pivo);
	}
}

void imprime (FILE *entrada, double matriz[][MAX], int n) {
	int
		i,
		j;

	for (i = 0; i < n; ++ i) {
		for (j = 0; j <= n; ++ j) {
			if (j == n)
				fprintf (entrada, "%.5f\\\\\n", matriz[i][j]);
			else
				fprintf (entrada, "%.5f\t&\t", matriz[i][j]);
		}
	}
	fprintf (entrada, "\n");
}

void pivotamento (int etapa, double matriz[][MAX], int n) {
	double
		aux [MAX],
		max;
	int
		i,
		j,
		linha;

	max = matriz[etapa][etapa];
	linha = etapa;
	for (i = etapa + 1; i < n; ++ i) {
		if (max < matriz[i][etapa]) {
			max = matriz[i][etapa];
			linha  = i;
		}
	}
	for (j = 0; (j <= n) && (linha != etapa); ++ j) {
		aux[j] = matriz[etapa][j];
		matriz[etapa][j] = matriz[linha][j];
		matriz[linha][j] = aux[j];
	}
}


int main () {
	int
		etapa,
		i,
		j,
		n;
	double
		solucao[MAX],
		matriz [MAX][MAX];
	FILE
		*arquivo;

	arquivo = fopen ("saida.tex", "w");
	printf ("Entre com o número n de equacoes do \
	sistema (n < 100): ");
	scanf ("%d", &n);
	for (i = 0; i < n; ++ i) {
		for (j = 0; j <= n; ++ j) {
			printf ("Entre com o valor a(%d, %d) da matriz \
			expandida do sistema: ", i + 1, j + 1);
			scanf ("%lf", &matriz[i][j]);
		}
	}

	for (etapa = 0; etapa < n - 1; ++ etapa) {
	pivotamento (etapa, matriz, n);
	imprime (arquivo, matriz, n);
	eliminacao (matriz, n, etapa);
	}
	imprime (arquivo, matriz, n);
	resolucao_uper (matriz, n, &solucao[0]);
	for (i = 0; i < n; ++ i)
		fprintf (arquivo, "I_%d = %.5f\n", i + 1, solucao[i]);
	fclose (arquivo);
	return 0;
}
