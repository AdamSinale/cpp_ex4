#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::make_shared;

template <typename T>
class Node {
private:
    T value;
    vector<Node<T>*> children;

public:
    Node(T val) : value(val) {}

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
};
