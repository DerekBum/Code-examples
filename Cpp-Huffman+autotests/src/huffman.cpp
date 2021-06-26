#include "huffman.h"

using namespace HuffmanTree;

HuffNode::HuffNode(unsigned char symbol) : symbol_(symbol) {}

HuffNode::HuffNode(unsigned char symbol, int freq) : symbol_(symbol), frequency_(freq) {}

HuffNode::HuffNode(int freq) : frequency_(freq) {}

HuffTree::HuffTree() : root_(new HuffNode) {}

HuffNode::~HuffNode() {
    delete left_;
    delete right_;
}

void HuffNode::create_left_son(HuffNode* to_left) {
    used();
    left_ = to_left;
}

void HuffNode::create_right_son(HuffNode* to_right) {
    used();
    right_ = to_right;
}

void HuffNode::used() {
    is_terminal = false;
}

HuffNode * HuffNode::get_left() const {
    return left_;
}

HuffNode * HuffNode::get_right() const {
    return right_;
}

bool HuffNode::terminal() const {
    return is_terminal;
}

unsigned char HuffNode::get_symbol() const {
    return symbol_;
}

int HuffNode::get_frequency() const {
    return frequency_;
}

HuffTree::~HuffTree() {
    delete root_;
}

void HuffTree::do_huffman_coding(std::ifstream &in, std::ofstream &out) {
    create_tree(in, false);
    fill_codes();

    in.clear();
    in.seekg(0, std::ios::beg);

    print_coded(in, out);
    print_size_after_code();
}

void HuffTree::do_huffman_decoding(std::ifstream &in, std::ofstream &out) {
    decode_tree(in);
    fill_codes();

    print_decoded(in, out);
    print_size_after_decode();
}

void HuffTree::create_tree(std::ifstream& in, bool is_read) {
    if (!is_read)
        read_statistics(in);
    if (statistics_.empty())
        return;
    fill_statistics();
}

void HuffTree::decode_tree(std::ifstream &in) {
    in.read((char*)&input_size, sizeof(int32_t));
    int32_t stat_size;
    in.read((char*)&stat_size, sizeof(int32_t));
    extra_size += 2 * sizeof(int32_t);
    while (stat_size--) {
        int32_t freq;
        unsigned char symbol;
        in.read((char*)&freq, sizeof(int32_t));
        extra_size += sizeof(int32_t);
        in.read((char*)&symbol, sizeof(unsigned char));
        extra_size++;
        statistics_.insert({freq, symbol});
    }
    create_tree(in, true);
}

void HuffTree::read_statistics(std::ifstream& in) {
    unsigned char current_symbol;
    std::map <unsigned char, int32_t> unordered_statistics;
    while (in.read((char*)&current_symbol, sizeof(unsigned char))) {
        unordered_statistics[current_symbol]++;
        input_size++;
    }
    for (const auto& elem : unordered_statistics)
        statistics_.insert({elem.second, elem.first});
}

void HuffTree::fill_statistics() {
    std::priority_queue <HuffNode*, std::vector <HuffNode*>, compare> empty_nodes;
    for (const auto& elem : statistics_)
        empty_nodes.push(new HuffNode(elem.second, elem.first));
    if (empty_nodes.size() == 1)
        empty_nodes.push(new HuffNode(input_size + 1));
    while (empty_nodes.size() != 1) {
        HuffNode* left = empty_nodes.top();
        empty_nodes.pop();
        HuffNode* right = empty_nodes.top();
        empty_nodes.pop();
        auto* parent = new HuffNode(left->get_frequency() + right->get_frequency());
        parent->create_left_son(left);
        parent->create_right_son(right);
        empty_nodes.push(parent);
    }
    delete root_;
    root_ = empty_nodes.top();
}

void HuffTree::fill_codes() {
    std::string current_code;
    get_code(root_, current_code);
}

void HuffTree::get_code(HuffNode *node, std::string &code) {
    if (node->terminal()) {
        codes_[node->get_symbol()] = code;
        return;
    }
    code += "0";
    get_code(node->get_left(), code);
    code.pop_back();
    code += "1";
    get_code(node->get_right(), code);
    code.pop_back();
}

void HuffTree::print_coded(std::ifstream& in, std::ofstream &out) {
    print_statistics(out);
    unsigned char current_symbol;
    uint8_t buffer = 0, buffer_size = 0;
    while (in.read((char*)&current_symbol, sizeof(char)))
        for (auto symbol : codes_[current_symbol]) {
            if (buffer_size == max_buffer_size) {
                coded_size++;
                out << buffer;
                buffer = 0;
                buffer_size = 0;
            }
            buffer += (symbol - '0') * powers_of_two[max_buffer_size - buffer_size - 1];
            buffer_size++;
        }
    if (buffer_size != 0) {
        coded_size++;
        out << buffer;
    }
}

void HuffTree::print_decoded(std::ifstream &in, std::ofstream &out) {
    std::string bin_code;
    get_bin_code(in, bin_code);
    auto head = root_;
    int number_of_symbols = input_size;
    for (auto symbol : bin_code) {
        if (symbol == '0')
            head = head->get_left();
        else
            head = head->get_right();
        if (head->terminal()) {
            out << head->get_symbol();
            head = root_;
            number_of_symbols--;
        }
        if (number_of_symbols == 0)
            break;
    }
}

void HuffTree::get_bin_code(std::ifstream &in, std::string &bin_code) {
    unsigned char current_code;
    while (in.read((char*)&current_code, sizeof(char))) {
        coded_size++;
        for (int8_t i = max_buffer_size - 1; i >= 0; i--) {
            int current_pow = powers_of_two[i];
            if (current_code >= current_pow) {
                bin_code += "1";
                current_code -= current_pow;
            } else
                bin_code += "0";
        }
    }
}

void HuffTree::print_statistics(std::ofstream &out) {
    out.write((const char*) &input_size, sizeof(int32_t));
    int32_t different_symbols = statistics_.size();
    out.write((const char*) &different_symbols, sizeof(int32_t));
    extra_size += 2 * sizeof(int32_t);
    for (const auto& elem : statistics_) {
        out.write((const char *) &elem.first, sizeof(int32_t));
        out << elem.second;
        extra_size += sizeof(int32_t) + 1;
    }
}

void HuffTree::print_size_after_code() const {
    std::cout << input_size << std::endl << coded_size << std::endl << extra_size;
}

void HuffTree::print_size_after_decode() const {
    std::cout << coded_size << std::endl << input_size << std::endl << extra_size;
}

const std::set <std::pair<int32_t, unsigned char>> & HuffTree::get_statistics() const {
    return statistics_;
}

HuffNode * HuffTree::get_root() const {
    return root_;
}

const std::map<unsigned char, std::string> & HuffTree::get_all_codes() const {
    return codes_;
}

void HuffTree::read_statistics_from_string(const std::string& source) {   // used only for testing
    std::map <unsigned char, int32_t> unordered_statistics;
    for (auto current_symbol : source) {
        unordered_statistics[current_symbol]++;
        input_size++;
    }
    for (const auto& elem : unordered_statistics)
        statistics_.insert({elem.second, elem.first});
}

std::string HuffTree::print_decoded_as_string(const std::string& coded_string) const {   // used only for testing
    std::string result;
    auto head = root_;
    for (auto symbol : coded_string) {
        if (symbol == '0')
            head = head->get_left();
        else
            head = head->get_right();
        if (head->terminal()) {
            result += head->get_symbol();
            head = root_;
        }
    }
    return result;
}
