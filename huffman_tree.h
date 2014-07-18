#pragma once

typedef struct HuffmanTree HuffmanTree;

int* generate_frequencies(int length, char* input);

HuffmanTree* new_tree(int* frequencies);

void free_tree(HuffmanTree* tree);

void dump_tree(HuffmanTree* tree);

int encode(HuffmanTree* tree, int length, char* input, char* resultPtr);

void decode(HuffmanTree* tree, int in_length, char* input, int out_length, char* resultPtr);
