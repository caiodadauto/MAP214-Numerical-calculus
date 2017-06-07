#include<stdio.h>
#include<math.h>
#define  H 6.283185E-3

double funcao (double x, double t, double v, double f) {
	return (x / 2) * (1 - pow(x, 2)) - (0.25 * v) + f * cos( t );
}

void runge_kuta (double *x, double *t, double *v, double *f) {
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
	k_1v = H * funcao (*x, *t, *v, *f);
	k_2x = H * (*v + k_1v / 2);
	k_2v = H * funcao (*x + k_1x / 2, *t + H / 2, *v + k_1v / 2, *f);
	k_3x = H * (*v + k_2v / 2);
	k_3v = H * funcao (*x + k_2x / 2, *t + H / 2, *v + k_2v / 2, *f);
	k_4x = H * (*v + k_3v);
	k_4v = H * funcao (*x + k_3x, *t + H, *v + k_3v, *f);
	*v = *v + (k_1v +2 * k_2v + 2 * k_3v + k_4v) / 6;
	*x = *x + (k_1x +2 * k_2x + 2 * k_3x + k_4x) / 6;
	*t += H;
}

int main () {
	int
		k,
		j,
		i;
	FILE
		*arquivo;
/* v = x ' */
	double
		f  = 0,
		x = -1,
		v = 1,
		t = 0;

	arquivo = fopen ("graf_birf.txt", "w");
	for (k = 0; k <= 1400; ++ k) {
		for (j = 0; j < 200000; ++ j) {
			runge_kuta (&x, &t, &v, &f);
		}
		for (i = 0; i < 100; ++ i) {
			for (j = 0; j < 1000; ++ j) {
				runge_kuta (&x, &t, &v, &f);
			}
			fprintf (arquivo, "%f\t%f\n", f, x);
			printf ("%d\n", k);
		}
		f += 0.0005;
		x = -1;
		v = 1;
		t = 0;
	}
	fclose (arquivo);
	return 0;
}
