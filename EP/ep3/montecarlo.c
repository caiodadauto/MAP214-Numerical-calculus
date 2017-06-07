#include <stdio.h>
#include <math.h>
#define M 2147483647
#define A 16807
#define EPS 1E-4

void imprime (FILE *saida, float area[]);
float desv_pad (float area_media, float area[], int N);
float media (float area[], int N);
short sao_iguais (float a, float b);
void aleatorio (unsigned long *aux, float *x, float *y);
short ta_dentro (float a, float b);

void imprime (FILE *saida, float area[]) {
	int
		i;
	float
		area_media,
		desvio;

	for (i = 1; i <= 17; ++i ) {
		area_media = media (area, (int) pow(2, i)),
		desvio = desv_pad (area_media, area, (int) pow(2, i));
		fprintf (saida, "%d & %.5f & %.3f & %.5f\\\\\n", (int)pow(2,i),
		area_media, desvio, desvio/(sqrt ((int)pow(2,i) + 1)));
		fprintf (saida, "\\midrule\n");
	}
}

float desv_pad (float area_media, float area[], int N) {
	int
		i;
	float
		soma = 0;

	for (i = 0; i < N; ++ i)
		soma += pow ((area_media - area[i]), 2);
	return sqrt (soma / (N - 1));
}

float media (float area[], int N) {
	int
		i;
	float
		soma = 0;

	for (i = 0; i < N; ++ i)
		soma += area[i];
	return soma /= N;
}

short sao_iguais (float a, float b) {
	if (a - b <= EPS && b - a <= EPS)
		return 1;
	return 0;
}

short ta_dentro (float a, float b) {
	if (b < a * a * a || sao_iguais (b, a * a * a))
		return 1;
	return 0;
}

void aleatorio (unsigned long *aux, float *x, float *y) {
	*x = (A * *aux) % M;
	*aux = (unsigned long) *x;
	*x /= M;
	*y = (A * *aux) % M;
	*aux = (unsigned long) *y;
	*y /= M;
}

int main () {
	FILE
		*arquivo;
	int
		k,
		j,
		i;
	unsigned long
		aux = 7994808;
	float
		x,
		y,
		area[131072];

	arquivo = fopen ("montecarlo.tex", "w");
	for (j = 0; j < 131072; ++j) {
		k = 0;
		for (i = 0; i < 100; ++i) {
			aleatorio (&aux, &x, &y);
			if (ta_dentro (x, y))
				++k;
		}
		/* A area do quadrado que contem y = x^3 é 1 */
		area[j] = (float) k / 100;
	}
	imprime (arquivo, area);
	fclose (arquivo);
	return 0;
}
