#include <stdio.h>
#include <stdint.h>

unsigned char *openFile(char *fileName, size_t *len);
unsigned char *genKey(unsigned char *pt, size_t len);
unsigned char *xorCharArray(unsigned char *text, unsigned char *key, size_t len);
int printCStyleCharArray(unsigned char *text, unsigned char *key, size_t len);
int main(int argc, char **argv);

