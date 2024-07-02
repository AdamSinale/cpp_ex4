#include <vector>
#include <memory>
#include <iostream>

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::ostream;

template <typename T>
class Node {
private:
    T value;
    vector<Node<T>*> children;

public:
    Node(T val) : value(val) {}

    ~Node() {}

    T get_value() const {
        return value;
    }

    vector<Node<T>*>& get_children() {
        return children;
    }

    const vector<Node<T>*>& get_children() const {
        return children;
    }

    void add_child(Node<T>* child) {
        children.push_back(child);
    }

    friend ostream& operator<<(ostream& os, const Node<T>* iterator) {
        return os << iterator->get_value();
    }
};
