
all: main.c src/menu.c src/backtracking.c src/dados.c src/gerador.c
	gcc main.c -o EXEC src/menu.c src/backtracking.c src/dados.c src/gerador.c

run: EXEC
	./EXEC

clear: EXEC
	rm EXEC