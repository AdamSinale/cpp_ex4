#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include "tree.cpp"
#include "gui_func.cpp"
#include "complex.hpp"

using namespace std;

vector<Button> buttons;
sf::Font font;
bool inputMode = false;
bool kInputMode = true;
string inputStr = "";
string kStr = "";
int k = 2;
sf::Text iteratorResult;

int main() {
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font" << endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

    vector<Node<Complex>*> nodes;
    Tree<Complex, 2>* binaryTreePtr = nullptr;
    Tree<Complex, 3>* ternaryTreePtr = nullptr;
    Node<Complex>* selectedParent = nullptr;
    vector<TreeNode<Complex>> treeNodes;

    iteratorResult.setFont(font);
    iteratorResult.setCharacterSize(20);
    iteratorResult.setFillColor(sf::Color::Black);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (kInputMode && event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    kStr += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == '\b' && !kStr.empty()) {
                    kStr.pop_back();
                } else if (event.text.unicode == '\r' && !kStr.empty()) {
                    k = stoi(kStr);
                    kInputMode = false;
                    inputMode = true;
                }
            }
            if (inputMode && event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    inputStr += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == '\b' && !inputStr.empty()) {
                    inputStr.pop_back();
                } else if (event.text.unicode == '\r' && !inputStr.empty()) {
                    int numNodes = stoi(inputStr);
                    for (int i = 0; i < numNodes; ++i) {
                        nodes.push_back(new Node<Complex>(Complex(i + 1, i + 1)));
                    }
                    if (!nodes.empty()) {
                        if (k == 2) {
                            binaryTreePtr = new Tree<Complex, 2>();
                            binaryTreePtr->add_root(nodes[0]);
                            treeNodes = spreadNodes(nodes, font);
                            buttons = createButtons(*binaryTreePtr, font);
                        } else {
                            ternaryTreePtr = new Tree<Complex, 3>();
                            ternaryTreePtr->add_root(nodes[0]);
                            treeNodes = spreadNodes(nodes, font);
                            buttons = createButtons(*ternaryTreePtr, font);
                        }
                    }
                    inputMode = false;
                }
            }
            if (!inputMode && event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    float mouseX = event.mouseButton.x;
                    float mouseY = event.mouseButton.y;
                    Node<Complex>* clickedNode = getNodeAtPosition(mouseX, mouseY, treeNodes);
                    if (clickedNode) {
                        if (!selectedParent) {
                            selectedParent = clickedNode;
                        } else {
                            if (binaryTreePtr) {
                                binaryTreePtr->add_sub_node(selectedParent, clickedNode);
                            } else if (ternaryTreePtr) {
                                ternaryTreePtr->add_sub_node(selectedParent, clickedNode);
                            }
                            selectedParent = nullptr;
                        }
                    }
                    for (const auto& button : buttons) {
                        if (isButtonPressed(event, button)) {
                            if (binaryTreePtr) {
                                if (button.label == "MyHeap") {
                                    vector<Node<Complex>*> newNodes = binaryTreePtr->myHeap();
                                    treeNodes = spreadNodes(newNodes, font); // Update treeNodes after creating heap
                                } else {
                                    displayIteratorValues(*binaryTreePtr, button.label, iteratorResult);
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        if (kInputMode) {
            drawInputPrompt(window, kStr, font, "Enter k value: ");
        } else if (inputMode) {
            drawInputPrompt(window, inputStr, font, "Enter number of nodes: ");
        } else {
            drawTreeNodes(window, treeNodes);
            drawConnections(window, treeNodes);
            drawButtons(window, buttons);
            window.draw(iteratorResult);
        }
        window.display();
    }

    for (auto node : nodes) {
        delete node;
    }

    delete binaryTreePtr;
    delete ternaryTreePtr;

    return 0;
}
