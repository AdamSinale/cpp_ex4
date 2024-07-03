#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include "tree.cpp"

using namespace std;

template <typename T>
struct TreeNode {
    Node<T>* node;
    sf::CircleShape shape;
    sf::Text text;
    float x, y;  // Position of the node
};

struct Button {
    sf::RectangleShape shape;
    sf::Text text;
    string label;
};

template<typename T>
Node<T>* getNodeAtPosition(float x, float y, vector<TreeNode<T>>& treeNodes) {
    for (auto& treeNode : treeNodes) {
        if (treeNode.shape.getGlobalBounds().contains(x, y)) {
            return treeNode.node;
        }
    }
    return nullptr;
}

void drawInputPrompt(sf::RenderWindow& window, const string& inputStr, sf::Font& font, const string& promptStr) {
    sf::Text prompt;
    prompt.setFont(font);
    prompt.setString(promptStr + inputStr);
    prompt.setCharacterSize(24);
    prompt.setFillColor(sf::Color::Black);
    prompt.setPosition(10, 10);
    window.draw(prompt);
}

template<typename T>
vector<TreeNode<T>> spreadNodes(vector<Node<T>*>& nodes, sf::Font& font) {
    vector<TreeNode<T>> treeNodes;
    float angleStep = 360.0f / nodes.size();
    float radius = 200.0f;
    float centerX = 400;
    float centerY = 300;

    for (size_t i = 0; i < nodes.size(); ++i) {
        float angle = angleStep * i * 3.14f / 180.0f;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);

        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(x, y);

        sf::Text text;
        text.setFont(font);
        text.setString(nodes[i]->get_value_str());
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x + 10, y + 5);

        treeNodes.push_back({nodes[i], circle, text, x, y});
    }
    return treeNodes;
}

template<typename T>
void drawTreeNodes(sf::RenderWindow& window, vector<TreeNode<T>>& treeNodes) {
    for (const auto& treeNode : treeNodes) {
        window.draw(treeNode.shape);
        window.draw(treeNode.text);
    }
}

template<typename T>
void drawConnections(sf::RenderWindow& window, vector<TreeNode<T>>& treeNodes) {
    for (const auto& treeNode : treeNodes) {
        for (const auto& child : treeNode.node->get_children()) {
            float parentX = treeNode.x + 20;
            float parentY = treeNode.y + 20;

            for (const auto& childNode : treeNodes) {
                if (childNode.node == child) {
                    float childX = childNode.x + 20;
                    float childY = childNode.y + 20;

                    sf::Vertex line[] =
                    {
                        sf::Vertex(sf::Vector2f(parentX, parentY), sf::Color::Black),
                        sf::Vertex(sf::Vector2f(childX, childY), sf::Color::Black)
                    };

                    window.draw(line, 2, sf::Lines);
                    break;
                }
            }
        }
    }
}

template<typename T, size_t k>
vector<Button> createButtons(Tree<T, k>& tree, sf::Font& font) {
    vector<Button> buttons;
    buttons.clear();
    vector<string> labels;

    if (k == 2) {
        labels = {"PreOrder", "InOrder", "PostOrder", "BFS", "DFS", "MyHeap"};
    } else {
        labels = {"BFS", "DFS"};
    }

    float x = 10;
    float y = 50;
    float width = 100;
    float height = 30;
    float spacing = 10;

    for (const auto& label : labels) {
        sf::RectangleShape shape(sf::Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2);

        sf::Text text;
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x + 10, y + 5);

        buttons.push_back({shape, text, label});

        y += height + spacing;
    }
    return buttons;
}

void drawButtons(sf::RenderWindow& window, vector<Button>& buttons) {
    for (const auto& button : buttons) {
        window.draw(button.shape);
        window.draw(button.text);
    }
}

bool isButtonPressed(const sf::Event& event, const Button& button) {
    return event.mouseButton.x >= button.shape.getPosition().x &&
           event.mouseButton.x <= button.shape.getPosition().x + button.shape.getSize().x &&
           event.mouseButton.y >= button.shape.getPosition().y &&
           event.mouseButton.y <= button.shape.getPosition().y + button.shape.getSize().y;
}

template<typename T, size_t k>
void displayIteratorValues(Tree<T, k>& tree, const string& label, sf::Text& iteratorResult) {
    ostringstream oss;

    if (label == "PreOrder") {
        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
            oss << it << " ";
        }
    } else if (label == "InOrder") {
        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
            oss << it << " ";
        }
    } else if (label == "PostOrder") {
        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
            oss << it << " ";
        }
    } else if (label == "BFS") {
        for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
            oss << it << " ";
        }
    } else if (label == "DFS") {
        for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
            oss << it << " ";
        }
    }

    iteratorResult.setString(oss.str());
    iteratorResult.setPosition(10, 500);
}
