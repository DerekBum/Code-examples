all: obj obj/main.o obj/Scheme.o obj/Figure.o obj/Rectangle.o obj/Circle.o lab_09
obj:
	mkdir -p obj/
obj/main.o: src/main.cpp
	g++ -c -Wall -Wextra -Werror src/main.cpp -o obj/main.o -I include
obj/Scheme.o: src/Scheme.cpp
	g++ -c -Wall -Wextra -Werror src/Scheme.cpp -o obj/Scheme.o -I include
obj/Figure.o: src/Figure.cpp
	g++ -c -Wall -Wextra -Werror src/Figure.cpp -o obj/Figure.o -I include
obj/Rectangle.o: src/Rectangle.cpp
	g++ -c -Wall -Wextra -Werror src/Rectangle.cpp -o obj/Rectangle.o -I include
obj/Circle.o: src/Circle.cpp
	g++ -c -Wall -Wextra -Werror src/Circle.cpp -o obj/Circle.o -I include
lab_09: obj/main.o obj/Scheme.o obj/Figure.o obj/Rectangle.o obj/Circle.o
	g++ obj/main.o obj/Scheme.o obj/Figure.o obj/Rectangle.o obj/Circle.o -o lab_09
clean:
	rm -rf obj/ lab_09

