CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
OBJ = src/main.o src/banco.o src/conta.o src/io.o src/lista.o src/cliente.o src/quicksort.o

banco: $(OBJ)
	$(CC) $(CFLAGS) -o banco $(OBJ)

src/main.o: src/main.c src/banco.h src/cliente.h src/io.h
src/banco.o: src/banco.c src/banco.h src/lista.h src/cliente.h src/io.h src/conta.h src/quicksort.h
src/conta.o: src/conta.c src/conta.h src/lista.h src/cliente.h
src/io.o: src/io.c src/io.h src/lista.h src/cliente.h
src/lista.o: src/lista.c src/lista.h src/cliente.h
src/cliente.o: src/cliente.c src/cliente.h
src/quicksort.o: src/quicksort.c src/quicksort.h src/cliente.h

clean:
	rm -f $(OBJ) banco
