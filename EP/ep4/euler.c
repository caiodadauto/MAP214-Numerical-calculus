#include<stdio.h>
#include<math.h>
#define  H 0.01

double funcao_z (double y_o, double t, double z_o) {
	return z_o + H * (z_o - y_o + pow(t, 3) - 3 * pow(t, 2) + 6 * t);
}

double funcao_y (double y_o, double z_o) {
	return y_o + H * z_o;
}

int main () {
	int
		i;
/* z = y ' */
	double
		y,
		z,
		z_o = 0,
		y_o = 0,
		t = 0;

	for (i = 0; i < 5/H; ++ i) {
		z = funcao_z (y_o, t, z_o);
		y = y_o + H * z_o;
		y_o = y;
		z_o = z;
		t += H;
	}
	printf ("y = %f\ty ' = %f\n", y_o, z_o);
	return 0;
}
