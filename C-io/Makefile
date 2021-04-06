all: obj obj/main.o obj/clist.o obj/point_list.o lab_05
obj:
	mkdir -p obj/
obj/main.o: src/main.c
	gcc -c -Wall -Wextra -Werror src/main.c -o obj/main.o -I include
obj/clist.o: src/clist.c
	gcc -c -Wall -Wextra -Werror src/clist.c -o obj/clist.o -I include
obj/point_list.o: src/point_list.c
	gcc -c -Wall -Wextra -Werror src/point_list.c -o obj/point_list.o -I include
lab_05: obj/main.o obj/clist.o obj/point_list.o
	gcc obj/main.o obj/clist.o obj/point_list.o -o lab_05
clean:
	rm -rf obj/ lab_05

