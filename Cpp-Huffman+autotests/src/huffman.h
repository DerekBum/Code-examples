#pragma once

#include <iostream>
#include <cmath>
#include <fstream>
#include <queue>
#include <map>
#include <set>

namespace HuffmanTree {
    struct HuffNode {
    public:
        explicit HuffNode(unsigned char symbol);
        explicit HuffNode(int freq);
        HuffNode(unsigned char symbol, int freq);
        HuffNode() = default;
        ~HuffNode();

        void create_left_son(HuffNode* to_left);
        void create_right_son(HuffNode* to_right);
        void used();

        HuffNode* get_left() const;
        HuffNode* get_right() const;
        bool terminal() const;
        unsigned char get_symbol() const;
        int get_frequency() const;
    private:
        unsigned char symbol_ = 0;
        int frequency_ = 0;
        bool is_terminal = true;
        HuffNode *left_ = nullptr, *right_ = nullptr;
    };

    struct compare {
        bool operator()(HuffNode* left, HuffNode* right) {
            return (left->get_frequency() > right->get_frequency());
        }
    };

    struct HuffTree {
    public:
        HuffTree();
        ~HuffTree();

        void do_huffman_coding(std::ifstream& in, std::ofstream& out);
        void do_huffman_decoding(std::ifstream& in, std::ofstream& out);

    private:
#ifdef MY_TESTS
    public:
#endif

        const int8_t max_buffer_size = 8;
        const int32_t powers_of_two[8] = {1, 2, 4, 8, 16, 32, 64, 128};

        HuffNode *root_;
        std::set <std::pair<int32_t, unsigned char>> statistics_;
        std::map <unsigned char, std::string> codes_;

        int input_size = 0, coded_size = 0, extra_size = 0;

        const std::set <std::pair<int32_t, unsigned char>>& get_statistics() const;
        HuffNode* get_root() const;
        const std::map <unsigned char, std::string>& get_all_codes() const;

        void fill_codes();

        void print_coded(std::ifstream& in, std::ofstream& out);

        void print_decoded(std::ifstream& in, std::ofstream& out);

        void print_size_after_code() const;
        void print_size_after_decode() const;

        void read_statistics_from_string(const std::string& source);
        std::string print_decoded_as_string(const std::string& coded_string) const;

        void decode_tree(std::ifstream& in);
        void get_code(HuffNode* node, std::string& code);
        void read_statistics(std::ifstream& in);
        void fill_statistics();
        void print_statistics(std::ofstream& out);

        void create_tree(std::ifstream& in, bool is_read);
        void get_bin_code(std::ifstream& in, std::string& bin_code);
    };
}
