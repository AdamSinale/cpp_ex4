#pragma once

#include "node.cpp"
#include <queue>
#include <stack>
#include <iostream>
#include <vector>

using std::queue;
using std::stack;
using std::ostream;
using std::vector;
using std::cout;
using std::endl;

template<typename T, size_t k = 2>
class Tree {
private:
    Node<T> root;

public:
    Tree() : root(T{}) {}
    ~Tree() {}

    void add_root(const Node<T>& root) {
        this->root = root;
    }

    void add_sub_node(Node<T>& parent, const Node<T>& child) {
        if (parent.get_children().size() == k) { 
            std::cout << "No more space" << std::endl;
            return;
        }
        parent.add_child(child);
    }

    friend std::ostream& operator<<(std::ostream& os, const Tree<T, k>& tree) {
        // Implement printing logic here
        return os;
    }

    class PreOrderIterator;
    class PostOrderIterator;
    class InOrderIterator;
    class BFSIterator;
    class DFSIterator;

    PreOrderIterator begin_pre_order() { return PreOrderIterator(&root); }
    PreOrderIterator end_pre_order() { return PreOrderIterator(nullptr); }

    PostOrderIterator begin_post_order() { return PostOrderIterator(&root); }
    PostOrderIterator end_post_order() { return PostOrderIterator(nullptr); }

    InOrderIterator begin_in_order() { return InOrderIterator(&root); }
    InOrderIterator end_in_order() { return InOrderIterator(nullptr); }

    BFSIterator begin_bfs_scan() { return BFSIterator(&root); }
    BFSIterator end_bfs_scan() { return BFSIterator(nullptr); }
    BFSIterator begin() { return BFSIterator(&root); }
    BFSIterator end() { return BFSIterator(nullptr); }

    DFSIterator begin_dfs_scan() { return DFSIterator(&root); }
    DFSIterator end_dfs_scan() { return DFSIterator(nullptr); }

    class TreeIterator {
    protected:
        stack<Node<T>*> node_stack;
        TreeIterator(Node<T>* root) {
            if (root != nullptr) {
                node_stack.push(root);
            }
        }

    public:
        virtual void visit(Node<T>* root) = 0;

        TreeIterator& operator++() {
            Node<T>* node = node_stack.top();
            node_stack.pop();
            visit(node);
            return *this;
        }

        bool operator!=(const TreeIterator& other) const {
            return !node_stack.empty() || !other.node_stack.empty();
        }

        Node<T>& operator*() const {
            return *node_stack.top();
        }

        Node<T>* operator->() const {
            return node_stack.top();
        }
    };

    class PreOrderIterator : public TreeIterator {
    public:
        PreOrderIterator(Node<T>* root) : TreeIterator(root) {
            if (root) {
                this->visit(root);
            }
        }

        void visit(Node<T>* root) override {
            if (!root) return;
            for (auto it = root->get_children().rbegin(); it != root->get_children().rend(); ++it) {
                this->node_stack.push(&(*it));
            }
        }
    };

    class PostOrderIterator : public TreeIterator {
    public:
        PostOrderIterator(Node<T>* root) : TreeIterator(root) {
            if (root) {
                this->visit(root);
            }
        }

        void visit(Node<T>* root) override {
            if (!root) return;
            this->node_stack.push(root);
            for (const auto& child : root->get_children()) {
                this->node_stack.push(&child);
            }
        }
    };

    class InOrderIterator : public TreeIterator {
    public:
        InOrderIterator(Node<T>* root) : TreeIterator(root) {
            if (root) {
                this->visit(root);
            }
        }

        void visit(Node<T>* root) override {
            if (!root) return;
            const auto& children = root->get_children();
            if (children.size() >= 1) { this->node_stack.push(&children[0]); }
            this->node_stack.push(root);
            if (children.size() >= 2) { this->node_stack.push(&children[1]); }
        }
    };

    class BFSIterator : public TreeIterator {
    public:
        BFSIterator(Node<T>* root) : TreeIterator(root) {
            if (root) {
                this->visit(root);
            }
        }

        void visit(Node<T>* root) override {
            if (!root) return;
            std::queue<Node<T>*> q;
            q.push(root);
            while (!q.empty()) {
                Node<T>* u = q.front();
                q.pop();
                this->node_stack.push(u);
                for (const auto& child : u->get_children()) {
                    q.push(const_cast<Node<T>*>(&child));
                }
            }
        }
    };

    class DFSIterator : public TreeIterator {
    public:
        DFSIterator(Node<T>* root) : TreeIterator(root) {
            if (root) {
                this->visit(root);
            }
        }

        void visit(Node<T>* root) override {
            if (!root) return;
            this->node_stack.push(root);
            for (auto it = root->get_children().rbegin(); it != root->get_children().rend(); ++it) {
                this->node_stack.push(&(*it));
            }
        }
    };
};
