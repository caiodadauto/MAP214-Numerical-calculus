#include <stdio.h>
#include <math.h>
#define PI 3.14159265
#define G 9.80665
#define MAX 100000

void imprime (float theta, FILE *saida, float periodo) {
    fprintf (saida, "%f\t%f \n", theta, periodo);
}

float funcao (float rad, float theta) {
    return 1 / (sqrt (1 - pow (sin (theta), 2) * pow (sin (rad), 2)));
}

float trapezio (float theta) {
    int
        i;
    float
        integral,
        soma = 0,
        particao = PI / (2 * MAX);

    integral = funcao (0, theta) + funcao (PI / 2, theta); 
    for (i = 1; i < MAX; ++ i) {
        soma += funcao (particao * i, theta);
    }
    integral += 2 * soma;
    integral *= particao / 2;
    return integral;
}

int main () {
    FILE
        *arquivo;
    float
        theta,
        periodo;

    arquivo = fopen ("grafico.tex", "w");
    for (theta = 0; theta < PI; theta += PI / 200) {
        periodo = trapezio (theta) * 4 * sqrt (1 / G);
        imprime (theta, arquivo, periodo);
    }
    fclose (arquivo);
    return 0;
}
