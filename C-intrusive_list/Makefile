all: obj obj/main.o obj/clist.o lab_04
obj:
	mkdir -p obj/
obj/main.o: src/main.c
	gcc -c -Wall -Wextra -Werror src/main.c -o obj/main.o -I include
obj/clist.o: src/clist.c
	gcc -c -Wall -Wextra -Werror src/clist.c -o obj/clist.o -I include
lab_04: obj/main.o obj/clist.o
	gcc obj/main.o obj/clist.o -o lab_04
clean:
	rm -rf obj/ lab_04

