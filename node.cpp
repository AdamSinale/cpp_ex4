#pragma once

#include <vector>

template <typename T>
class Node {
private:
    T value;
    std::vector<Node<T>> children;

public:
    Node(T val) : value(val) {}

    T get_value() const {
        return value;
    }

    std::vector<Node<T>>& get_children() {
        return children;
    }

    const std::vector<Node<T>>& get_children() const {
        return children;
    }

    void add_child(const Node<T>& child) {
        children.push_back(child);
    }
};
