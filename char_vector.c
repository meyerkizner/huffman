#include <stdlib.h>
#include "char_vector.h"

struct CharVector {
	char* contents;
};

CharVector* new_vector(void)
{
	CharVector* vector = (CharVector*) malloc(sizeof(CharVector));
	vector->contents = (char*) malloc(32);
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

CharVector* vector_union(CharVector* v1, CharVector* v2)
{
	CharVector* v_union = new_vector();
	for (int i = 0; i < 32; i++) {
		v_union->contents[i] = v1->contents[i] | v2->contents[i];
	}
	return v_union;
}

