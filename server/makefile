server: server.o
	gcc -o server server.o -L/opt/homebrew/lib -lSDL2_net
server.o: server.c
	gcc -c server.c -I/opt/homebrew/include 
clean:
	rm -f *.o server
