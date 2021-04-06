all: obj obj/main.o obj/mergesort.o lab_03
obj:
	mkdir -p obj/
obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o -I include
obj/mergesort.o: src/mergesort.c include/mergesort.h
	gcc -c src/mergesort.c -o obj/mergesort.o -I include
lab_03: obj/main.o obj/mergesort.o
	gcc obj/main.o obj/mergesort.o -o lab_03
clean:
	rm -r obj/ lab_03

