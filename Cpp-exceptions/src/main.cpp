#include "matrix.h"

const std::size_t register_size = 10;

std::size_t cin_register() {
    std::string reg_number;
    std::cin >> reg_number;
    return reg_number[1] - '0';
}

int main() {
    Matrix* matrix_register = new Matrix [register_size];
    std::string type;
    std::cin >> type;
    while (type != "exit") {
        try {
            if (type == "load") {
                std::string file_name;
                std::size_t index = cin_register();
                std::cin >> file_name;
                matrix_register[index].load(file_name);
            } else if (type == "print") {
                std::size_t index = cin_register();
                matrix_register[index].print();
            } else if (type == "add") {
                std::size_t index_first = cin_register(), index_second = cin_register();
                matrix_register[index_first].add(matrix_register[index_second]);
            } else if (type == "mul") {
                std::size_t index_first = cin_register(), index_second = cin_register();
                matrix_register[index_first].mul(matrix_register[index_second]);
            } else if (type == "elem") {
                std::size_t index = cin_register(), r, c;
                std::cin >> r >> c;
                matrix_register[index].elem(r, c);
            }
        } catch (MatrixException &ex) {
            std::cout << ex.what() << std::endl;
        } catch (std::bad_alloc &e) {
            std::cout << "Unable to allocate memory." << std::endl;
        }
        std::cin >> type;
    }
    delete [] matrix_register;
    return 0;
}
