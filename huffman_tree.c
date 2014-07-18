#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree.h"
#include "char_vector.h"
#include "priority_queue.h"

typedef struct HuffmanNode {
	CharVector* letters;
	int count;
	struct HuffmanNode* left;
	struct HuffmanNode* right;
} HuffmanNode;

struct HuffmanTree {
	HuffmanNode* root;
};

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

int dump_node(HuffmanNode* node, int* nextId)
{
	int nodeId = *nextId;
	*nextId += 1;
	printf("%d [label=\"", nodeId);
	for (int i = 0; i < 256; i++) {
		if (vector_contains(node->letters, i)) {
			if (i == '\"') {
				putc('\\', stdout);
			}
			putc(i, stdout);
		}
	}
	printf("\"]\n");
	if (node->left != NULL) {
		int leftId = dump_node(node->left, nextId);
		printf("%d -- %d\n", nodeId, leftId);
	}
	if (node->right != NULL) {
		int rightId = dump_node(node->right, nextId);
		printf("%d -- %d\n", nodeId, rightId);
	}
	return nodeId;
}

int* generate_frequencies(int length, char* input)
{
	int* frequencies = (int*) malloc(256 * sizeof(int));
	for (int i = 0; i < 256; i++) {
		frequencies[i] = 0;
	}

	for (int j = 0; j < length; j++) {
		char c = input[j];
		frequencies[c] += 1;
	}

	return frequencies;
}

HuffmanTree* new_tree(int* frequencies)
{
	PriorityQueue* queue = new_queue();
	for (int i = 0; i < 256; i++) {
		if (frequencies[i] > 0) {
			HuffmanNode* node = new_node();
			vector_insert(node->letters, i);
			node->count = frequencies[i];
			enqueue(queue, node->count, node);
		}
	}
	while (queue_length(queue) > 1) {
		HuffmanNode* node1 = (HuffmanNode*) dequeue(queue);
		HuffmanNode* node2 = (HuffmanNode*) dequeue(queue);
		HuffmanNode* parent = new_node();
		vector_insert_all(parent->letters, node1->letters);
		vector_insert_all(parent->letters, node2->letters);
		parent->count = node1->count + node2->count;
		parent->left = node1;
		parent->right = node2;
		enqueue(queue, parent->count, parent);
	}
	HuffmanNode* root = dequeue(queue);
	free_queue(queue);

	HuffmanTree* tree = (HuffmanTree*) malloc(sizeof(HuffmanTree));
	tree->root = root;
	return tree;
}

void free_tree(HuffmanTree* tree)
{
	free_node(tree->root);
	free(tree);
}

void dump_tree(HuffmanTree* tree)
{
	printf("graph tree {\n");
	int id = 0;
	dump_node(tree->root, &id);
	printf("}\n");
}

int encode(HuffmanTree* tree, int length, char* input, char* resultPtr)
{
	int byteOffset = 0;
	char bitOffset = 0;
	resultPtr[0] = 0;

	for (int i = 0; i < length; i++) {
		char c = input[i];
		HuffmanNode* node = tree->root;
		while (vector_contains(node->letters, c)) {
			if (bitOffset >= 8) {
				resultPtr[++byteOffset] = 0;
				bitOffset = 0;
			}

			if (node->left != NULL && vector_contains(node->left->letters, c)) {
				bitOffset += 1;
				node = node->left;
			} else if (node->right != NULL && vector_contains(node->right->letters, c)) {
				resultPtr[byteOffset] |= (1 << (7 - bitOffset));
				bitOffset += 1;
				node = node->right;
			} else {
				break;
			}
		}
	}
	return byteOffset + 1;
}

void decode(HuffmanTree* tree, int in_length, char* input, int out_length, char* resultPtr)
{
	int byteOffset = 0;
	char bitOffset = 8;
	int outOffset = 0;
	char byte;
	HuffmanNode* node = tree->root;
	while (outOffset < out_length) {
		if (bitOffset >= 8) {
			byte = input[byteOffset++];
			bitOffset = 0;
		}
		while ((node->left != NULL || node->right != NULL) && bitOffset < 8) {
			if (byte & (1 << (7 - bitOffset))) {
				node = node->right;
			} else {
				node = node->left;
			}
			bitOffset += 1;
		}
		if (bitOffset < 8) {
			int i;
			for (i = 0; i < 256; i++) {
				if (vector_contains(node->letters, i)) {
					break;
				}
			}
			resultPtr[outOffset++] = i;
			node = tree->root;
		}
	}
}
