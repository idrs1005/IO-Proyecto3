ventana: Principal.c
	gcc -g -c Principal.c `pkg-config --cflags gtk+-3.0 cairo` -lm -I.
	gcc -g Principal.o -o Principal `pkg-config --libs gtk+-3.0 cairo` -lm -I.