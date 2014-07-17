#pragma once

typedef struct CharVector CharVector;

CharVector* new_vector(void);

void free_vector(CharVector* vector);

void vector_insert(CharVector* vector, char c);

void vector_insert_all(CharVector* target, CharVector* origin);

void vector_remove(CharVector* vector, char c);

int vector_contains(CharVector* vector, char c);
