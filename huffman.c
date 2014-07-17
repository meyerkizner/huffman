#include <stdio.h>
#include <string.h>
#include "huffman_tree.h"

int main(int argc, char** argv)
{
	char text[10000];
	int i = 0;
	int c;
	while ((c = getchar()) != EOF) {
		text[i++] = c;
	}
	text[i] = '\0';

	HuffmanTree* tree = new_tree(text);
	char result[strlen(text) + 1];
	int length = encode(tree, text, result);
	free_tree(tree);

	for (int j = 0; j < length; j++) {
		putc(result[j], stdout);
	}
	
	return 0;
}
