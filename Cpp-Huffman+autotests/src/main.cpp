#include "huffman.h"

#include <cstring>

void error_message() {
    std::cout << "Error: invalid args.";
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        error_message();
        return 1;
    }

    std::string type, input_file, output_file;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-u") == 0)
            type = argv[i];
        else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            i++;
            input_file = argv[i];
        }
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            i++;
            output_file = argv[i];
        } else {
            error_message();
            return 1;
        }
    }

    if (type.empty()) {
        error_message();
        return 1;
    }

    if (type == "-c") {
        std::ifstream in(input_file);

        if (!in) {
            error_message();
            return 1;
        }

        std::ofstream out(output_file, std::ios::binary);

        if (!out) {
            error_message();
            return 1;
        }

        auto *tree = new HuffmanTree::HuffTree;
        tree->do_huffman_coding(in, out);

        delete tree;
    } else if (type == "-u") {
        std::ifstream in(input_file, std::ios::binary);

        if (!in) {
            error_message();
            return 1;
        }

        std::ofstream out(output_file);

        if (!out) {
            error_message();
            return 1;
        }

        auto *tree = new HuffmanTree::HuffTree;

        tree->do_huffman_decoding(in, out);

        delete tree;
    } else {
        error_message();
        return 1;
    }
    return 0;
}
