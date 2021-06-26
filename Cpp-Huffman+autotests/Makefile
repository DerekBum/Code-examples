all: obj obj/main.o obj/huffman.o hw_02
obj/main.o: src/main.cpp
	g++ -c -std=c++17 -Wall -Wextra -Werror src/main.cpp -o obj/main.o -I include
obj/huffman.o: src/huffman.cpp
	g++ -c -std=c++17 -Wall -Wextra -Werror src/huffman.cpp -o obj/huffman.o -I include
hw_02: obj/main.o obj/huffman.o
	g++ obj/main.o obj/huffman.o -o hw_02
test: obj obj/test.o obj/huffman_test.o obj/huffman.o hw_02_test
obj:
	mkdir -p obj/
obj/test.o: test/test.cpp
	g++ -c -std=c++17 -Wall -Wextra -Werror test/test.cpp -o obj/test.o -I include
obj/huffman_test.o: test/huffman_test.cpp
	g++ -c -std=c++17 -Wall -Wextra -Werror test/huffman_test.cpp -o obj/huffman_test.o -I include
hw_02_test: obj/test.o obj/huffman.o obj/huffman_test.o
	g++ obj/test.o obj/huffman.o obj/huffman_test.o -o hw_02_test
clean:
	rm -rf obj/ hw_02 hw_02_test
