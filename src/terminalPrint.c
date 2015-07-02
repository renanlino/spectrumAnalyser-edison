#include "terminalPrint.h"
#include <string.h>

struct timeval inicio, fim;
double tmili;

void printFreq(float lines, float maxY, float amps[], int N) {
	/*Draws Amplitude x Frequency graphics in serial session*/
	int i, k, linesInt = lines;
		setCursor(1,1);
		for (i = linesInt; i >= 0; i--) {
			for (k = 0; k < N; k++) {
				if (amps[k] > i*maxY/lines) printf("%s", "#"); //Change the second argument of printf to desired char
				else printf(" ");
			}
			printf("    \n");
		}
}

void clear() {
	/*Clear terminal screen*/
	printf("%c[%dJ", ESC, 2);
}

void setCursor(int lin, int col) {
	/*Moves cursor to defined point*/
	printf("%c[%d;%dH", ESC, lin, col);
}

void hideCursor() {
	/*Stop blinking*/
	printf("%c[?25l", ESC);
}

void printCoord (int N, float deltaF) {
	/*Creates a horizontal axis*/
	int i;
	for (i = 0; i < N; i++) {
		printf("-");
	}
	printf("-->\n");

	for (i = 0; i < N + 1; i = i + 20) {
		printf(".                  ");
	}
	printf("\n");

	for (i = 0; i < N + 1; i = i + 20) {
		printf("%.1f                ", i*deltaF/1000);
	}
	printf("\n");
}
