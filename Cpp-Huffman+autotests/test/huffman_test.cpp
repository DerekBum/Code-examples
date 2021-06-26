#include "huffman_test.h"

void NodeTests::run_all_tests() {
    test_constructor();
    test_set_get_terminal();
    test_set_get_son();
}

void NodeTests::test_constructor() {
    SUBCASE("Default constructor") {
        HuffmanTree::HuffNode node;
        CHECK(node.get_right() == nullptr);
        CHECK(node.get_left() == nullptr);
        CHECK(node.terminal());
        CHECK(node.get_frequency() == 0);
        CHECK(node.get_symbol() == 0);
    }

    SUBCASE("Symbol constructor") {
        unsigned char symbol = 't';
        HuffmanTree::HuffNode node(symbol);
        CHECK(node.get_right() == nullptr);
        CHECK(node.get_left() == nullptr);
        CHECK(node.terminal());
        CHECK(node.get_frequency() == 0);
        CHECK(node.get_symbol() == symbol);
    }

    SUBCASE("Frequency constructor") {
        HuffmanTree::HuffNode node(123);
        CHECK(node.get_right() == nullptr);
        CHECK(node.get_left() == nullptr);
        CHECK(node.terminal());
        CHECK(node.get_frequency() == 123);
        CHECK(node.get_symbol() == 0);
    }

    SUBCASE("Symbol and frequency constructor") {
        unsigned char symbol = 't';
        HuffmanTree::HuffNode node(symbol, 123);
        CHECK(node.get_right() == nullptr);
        CHECK(node.get_left() == nullptr);
        CHECK(node.terminal());
        CHECK(node.get_frequency() == 123);
        CHECK(node.get_symbol() == symbol);
    }
}

void NodeTests::test_set_get_terminal() {
    HuffmanTree::HuffNode node;
    CHECK(node.terminal());
    node.used();
    CHECK(!node.terminal());
}

void NodeTests::test_set_get_son() {
    SUBCASE("Left son") {
        HuffmanTree::HuffNode node, to_left('L', 123);
        node.create_left_son(&to_left);
        CHECK(!node.terminal());
        CHECK(node.get_right() == nullptr);
        CHECK(node.get_left()->get_symbol() == 'L');
        CHECK(node.get_left()->get_frequency() == 123);
        CHECK(node.get_left()->get_left() == nullptr);
        CHECK(node.get_left()->get_right() == nullptr);
        CHECK(node.get_left()->terminal());
        node.create_left_son(nullptr);
    }
    SUBCASE("Right son") {
        HuffmanTree::HuffNode node, to_right('R', 321);
        node.create_right_son(&to_right);
        CHECK(!node.terminal());
        CHECK(node.get_left() == nullptr);
        CHECK(node.get_right()->get_symbol() == 'R');
        CHECK(node.get_right()->get_frequency() == 321);
        CHECK(node.get_right()->get_left() == nullptr);
        CHECK(node.get_right()->get_right() == nullptr);
        CHECK(node.get_right()->terminal());
        node.create_right_son(nullptr);
    }
}

void TreeTests::run_all_tests() {
    test_statistics();
    test_fill_statistics();
    test_build_tree();
    test_fill_codes();
    test_before_and_after();
}

void TreeTests::test_statistics() const {
    auto result = tree.get_statistics();
    auto it = result.begin();
    CHECK(it->first == 1);
    CHECK(it->second == 'H');
    it++;
    CHECK(it->first == 1);
    CHECK(it->second == 'O');
    it++;
    CHECK(it->first == 1);
    CHECK(it->second == 'e');
    it++;
    CHECK(it->first == 2);
    CHECK(it->second == 'l');
    it++;
    CHECK(it == result.end());
}

void TreeTests::test_fill_statistics() {
    tree.fill_statistics();
    auto result = tree.get_statistics();
    auto it = result.begin();
    CHECK(it->first == 1);
    CHECK(it->second == 'H');
    it++;
    CHECK(it->first == 1);
    CHECK(it->second == 'O');
    it++;
    CHECK(it->first == 1);
    CHECK(it->second == 'e');
    it++;
    CHECK(it->first == 2);
    CHECK(it->second == 'l');
    it++;
    CHECK(it == result.end());
}

void TreeTests::test_build_tree() const {
    auto current_node = tree.get_root();
    CHECK(!current_node->terminal());
    CHECK(current_node->get_frequency() == 5);
    auto left_node = current_node->get_left();
    CHECK(!left_node->terminal());
    CHECK(left_node->get_frequency() == 2);
    CHECK(left_node->get_left()->terminal());
    CHECK(left_node->get_left()->get_frequency() == 1);
    CHECK(left_node->get_left()->get_symbol() == 'H');
    CHECK(left_node->get_left()->get_left() == nullptr);
    CHECK(left_node->get_left()->get_right() == nullptr);
    CHECK(left_node->get_right()->terminal());
    CHECK(left_node->get_right()->get_frequency() == 1);
    CHECK(left_node->get_right()->get_symbol() == 'e');
    CHECK(left_node->get_right()->get_left() == nullptr);
    CHECK(left_node->get_right()->get_right() == nullptr);
    current_node = current_node->get_right();
    CHECK(!current_node->terminal());
    CHECK(current_node->get_frequency() == 3);
    CHECK(current_node->get_left()->terminal());
    CHECK(current_node->get_left()->get_frequency() == 1);
    CHECK(current_node->get_left()->get_symbol() == 'O');
    CHECK(current_node->get_left()->get_left() == nullptr);
    CHECK(current_node->get_left()->get_right() == nullptr);
    CHECK(current_node->get_right()->terminal());
    CHECK(current_node->get_right()->get_frequency() == 2);
    CHECK(current_node->get_right()->get_symbol() == 'l');
    CHECK(current_node->get_right()->get_left() == nullptr);
    CHECK(current_node->get_right()->get_right() == nullptr);
}

void TreeTests::test_fill_codes() {
    tree.fill_codes();
    auto codes = tree.get_all_codes();
    auto it = codes.begin();
    CHECK(it->first == 'H');
    CHECK(it->second == "00");
    it++;
    CHECK(it->first == 'O');
    CHECK(it->second == "10");
    it++;
    CHECK(it->first == 'e');
    CHECK(it->second == "01");
    it++;
    CHECK(it->first == 'l');
    CHECK(it->second == "11");
    it++;
    CHECK(it == codes.end());
}

void TreeTests::test_before_and_after() const {
    std::string result = tree.print_decoded_as_string("0001111110");
    CHECK(result == "HellO");
}