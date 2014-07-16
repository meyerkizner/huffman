#pragma once

typedef struct PriorityQueue PriorityQueue;

PriorityQueue* new_queue(void);

void free_queue(PriorityQueue* queue);

int queue_length(PriorityQueue* queue);

void enqueue(PriorityQueue* queue, int key, void* data);

void* dequeue(PriorityQueue* queue);

