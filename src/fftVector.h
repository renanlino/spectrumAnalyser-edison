#include <math.h>
#include <complex.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

typedef double complex cplx;

#define PI 3.14159265359

void _fft (cplx input[], cplx output[], int N, int step);
void fft(cplx buf[], int N);
void norm (cplx vec[], float amps[], int N, float DELTA, double deltaFreq);
int runFFT (cplx inputData[], int N, float DELTA, double deltaFreq, int bench, float yMax, float lines);
