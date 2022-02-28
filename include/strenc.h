#include <stdio.h>
#include <stdint.h>

unsigned char *openFile(char *fileName);
unsigned char *genKey(unsigned char *pt);
unsigned char *xorCharArray(unsigned char *text, unsigned char *key);
int printCStyleCharArray(unsigned char *text, unsigned char *key);
int main(int argc, char **argv);

