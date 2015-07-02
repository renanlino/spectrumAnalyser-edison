#include <unistd.h>
#include <stdio.h>
#include "mraa.h"
#include "mraa/aio.h"
#include "fftVector.h"
#include "terminalPrint.h"

#define STD_N 256 // Number of samples (+samples, +resolution, -frames per second)
#define STD_DELTA 0.001 // Min amplitude to show (-delta, + noise)
#define STD_ADCPIN 0 // Arduino Analog Pin
#define STD_YMAX 0.1 // Max Amplitude in Y Axis. Use 0.1~0.2 for music, ~0.5 for single frequency signals
#define STD_LINES 30.0 // Number of lines in Y Axis ----- USE FLOAT VALUE------
#define BENCH_FLAG 0 // 1 for benchmark test, 0 to regular run


float resolution = 2048.0; //Edison's Analog Resolution

int main(int argc, char **argv) {
	
	int k, N = STD_N, adcNumber = STD_ADCPIN, bench = BENCH_FLAG;
	float yMax = STD_YMAX, lines = STD_LINES, DELTA = STD_DELTA;
	mraa_aio_context adc;

	struct timeval inicio, fim;
	double tmili;

	if (argc == 2) {
		yMax = atof(argv[1]);
	}
	else if (argc == 3) {
		yMax = atof(argv[1]);
		lines = atof(argv[2]);
	}

	adc = mraa_aio_init(adcNumber);
	if (adc == NULL) return 1;

	hideCursor();
	clear();

	while (1) {
		cplx samples[N];
		double deltaFreq;

		gettimeofday(&inicio, NULL);
		for (k = 0; k < N; k++) {
			uint16_t sample = mraa_aio_read(adc);
			samples[k] = (cplx) 5*sample/(resolution - 1.0);
		}
		gettimeofday(&fim, NULL);

		tmili = (double) (1000 *(fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1000);
		deltaFreq = 1000.0 / tmili;

		if (bench == 1) {
			printf("\n>>>> Bench with:\n     N=%d\n     delta=%f\n", N, DELTA);
			printf(">>>> Sample time : %.2fms\n", tmili);
			printf("     deltaFreq   : %.2fHz\n", deltaFreq);
			printf("     max freq.   : %.2fHz\n", 500*N/tmili);
		}
		runFFT(samples, N, DELTA, deltaFreq, bench, yMax, lines);
		printCoord (N/2, 40);
	}

	mraa_aio_close(adc);
	return 0;
}
