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

HuffmanTree* new_tree(int length, char* text)
{
	HuffmanNode* leafNodes[256];
	for (int i = 0; i < 256; i++) {
		leafNodes[i] = NULL;
	}

	for (int j = 0; j < length; j++) {
		char c = text[j];
		if (leafNodes[c] == NULL) {
			leafNodes[c] = new_node();
			vector_insert(leafNodes[c]->letters, c);
		}
		leafNodes[c]->count += 1;
	}

	PriorityQueue* queue = new_queue();
	for (int k = 0; k < 256; k++) {
		if (leafNodes[k] != NULL) {
			enqueue(queue, leafNodes[k]->count, leafNodes[k]);
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

int encode(HuffmanTree* tree, int length, char* text, char* resultPtr)
{
	int byteOffset = 0;
	char bitOffset = 0;
	resultPtr[0] = 0;

	for (int i = 0; i < length; i++) {
		if (bitOffset >= 8) {
			resultPtr[++byteOffset] = 0;
			bitOffset = 0;
		}

		char c = text[i];
		HuffmanNode* node = tree->root;
		while (vector_contains(node->letters, c)) {
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
