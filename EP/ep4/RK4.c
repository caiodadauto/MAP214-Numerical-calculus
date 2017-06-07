#include<stdio.h>
#include<math.h>
#define  H 0.01

double funcao (double y, double t, double z) {
	return z - y + pow(t, 3) - 3 * pow(t, 2) + 6 * t;
}

int main () {
/* z = y ' */
	int
		i;
	double
		k_1z,
		k_2z,
		k_3z,
		k_4z,
		k_1y,
		k_2y,
		k_3y,
		k_4y,
		z = 0,
		y = 0,
		t = 0;

	for (i = 0; i < 5/H; ++ i) {
		k_1y = H * z;
		k_1z = H * funcao (y, t, z);
		k_2y = H * (z + k_1z / 2);
		k_2z = H * funcao (y + k_1y / 2, t + H / 2, z + k_1z / 2);
		k_3y = H * (z + k_2z / 2);
		k_3z = H * funcao (y + k_2y / 2, t + H / 2, z + k_2z / 2);
		k_4y = H * (z + k_3z);
		k_4z = H * funcao (y + k_3y, t + H, z + k_3z);
		z = z + (k_1z + 2 * k_2z + 2 * k_3z + k_4z) / 6;
		y = y + (k_1y +2 * k_2y + 2 * k_3y + k_4y) / 6;
		t += H;
	}
	printf ("y = %.15f\ty ' = %.15f\n", y, z);
	return 0;
}
