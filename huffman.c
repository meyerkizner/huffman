#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "char_vector.h"
#include "priority_queue.h"

typedef struct HuffmanNode {
	CharVector* letters;
	int count;
	struct HuffmanNode* left;
	struct HuffmanNode* right;
} HuffmanNode;

HuffmanNode* new_node(void)
{
	HuffmanNode* node = (HuffmanNode*) malloc(sizeof(HuffmanNode));
	node->letters = new_vector();
	node->count = 0;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void free_node(HuffmanNode* node)
{
	if (node->left != NULL) {
		free_node(node->left);
	}
	if (node->right != NULL) {
		free_node(node->right);
	}
	free_vector(node->letters);
	free(node);
}

HuffmanNode* build(char* text)
{
	int i;
	HuffmanNode* leafNodes[256];
	for (i = 0; i < 256; i++) {
		leafNodes[i] = NULL;
	}
	
	i = 0;
	char c;
	while ((c = text[i++]) != '\0') {
		if (leafNodes[c] == NULL) {
			leafNodes[c] = new_node();
			vector_insert(leafNodes[c]->letters, c);
		}
		leafNodes[c]->count += 1;
	}

	PriorityQueue* queue = new_queue();
	for (int j = 0; j < 256; j++) {
		if (leafNodes[j] != NULL) {
			enqueue(queue, leafNodes[j]->count, leafNodes[j]);
		}
	}
	while (queue_length(queue) > 1) {
		HuffmanNode* node1 = (HuffmanNode*) dequeue(queue);
		HuffmanNode* node2 = (HuffmanNode*) dequeue(queue);
		HuffmanNode* parent = new_node();
		parent->letters = vector_union(node1->letters, node2->letters);
		parent->count = node1->count + node2->count;
		parent->left = node1;
		parent->right = node2;
		enqueue(queue, parent->count, parent);
	}
	HuffmanNode* result = dequeue(queue);
	free_queue(queue);
	return result;
}

char* encode(HuffmanNode* tree, char* text)
{
	int size = strlen(text);
	char* result = (char*) malloc(size + 1);
	int byteOffset = 0;
	char bitOffset = 0;
	result[0] = 0;

	int i = 0;
	char c;
	while ((c = text[i++]) != '\0') {
		HuffmanNode* node = tree;
		while (vector_contains(node->letters, c)) {
			if (node->left != NULL && vector_contains(node->left->letters, c)) {
				bitOffset += 1;
				node = node->left;
			} else if (node->right != NULL && vector_contains(node->right->letters, c)) {
				result[byteOffset] |= (1 << (7 - bitOffset));
				bitOffset += 1;
				node = node->right;
			} else {
				break;
			}
			
			if (bitOffset >= 8) {
				result[++byteOffset] = 0;
				bitOffset = 0;
			}
		}
	}
	result[++byteOffset] = 0;
	return result;
}

int main(int argc, char** argv)
{
	char text[10000];
	int i = 0;
	int c;
	while ((c = getchar()) != EOF) {
		text[i++] = c;
	}
	text[i] = '\0';

	HuffmanNode* tree = build(text);
	char* result = encode(tree, text);
	free_node(tree);

	int j = 0;
	while ((c = result[j]) != '\0') {
		putc(result[j++], stdout);
	}
	
	free(result);
	return 0;
}

