

All:
	gcc -c -o main.o main.c -I .
	gcc -c -o hellolinux.o hellolinux.c -I .
	gcc -c -o helloworld.o helloworld.c -I .
Linking1:
	gcc -o test main.o helloworld.o -I .
Linking2:
	gcc -o test main.o hellolinux.o -I .
clean:
	rm -rf *.o test