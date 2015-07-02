#include <stdio.h>
#include <sys/time.h>

#define ESC 0x1B

void clear();
void setCursor(int lin, int col);
void printFreq(float lines, float maxY, float amps[], int N);
void hideCursor();
void printCoord (int N, float deltaF);
