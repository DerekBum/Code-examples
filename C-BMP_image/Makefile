all: obj obj/main.o obj/bmp.o obj/stego.o hw_01
obj:
	mkdir -p obj/
obj/main.o: src/main.c
	gcc -c -Wall -Wextra -Werror src/main.c -o obj/main.o -I include
obj/bmp.o: src/bmp.c
	gcc -c -Wall -Wextra -Werror src/bmp.c -o obj/bmp.o -I include
obj/stego.o: src/stego.c
	gcc -c -Wall -Wextra -Werror src/stego.c -o obj/stego.o -I include
hw_01: obj/main.o obj/bmp.o obj/stego.o
	gcc obj/main.o obj/bmp.o obj/stego.o -o hw_01
clean:
	rm -rf obj/ hw_01

