// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.cpp"
#include "complex.hpp"

// Helper function to create a simple tree for testing
template<typename T>
Tree<T> createSampleTree() {
    Tree<T> tree;
    auto root = new Node<T>(1);
    tree.add_root(root);
    auto child1 = new Node<T>(2);
    auto child2 = new Node<T>(3);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    auto child3 = new Node<T>(4);
    auto child4 = new Node<T>(5);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);
    return tree;
}

TEST_CASE("Test Tree with double") {
    Tree<double> tree = createSampleTree<double>();

    CHECK(tree.getRoot()->get_value() == 1);

    // Test PreOrderIterator
    vector<double> var = {1,2,4,5,3};
    size_t i = 0;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        CHECK((*node)->get_value() == var[i]);
        i++;
    }

    // Test InOrderIterator
    auto in_it = tree.begin_in_order();
    CHECK((*in_it)->get_value() == 4);
    ++in_it;
    CHECK((*in_it)->get_value() == 2);
    ++in_it;
    CHECK((*in_it)->get_value() == 5);
    ++in_it;
    CHECK((*in_it)->get_value() == 1);
    ++in_it;
    CHECK((*in_it)->get_value() == 3);

    // Test PostOrderIterator
    auto post_it = tree.begin_post_order();
    CHECK((*post_it)->get_value() == 4);
    ++post_it;
    CHECK((*post_it)->get_value() == 5);
    ++post_it;
    CHECK((*post_it)->get_value() == 2);
    ++post_it;
    CHECK((*post_it)->get_value() == 3);
    ++post_it;
    CHECK((*post_it)->get_value() == 1);

    // Test BFSIterator
    auto bfs_it = tree.begin_bfs_scan();
    CHECK((*bfs_it)->get_value() == 1);
    ++bfs_it;
    CHECK((*bfs_it)->get_value() == 2);
    ++bfs_it;
    CHECK((*bfs_it)->get_value() == 3);
    ++bfs_it;
    CHECK((*bfs_it)->get_value() == 4);
    ++bfs_it;
    CHECK((*bfs_it)->get_value() == 5);

    // Test DFSIterator
    auto dfs_it = tree.begin_dfs_scan();
    CHECK((*dfs_it)->get_value() == 4);
    ++dfs_it;
    CHECK((*dfs_it)->get_value() == 5);
    ++dfs_it;
    CHECK((*dfs_it)->get_value() == 2);
    ++dfs_it;
    CHECK((*dfs_it)->get_value() == 3);
    ++dfs_it;
    CHECK((*dfs_it)->get_value() == 1);
}

TEST_CASE("Test Tree with Complex") {
    Tree<Complex> tree;
    auto root = new Node<Complex>(Complex(1, 1));
    tree.add_root(root);
    auto child1 = new Node<Complex>(Complex(2, 2));
    auto child2 = new Node<Complex>(Complex(3, 3));
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    auto child3 = new Node<Complex>(Complex(4, 4));
    auto child4 = new Node<Complex>(Complex(5, 5));
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);

    CHECK(tree.getRoot()->get_value().getReal() == 1);

    // Test PreOrderIterator
    auto it = tree.begin_pre_order();
    CHECK((*it)->get_value().getReal() == 1);
    ++it;
    CHECK((*it)->get_value().getReal() == 2);
    ++it;
    CHECK((*it)->get_value().getReal() == 4);
    ++it;
    CHECK((*it)->get_value().getReal() == 5);
    ++it;
    CHECK((*it)->get_value().getReal() == 3);

    // Test InOrderIterator
    auto in_it = tree.begin_in_order();
    CHECK((*in_it)->get_value().getReal() == 4);
    ++in_it;
    CHECK((*in_it)->get_value().getReal() == 2);
    ++in_it;
    CHECK((*in_it)->get_value().getReal() == 5);
    ++in_it;
    CHECK((*in_it)->get_value().getReal() == 1);
    ++in_it;
    CHECK((*in_it)->get_value().getReal() == 3);

    // Test PostOrderIterator
    auto post_it = tree.begin_post_order();
    CHECK((*post_it)->get_value().getReal() == 4);
    ++post_it;
    CHECK((*post_it)->get_value().getReal() == 5);
    ++post_it;
    CHECK((*post_it)->get_value().getReal() == 2);
    ++post_it;
    CHECK((*post_it)->get_value().getReal() == 3);
    ++post_it;
    CHECK((*post_it)->get_value().getReal() == 1);

    // Test BFSIterator
    auto bfs_it = tree.begin_bfs_scan();
    CHECK((*bfs_it)->get_value().getReal() == 1);
    ++bfs_it;
    CHECK((*bfs_it)->get_value().getReal() == 2);
    ++bfs_it;
    CHECK((*bfs_it)->get_value().getReal() == 3);
    ++bfs_it;
    CHECK((*bfs_it)->get_value().getReal() == 4);
    ++bfs_it;
    CHECK((*bfs_it)->get_value().getReal() == 5);

    // Test DFSIterator
    auto dfs_it = tree.begin_dfs_scan();
    CHECK((*dfs_it)->get_value().getReal() == 4);
    ++dfs_it;
    CHECK((*dfs_it)->get_value().getReal() == 5);
    ++dfs_it;
    CHECK((*dfs_it)->get_value().getReal() == 2);
    ++dfs_it;
    CHECK((*dfs_it)->get_value().getReal() == 3);
    ++dfs_it;
    CHECK((*dfs_it)->get_value().getReal() == 1);
}
