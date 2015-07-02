#include "fftVector.h"
#include "terminalPrint.h"

void _fft (cplx input[], cplx output[], int N, int step){
	/*Cooley-Tukey's Algorithm, available in:
	 * http://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
	 * */
    int k;

    if (step < N) {
        _fft(output, input, N, step * 2);
        _fft(output + step, input + step, N, step * 2);

        for (k = 0; k < N; k += 2 * step) {
            cplx t = cexp(-I * PI * k / N) * output[k + step];
			input[k / 2]     = output[k] + t;
			input[(k + N)/2] = output[k] - t;
        }
    }
}

void fft(cplx buf[], int N) {
    int k;
	cplx out[N];
	for (k = 0; k < N; k++) out[k] = buf[k];

	_fft(buf, out, N, 1);
}

void norm (cplx vec[], float amps[], int N, float DELTA, double deltaFreq) {
	/* vec[]: vector of dimension N with FFT result
	 * amps[]: amplitudes vector, each element related to your respective frequency
	 * N: dimension of vec[] and amps[]
	 * DELTA: as defined in fft.c
	 * deltaFreq: frequency resolution
	 * showNorm -> return a vector with amplitude of each frequency obtained with FFT
	 * */
    int k;
    float t;
    for (k = 0; k < N; k++) {
    	t = sqrt( pow(creal(vec[k]), 2) + pow( cimag(vec[k]), 2 ))/N; /*Modulus of a complex number*/
        if (t > DELTA) {
        	amps[k] = t;
        } else {
        	amps[k] = 0;
        }
    }
}

int runFFT (cplx inputData[], int N, float DELTA, double deltaFreq, int bench, float yMax, float lines) {
	/* inputData[]: samples vector with dimension N
	 * N: number of samples
	 * DELTA: as defined in fft.c
	 * deltaFreq: frequency resolution
	 *
	 * runFFT() -> control of FFT
	 * */
	struct timeval inicio, fim;
	double tmili;
	float amps[N/2];

	if (bench == 1) {
		gettimeofday(&inicio, NULL);
	}
	
    fft(inputData, N); /*FFT call*/

    if (bench == 1) {
    	gettimeofday(&fim, NULL);
		tmili = (double) (1000 *(fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1000);
		printf(">>>> FFT time :   %.2f\n", tmili);
    }
    
	
	if (bench == 1) gettimeofday(&inicio, NULL);
    norm(inputData, amps, N/2, DELTA, deltaFreq);
    if (bench == 1) {
    	gettimeofday(&fim, NULL);
		tmili = (double) (1000 *(fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1000);
		printf(">>>> Norm. time : %.2f\n", tmili);
    }

    gettimeofday(&inicio, NULL);
    printFreq(lines, yMax, amps, N/2);
    gettimeofday(&fim, NULL);
    tmili = (double) (1000 *(fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1000);

    return 0;
}
