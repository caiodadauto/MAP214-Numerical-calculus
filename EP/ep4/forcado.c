#include<stdio.h>
#include<math.h>
#define  H 0.05

double funcao (double x, double t, double v) {
	return (x / 2) * (1 - pow(x, 2)) - (0.25 * v) + 0.6 * cos( t );
}

int main () {
	int
		i;
	FILE
		*arquivo;
/* v = x ' */
	double
		k_1v,
		k_2v,
		k_3v,
		k_4v,
		k_1x,
		k_2x,
		k_3x,
		k_4x,
		x = -1,
		v = 1,
		t = 0;

	arquivo = fopen ("graf_for.txt", "w");
	for (i = 0; i < 420/H; ++ i) {
		k_1x = H * v;
		k_1v = H * funcao (x, t, v);
		k_2x = H * (v + k_1v / 2);
		k_2v = H * funcao (x + k_1x / 2, t + H / 2, v + k_1v / 2);
		k_3x = H * (v + k_2v / 2);
		k_3v = H * funcao (x + k_2x / 2, t + H / 2, v + k_2v / 2);
		k_4x = H * (v + k_3v);
		k_4v = H * funcao (x + k_3x, t + H, v + k_3v);
		if (i > 7000)
			fprintf (arquivo, "%f\t%f\n", x, v);
		v = v + (k_1v +2 * k_2v + 2 * k_3v + k_4v) / 6;
		x = x + (k_1x +2 * k_2x + 2 * k_3x + k_4x) / 6;
		t += H;
	}
	fclose (arquivo);
	return 0;
}
