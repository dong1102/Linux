all  : main
main:main.o add.o max.o
	gcc -o main main.o add.o max.o
main.o:main.c
	gcc -c main.c
add.o:add.c
	gcc -c add.c
max.o:max.c
	gcc -c max.c
clean:
	rm -rf  *.o main

