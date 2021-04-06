all: obj obj/main.o obj/matrix.o lab_07
obj:
	mkdir -p obj/
obj/main.o: src/main.cpp
	g++ -c -Wall -Wextra -Werror src/main.cpp -o obj/main.o -I include
obj/matrix.o: src/matrix.cpp
	g++ -c -Wall -Wextra -Werror src/matrix.cpp -o obj/matrix.o -I include
lab_07: obj/main.o obj/matrix.o
	g++ obj/main.o obj/matrix.o -o lab_07
clean:
	rm -rf obj/ lab_07

