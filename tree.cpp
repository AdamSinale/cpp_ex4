#ifndef TREE_HPP
#define TREE_HPP

#include "node.cpp"
#include <queue>
#include <vector>
#include <memory>
#include <algorithm>

using std::queue;
using std::vector;
using std::cout;
using std::endl;

template<typename T, size_t k = 2>
class Tree {
private:
    Node<T>* root;

public:
    Tree() : root(nullptr) {}
    ~Tree() {} 
    
    void add_root(Node<T>* root) { this->root = root; }

    void add_sub_node(Node<T>* parent, Node<T>* child);

    friend ostream& operator<<(ostream& os, const Tree<T, k>& tree) {
        // Implement printing logic here
        return os;
    }

    class TreeIterator {
    protected:
        queue<Node<T>*> node_queue;
        TreeIterator() {}

    public:
        virtual TreeIterator& operator++() {
            node_queue.pop();
            return *this;
        }

        virtual bool operator!=(const TreeIterator& other) const {
            return !node_queue.empty() || !other.node_queue.empty();
        }

        virtual Node<T>* operator*() const {
            return node_queue.front();
        }

        friend ostream& operator<<(ostream& os, const TreeIterator& iterator) {
            return os << *iterator;
        }
    };

    class PreOrderIterator : public TreeIterator {
    public:
        PreOrderIterator(Node<T>* root) : TreeIterator() {
            if (root != nullptr) {
                this->visit(root);
            }
        }
        void visit(Node<T>* root);
    };

    PreOrderIterator begin_pre_order() { return PreOrderIterator(root); }
    PreOrderIterator end_pre_order() { return PreOrderIterator(nullptr); }

    class PostOrderIterator : public TreeIterator {
    public:
        PostOrderIterator(Node<T>* root) : TreeIterator() {
            if (root != nullptr) {
                this->visit(root);
            }
        }
        void visit(Node<T>* root);
    };

    PostOrderIterator begin_post_order() { return PostOrderIterator(root); }
    PostOrderIterator end_post_order() { return PostOrderIterator(nullptr); }

    class InOrderIterator : public TreeIterator {
    public:
        InOrderIterator(Node<T>* root) : TreeIterator() {
            if (root != nullptr) {
                this->visit(root);
            }
        }

        void visit(Node<T>* root);
    };

    InOrderIterator begin_in_order() { return InOrderIterator(root); }
    InOrderIterator end_in_order() { return InOrderIterator(nullptr); }

    class BFSIterator : public TreeIterator {
    public:
        BFSIterator(Node<T>* root) : TreeIterator() {
            if (root != nullptr) {
                this->visit(root);
            }
        }

        void visit(Node<T>* root);
    };

    BFSIterator begin_bfs_scan() { return BFSIterator(root); }
    BFSIterator end_bfs_scan() { return BFSIterator(nullptr); }

    class DFSIterator : public TreeIterator {
    public:
        DFSIterator(Node<T>* root) : TreeIterator() {
            if (root != nullptr) {
                this->visit(root);
            }
        }

        void visit(Node<T>* root);
    };

    DFSIterator begin_dfs_scan() { return DFSIterator(root); }
    DFSIterator end_dfs_scan() { return DFSIterator(nullptr); }

    BFSIterator begin() { return BFSIterator(root); }
    BFSIterator end() { return BFSIterator(nullptr); }

    void myHeap();
};

template<typename T, size_t k>
void Tree<T, k>::add_sub_node(Node<T>* parent, Node<T>* child) {
    for (auto it = this->begin_bfs_scan(); it != this->end_bfs_scan(); ++it) {
        Node<T>* node = *it;
        vector<Node<T>*>& children = node->get_children();
        auto child_it = std::find(children.begin(), children.end(), child);
        if (child_it != children.end()) {
            children.erase(child_it);
            cout << "Had another parent, replaced" << endl;
            break;
        }
    }
    if (parent->get_children().size() == k) { 
        cout << "No more space" << endl;
        return;
    }
    parent->add_child(child);
}

template<typename T, size_t k>
void Tree<T, k>::PreOrderIterator::visit(Node<T>* root) {
    if (!root) return;
    this->node_queue.push(root);
    for (const auto child : root->get_children()) {
        visit(child);
    }
}

template<typename T, size_t k>
void Tree<T, k>::PostOrderIterator::visit(Node<T>* root) {
    if (!root) return;
    for (const auto child : root->get_children()) {
        visit(child);
    }
    this->node_queue.push(root);
}

template<typename T, size_t k>
void Tree<T, k>::InOrderIterator::visit(Node<T>* root) {
    if (!root) return;
    vector<Node<T>*> children = root->get_children();
    if (children.size() >= 1) { this->visit(children[0]); }
    this->node_queue.push(root);
    if (children.size() >= 2) { this->visit(children[1]); }
}

template<typename T, size_t k>
void Tree<T, k>::BFSIterator::visit(Node<T>* root) {
    if (!root) return;
    queue<Node<T>*> q;
    q.push(root);
    while (!q.empty()) {
        Node<T>* u = q.front();
        q.pop();
        this->node_queue.push(u);
        for (const auto child : u->get_children()) {
            q.push(child);
        }
    }
}

template<typename T, size_t k>
void Tree<T, k>::DFSIterator::visit(Node<T>* root) {
    if (!root) return;
    for (const auto child : root->get_children()) {
        this->visit(child);
    }
    this->node_queue.push(root);
}

template<typename T, size_t k>
void Tree<T, k>::myHeap() {
    vector<T> values;
    if (k != 2) { 
        cout << "Heap available only for 2-ary" << endl;
        return;
    }
    for (auto it = this->begin_bfs_scan(); it != this->end_bfs_scan(); ++it) {
        values.push_back((*it)->get_value());
    }
    std::sort(values.begin(), values.end());
    if (values.empty()) { return; }
    delete root;
    root = new Node<T>(values[0]);
    vector<Node<T>*> nodes;
    nodes.push_back(root);
    for (unsigned int i = 1; i < values.size(); i++){
        Node<T>* newNode = new Node<T>(values[i]);
        nodes.push_back(newNode);
        add_sub_node(nodes[(i-1)/2], newNode);
    }
}

#endif // TREE_HPP
