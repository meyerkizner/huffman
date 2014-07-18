#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree.h"

int main(int argc, char** argv)
{
	const int FREQ_LENGTH = 256 * sizeof(int);

	if (argc != 3) {
		printf("Usage: %s input_file output_file\n", argv[0]);
		return 1;
	}

	FILE* in_file = fopen(argv[1], "rb");
	fseek(in_file, 0L, SEEK_END);
	int in_length = ftell(in_file) - FREQ_LENGTH;
	rewind(in_file);

	if (in_length < 0) {
		printf("Invalid input file\n");
		fclose(in_file);
		return 1;
	}

	int* frequencies = (int*) malloc(FREQ_LENGTH);
	fread(frequencies, sizeof(int), 256, in_file);
	char* input = (char*) malloc(in_length);
	fread(input, 1, in_length, in_file);
	fclose(in_file);

	HuffmanTree* tree = new_tree(frequencies);
	char* output = (char*) malloc(8 * in_length); // maximum theoretical compression factor
	int out_length = decode(tree, in_length, input, output);
	free_tree(tree);

	FILE* out_file = fopen(argv[2], "wb");
	fwrite(output, 1, out_length, out_file);
	fclose(out_file);

	free(input);
	free(frequencies);
	free(output);

	return 0;
}
