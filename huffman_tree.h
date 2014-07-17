#pragma once

typedef struct HuffmanTree HuffmanTree;

HuffmanTree* new_tree(char* text);

void free_tree(HuffmanTree* tree);

int encode(HuffmanTree* tree, char* text, char* resultPtr);
