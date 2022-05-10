hello: main.o filehandler.o LTexture.o floatingWords.o game.o timer.o menu.o network.o
	gcc -o hello main.o filehandler.o floatingWords.o LTexture.o game.o timer.o menu.o network.o -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_net
main.o: main.c
	gcc -c main.c -I/opt/homebrew/include/SDL2
filehandler.o: filehandler.c
	gcc -c filehandler.c -I/opt/homebrew/include/SDL2
LTexture.o: LTexture.c
	gcc -c LTexture.c -I/opt/homebrew/include/SDL2
floatingWords.o: floatingWords.c
	gcc -c floatingWords.c -I/opt/homebrew/include/SDL2
game.o: game.c
	gcc -c game.c -I/opt/homebrew/include/SDL2
timer.o: timer.c 
	gcc -c timer.c -I/opt/homebrew/include/SDL2
menu.o: menu.c
	gcc -c menu.c -I/opt/homebrew/include/SDL2
network.o: network.c
	gcc -c network.c -I/opt/homebrew/include/SDL2
clean:
	rm -f *.o hello
    