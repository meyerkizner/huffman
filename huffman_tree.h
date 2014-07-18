#pragma once

typedef struct HuffmanTree HuffmanTree;

HuffmanTree* new_tree(int length, char* text);

void free_tree(HuffmanTree* tree);

int encode(HuffmanTree* tree, int length, char* text, char* resultPtr);
