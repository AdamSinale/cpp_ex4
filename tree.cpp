
#include "node.cpp"
#include <queue>
#include <iostream>
#include <vector>
#include <memory>

using std::queue;
using std::ostream;
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

    void add_root(Node<T>* root) {
        this->root = root;
    }

    void add_sub_node(Node<T>* parent, Node<T>* child) {
        if (parent->get_children().size() == k) { 
            cout << "No more space" << endl;
            return;
        }
        parent->add_child(child);
    }

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
            return os << (*iterator)->get_value();
        }
    };

    class PreOrderIterator : public TreeIterator {
    public:
        PreOrderIterator(Node<T>* root) : TreeIterator() {
            if (root != nullptr) {
                this->visit(root);
            }
        }
        void visit(Node<T>* root) {
            if (!root) return;
            this->node_queue.push(root);
            for (const auto child : (*root).get_children()) {
                visit(child);
            }
        }
    };

    TreeIterator begin_pre_order() { return PreOrderIterator(root); }
    TreeIterator end_pre_order() { return PreOrderIterator(nullptr); }

    class PostOrderIterator : public TreeIterator {
    public:
        PostOrderIterator(Node<T>* root) : TreeIterator() {
            if (root != nullptr) {
                this->visit(root);
            }
        }
        void visit(Node<T>* root) {
            if (!root) return;
            for (const auto child : (*root).get_children()) {
                visit(child);
            }
            this->node_queue.push(root);
        }
    };

    TreeIterator begin_post_order() { return PostOrderIterator(root); }
    TreeIterator end_post_order() { return PostOrderIterator(nullptr); }

    class InOrderIterator : public TreeIterator {
    public:
        InOrderIterator(Node<T>* root) : TreeIterator() {
            if (root != nullptr) {
                this->visit(root);
            }
        }

        void visit(Node<T>* root) {
            if (!root) return;
            vector<Node<T>*> children = (*root).get_children();
            if (children.size() >= 1) { this->visit(children[0]); }
            this->node_queue.push(root);
            if (children.size() >= 2) { this->visit(children[1]); }
        }
    };

    TreeIterator begin_in_order() { return InOrderIterator(root); }
    TreeIterator end_in_order() { return InOrderIterator(nullptr); }

    class BFSIterator : public TreeIterator {
    public:
        BFSIterator(Node<T>* root) : TreeIterator() {
            if (root != nullptr) {
                this->visit(root);
            }
        }

        void visit(Node<T>* root) {
            if (!root) return;
            queue<Node<T>*> q;
            q.push(root);
            while (!q.empty()) {
                Node<T>* u = q.front();
                q.pop();
                this->node_queue.push(u);
                for (const auto child : (*u).get_children()) {
                    q.push(child);
                }
            }
        }
    };
    TreeIterator begin() { return end_bfs_scan(); }
    TreeIterator end() { return end_bfs_scan(); }
    TreeIterator begin_bfs_scan() { return BFSIterator(root); }
    TreeIterator end_bfs_scan() { return BFSIterator(nullptr); }

    class DFSIterator : public TreeIterator {
    public:
        DFSIterator(Node<T>* root) : TreeIterator() {
            if (root != nullptr) {
                this->visit(root);
            }
        }

        void visit(Node<T>* root) {
            if (!root) return;
            for (const auto child : (*root).get_children()) {
                this->visit(child);
            }
            this->node_queue.push(root);
        }
    };

    TreeIterator begin_dfs_scan() { return DFSIterator(root); }
    TreeIterator end_dfs_scan() { return DFSIterator(nullptr); }

};
