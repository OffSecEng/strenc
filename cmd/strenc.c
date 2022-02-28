#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

// Local includes
#include "strenc.h"

// Open file and return point to char containing file contents
unsigned char *openFile(char *fileName) {
	size_t c = 0;
	size_t size = 8;
	unsigned char *buf = malloc(size);

	FILE *fp;
	fp = fopen(fileName, "r");

	for (size_t i = 0; (c = fgetc(fp)) != EOF; i++) {
		if (i == size) { // If size of current buffer need to be doubled
			size *= 2;
			buf = reallocarray(buf, size, sizeof(unsigned char));
			if (buf == NULL) {
				printf("Error resizing array, exiting...\n");
				exit(EXIT_FAILURE);
			}
		}
		buf[i] = c;
	}

	fclose(fp);
	return buf;
}

unsigned char *genKey(unsigned char *pt) {
	unsigned char *key = malloc(strlen((char *)pt));
	srand(time(NULL));

	// rand() should not normally be used for
	// generating secure numbers, we do not care
	// here
	for (int i = 0; i < strlen((char *)pt); i++) {
		key[i] = rand();
	}

	return key;
}

unsigned char *xorCharArray(unsigned char *text, unsigned char *key) {
	unsigned char *ft = malloc(strlen((char *)text));

	for (int i = 0; i < strlen((char *)text); i++) { // Xor pt & key
		ft[i] = text[i] ^ key[i];
	}

	return ft;
}

int printCStyleCharArray(unsigned char *text, unsigned char *key) {
	// Print text
	printf("unsigned char text[%zu] = { ", strlen((char *)text));
	for (int i = 0; i < strlen((char *)text); i++) {
		printf("0x%02X", text[i]);
		if ((i + 1) == strlen((char *)text)) {
			printf(" ");
		} else {
			printf(", ");
		}
	}
	printf("};\n");
	// Print key
	printf("unsigned char text_key[%zu] = { ", strlen((char *)key));
	for (int i = 0; i < strlen((char *)key); i++) {
		printf("0x%02X", key[i]);
		if ((i + 1) == strlen((char *)key)) {
			printf(" ");
		} else {
			printf(", ");
		}
	}
	printf("};\n");
	return 0;
}

int main(int argc, char **argv) {
	unsigned char *pt = malloc(sizeof(unsigned char));
	unsigned char *key = malloc(sizeof(unsigned char));
	unsigned char *ct = malloc(sizeof(unsigned char));

	// Setting up options
	static const struct option long_options[] = {
		{"help", no_argument, NULL, 'h'},
		{"file", required_argument, NULL, 'f'},
		{"string", required_argument, NULL, 's'},
		{0, 0, 0, 0}
	};

	const char* usage =
		"Usage strenc [options]\n\n"
		"  -h --help\t\t\tShows this message\n"
		"  -f --file\t\t\tInput file to be xored\n"
		"  -s --string\t\t\tInput string to be xored\n"
		"\n";

	int c; // Used to grab individual args
	while(1) {
		int option_index = 0;
		c = getopt_long(argc, argv, "hf:s:", long_options, &option_index);
		if (c == -1) { // Break if no more args are present
			break;
		}
		switch(c) {
			case 'h':
				printf("%s", usage);
				exit(EXIT_SUCCESS);
			case 'f':
				if (strlen((char *)pt) != 0) { // Exit if string is already set
					printf("Error string input already set\n");
					exit(EXIT_FAILURE);
				}
				pt = openFile(optarg);
				break;
			case 's':
				if (strlen((char *)pt) != 0) { // Exit if file is already set
					printf("Error file input already set\n");
					exit(EXIT_FAILURE);
				}
				pt = malloc(strlen(optarg));
				strcpy((char *)pt, optarg);
				break;
		}
	}
	if (strlen((char *)pt) == 0) { // Exit if plain text is not > len 0
		printf("Plain text has not been set\n");
		exit(EXIT_FAILURE);
	}

	key = genKey(pt);
	ct = xorCharArray(pt, key);

	printCStyleCharArray(ct, key);

	// Freeing memory and returning
	free(pt);
	free(key);
	free(ct);
	exit(EXIT_SUCCESS);
}

