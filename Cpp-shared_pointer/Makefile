all: obj obj/main.o obj/matrix.o obj/shared_ptr.o lab_08
obj:
	mkdir -p obj/
obj/main.o: src/main.cpp
	g++ -c -Wall -Wextra -Werror src/main.cpp -o obj/main.o -I include
obj/matrix.o: src/matrix.cpp
	g++ -c -Wall -Wextra -Werror src/matrix.cpp -o obj/matrix.o -I include
obj/shared_ptr.o: src/shared_ptr.cpp
	g++ -c -Wall -Wextra -Werror src/shared_ptr.cpp -o obj/shared_ptr.o -I include
lab_08: obj/main.o obj/matrix.o obj/shared_ptr.o
	g++ obj/main.o obj/matrix.o obj/shared_ptr.o -o lab_08
clean:
	rm -rf obj/ lab_08

