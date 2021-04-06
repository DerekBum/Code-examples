all: obj obj/str.o obj/test.o obj/test_str.o lab_02
obj:
	mkdir -p obj/
obj/str.o: src/str.c include/str.h
	gcc -c src/str.c -o obj/str.o -I include
obj/test.o: src/test.c
	gcc -c src/test.c -o obj/test.o -I include
obj/test_str.o: src/test_str.c include/test_str.h
	gcc -c src/test_str.c -o obj/test_str.o -I include
lab_02: obj/str.o obj/test.o obj/test_str.o
	gcc obj/str.o obj/test.o obj/test_str.o -o lab_02
clean:
	rm -r obj/ lab_02

