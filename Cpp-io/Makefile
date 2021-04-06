all: obj obj/main.o obj/employees.o lab_10
obj:
	mkdir -p obj/
obj/main.o: src/main.cpp
	g++ -c -std=c++17 -Wall -Wextra -Werror src/main.cpp -o obj/main.o -I include
obj/employees.o: src/employees.cpp
	g++ -c -std=c++17 -Wall -Wextra -Werror src/employees.cpp -o obj/employees.o -I include
lab_10: obj/main.o obj/employees.o
	g++ obj/main.o obj/employees.o -o lab_10
clean:
	rm -rf obj/ lab_10

