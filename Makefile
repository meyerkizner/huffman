cc = clang
objects = char_vector.o priority_queue.o huffman_tree.o

huffman: huffman.c huffman_tree.h $(objects)
	$(cc) -o huffman huffman.c $(objects)

char_vector.o: char_vector.c char_vector.h
	$(cc) -funsigned-char -c char_vector.c

priority_queue.o: priority_queue.c priority_queue.h
	$(cc) -c priority_queue.c

huffman_tree.o: huffman_tree.c huffman_tree.h char_vector.h priority_queue.h
	$(cc) -funsigned-char -c huffman_tree.c

.PHONY: clean
clean:
	rm huffman $(objects)
