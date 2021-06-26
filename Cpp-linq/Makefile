all: obj obj/main.o lab_14
obj:
	mkdir -p obj/
obj/main.o: src/main.cpp
	g++ -c -std=c++17 -Wall -Wextra -Werror src/main.cpp -o obj/main.o -I include
lab_14: obj/main.o
	g++ obj/main.o -o lab_14
clean:
	rm -rf obj/ lab_14

