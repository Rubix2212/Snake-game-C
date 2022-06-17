snake.exe: obj\snake.o obj\funciones.o
	gcc -o snake obj\snake.o obj\funciones.o

obj\snake.o: src\snake.c src\snake.h
	gcc -c src\snake.c -o obj\snake.o

obj\funciones.o: src\funciones.c src\snake.h
	gcc -c src\funciones.c -o obj\funciones.o

clean:
	del obj\snake.o