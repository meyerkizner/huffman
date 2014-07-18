#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree.h"

int main(int argc, char** argv)
{
	if (argc != 3) {
		printf("Usage: %s input_file output_file\n", argv[0]);
		return 1;
	}

	FILE* in_file = fopen(argv[1], "rb");
	fseek(in_file, 0L, SEEK_END);
	int in_length = ftell(in_file);
	rewind(in_file);
	char* input = (char*) malloc(in_length); // malloc to avoid blowing the stack
	fread(input, 1, in_length, in_file);
	fclose(in_file);

	HuffmanTree* tree = new_tree(in_length, input);
	char* output = (char*) malloc(in_length);
	int out_length = encode(tree, in_length, input, output);
	free_tree(tree);

	FILE* out_file = fopen(argv[2], "wb");
	fwrite(output, 1, out_length, out_file);
	fclose(out_file);

	free(input);
	free(output);
	
	return 0;
}
