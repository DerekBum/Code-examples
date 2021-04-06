all: obj obj/main.o obj/my_vector.o lab_06
obj:
	mkdir -p obj/
obj/main.o: src/main.cpp
	g++ -c -Wall -Wextra -Werror src/main.cpp -o obj/main.o -I include
obj/my_vector.o: src/my_vector.cpp
	g++ -c -Wall -Wextra -Werror src/my_vector.cpp -o obj/my_vector.o -I include
lab_06: obj/main.o obj/my_vector.o
	g++ obj/main.o obj/my_vector.o -o lab_06
clean:
	rm -rf obj/ lab_06

