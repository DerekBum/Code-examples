#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "huffman_test.h"

TEST_CASE("Node Tests") {
    NodeTests::run_all_tests();
}

TEST_CASE("Tree Tests") {
    TreeTests eng;
    eng.tree.read_statistics_from_string("HellO");
    eng.run_all_tests();
}