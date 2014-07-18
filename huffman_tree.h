#pragma once

typedef struct HuffmanTree HuffmanTree;

HuffmanTree* new_tree(int length, char* input);

void free_tree(HuffmanTree* tree);

int encode(HuffmanTree* tree, int length, char* input, char* resultPtr);
