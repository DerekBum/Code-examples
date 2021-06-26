#pragma once

#define MY_TESTS

#include "doctest.h"
#include "../src/huffman.h"

class NodeTests {
public:
    static void run_all_tests();
private:
    static void test_constructor();
    static void test_set_get_terminal();
    static void test_set_get_son();
};

class TreeTests {
public:
    void run_all_tests();
    HuffmanTree::HuffTree tree;

private:
    void test_statistics() const;
    void test_fill_statistics();
    void test_build_tree() const;
    void test_fill_codes();
    void test_before_and_after() const;
};