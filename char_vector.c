#include <stdlib.h>
#include "char_vector.h"

struct CharVector {
	char* contents;
};

CharVector* new_vector(void)
{
	CharVector* vector = (CharVector*) malloc(sizeof(CharVector));
	vector->contents = (char*) malloc(32);
	for (int i = 0; i < 32; i++) {
		vector->contents[i] = 0;
	}
	return vector;
}

void free_vector(CharVector* vector)
{
	free(vector->contents);
	free(vector);
}

void vector_insert(CharVector* vector, char c)
{
	char byteOffset = c / 8;
	char bitOffset = c % 8;
	vector->contents[byteOffset] |= (1 << bitOffset);
}

void vector_insert_all(CharVector* target, CharVector* origin)
{
	for (int i = 0; i < 32; i++) {
		target->contents[i] |= origin->contents[i];
	}
}

void vector_remove(CharVector* vector, char c)
{
	char byteOffset = c / 8;
	char bitOffset = c % 8;
	vector->contents[byteOffset] &= ~(1 << bitOffset);
}

int vector_contains(CharVector* vector, char c)
{
	char byteOffset = c / 8;
	char bitOffset = c % 8;
	char result = vector->contents[byteOffset] & (1 << bitOffset);
	return (result != 0);
}

