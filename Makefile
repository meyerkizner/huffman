objects = char_vector.o priority_queue.o

huffman: huffman.c char_vector.h priority_queue.h $(objects)
	clang -o huffman huffman.c $(objects)

char_vector.o: char_vector.c char_vector.h
	clang -funsigned-char -c char_vector.c

priority_queue.o: priority_queue.c priority_queue.h
	clang -c priority_queue.c

.PHONY: clean
clean:
	rm huffman $(objects)

