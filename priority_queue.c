#include <stdlib.h>
#include "priority_queue.h"

typedef struct HeapNode {
	int key;
	void* data;
} HeapNode;

struct PriorityQueue {
	HeapNode** heap;
	int length;
	int arraySize;
};

PriorityQueue* new_queue(void)
{
	PriorityQueue* queue = (PriorityQueue*) malloc(sizeof(PriorityQueue));
	queue->heap = (HeapNode**) malloc(2 * sizeof(HeapNode*));
	queue->length = 0;
	queue->arraySize = 2;
	return queue;
}

void free_queue(PriorityQueue* queue)
{
	for (int i = 0; i < queue->length; i++) {
		free(queue->heap[i]);
	}
	free(queue->heap);
	free(queue);
}

int queue_length(PriorityQueue* queue)
{
	return queue->length;
}

void enqueue(PriorityQueue* queue, int key, void* data)
{
	if (queue->length == queue->arraySize) {
		// dynamically resize the heap array
		HeapNode** newHeap = (HeapNode**) malloc(2 * queue->arraySize * sizeof(HeapNode*));
		for (int i = 0; i < queue->length; i++) {
			newHeap[i] = queue->heap[i];
		}
		free(queue->heap);
		queue->heap = newHeap;
		queue->arraySize *= 2;
	}

	HeapNode* node = (HeapNode*) malloc(sizeof(HeapNode));
	node->key = key;
	node->data = data;

	int nodeIndex = queue->length;
	queue->heap[nodeIndex] = node;
	while (nodeIndex > 0) {
		int parentIndex = (nodeIndex - 1) / 2;
		HeapNode* parent = queue->heap[parentIndex];
		if (parent->key > node->key) {
			queue->heap[parentIndex] = node;
			queue->heap[nodeIndex] = parent;
			nodeIndex = parentIndex;
		} else {
			break;
		}
	}
	queue->length += 1;
}

void* dequeue(PriorityQueue* queue)
{
	void* result = queue->heap[0]->data;
	free(queue->heap[0]);

	HeapNode* node = queue->heap[--queue->length];
	queue->heap[0] = node;

	int nodeIndex = 0;
	while (nodeIndex < queue->length) {
		int leftIndex = 2 * nodeIndex + 1;
		int rightIndex = 2 * nodeIndex + 2;
		HeapNode* left = queue->heap[leftIndex];
		HeapNode* right = queue->heap[rightIndex];
		if (leftIndex < queue->length && left->key < right->key && left->key < node->key) {
			queue->heap[leftIndex] = node;
			queue->heap[nodeIndex] = left;
			nodeIndex = leftIndex;
		} else if (rightIndex < queue->length && right->key < node->key) {
			queue->heap[rightIndex] = node;
			queue->heap[nodeIndex] = right;
			nodeIndex = rightIndex;
		} else {
			break;
		}
	}

	if ((4 * queue->length) <= queue->arraySize && queue->arraySize > 2) {
		// dynamically resize the heap array
		HeapNode** newHeap = (HeapNode**) malloc((queue->arraySize / 2) * sizeof(HeapNode*));
		for (int i = 0; i < queue->length; i++) {
			newHeap[i] = queue->heap[i];
		}
		free(queue->heap);
		queue->heap = newHeap;
		queue->arraySize /= 2;
	}

	return result;
}

