#pragma once

typedef struct HuffmanTree HuffmanTree;

int* generate_frequencies(int length, char* input);

HuffmanTree* new_tree(int* frequencies);

void free_tree(HuffmanTree* tree);

int encode(HuffmanTree* tree, int length, char* input, char* resultPtr);

int decode(HuffmanTree* tree, int length, char* input, char* resultPtr);
