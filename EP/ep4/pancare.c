#include<stdio.h>
#include<math.h>
#define  H 6.283185E-3

double funcao (double x, double t, double v) {
	return (x / 2) * (1 - pow(x, 2)) - (0.25 * v) + 0.27 * cos( t );
}

void runge_kuta (double *x, double *t, double *v) {
	double
		k_1v,
		k_2v,
		k_3v,
		k_4v,
		k_1x,
		k_2x,
		k_3x,
		k_4x;

	k_1x = H * *v;
	k_1v = H * funcao (*x, *t, *v);
	k_2x = H * (*v + k_1v / 2);
	k_2v = H * funcao (*x + k_1x / 2, *t + H / 2, *v + k_1v / 2);
	k_3x = H * (*v + k_2v / 2);
	k_3v = H * funcao (*x + k_2x / 2, *t + H / 2, *v + k_2v / 2);
	k_4x = H * (*v + k_3v);
	k_4v = H * funcao (*x + k_3x, *t + H, *v + k_3v);
	*v = *v + (k_1v +2 * k_2v + 2 * k_3v + k_4v) / 6;
	*x = *x + (k_1x +2 * k_2x + 2 * k_3x + k_4x) / 6;
	*t += H;
}

int main () {
	int
		j,
		i;
	FILE
		*arquivo;
/* v = x ' */
	double
		x = -1,
		v = 1,
		t = 0;

	arquivo = fopen ("graf_pan.txt", "w");
	for (j = 0; j < 200000; ++ j) {
		runge_kuta (&x, &t, &v);
	}
	for (i = 0; i < 20000; ++ i) {
		for (j = 0; j < 1000; ++ j) {
			runge_kuta (&x, &t, &v);
		}
		fprintf (arquivo, "%f\t%f\n", x, v);
		printf ("%d\n", i);
	}
	fclose (arquivo);
	return 0;
}
