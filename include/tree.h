// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <algorithm>

class Tree {
 private:
    struct Node {
        std::vector<Node*> descendants;
        char ch;
        Node() : ch('#') {}
    };
    Node* kernel = nullptr;
    std::vector<std::vector<char>> permutations;
    void createTree(Node*, const std::vector<char>&);
    void makePermutations(Node*, std::vector<char>);
    void createTreePermutations(const std::vector<char>&);
 public:
    explicit Tree(const std::vector<char>&);
    std::vector<std::vector<char>> getPermutations() const;
};

void Tree::createTree(Node* kernel, const std::vector<char>& sel) {
    if (kernel != nullptr) {
        for (const auto& symbol : sel) {
            Node* pereh = new Node;
            pereh->ch = symbol;
            kernel->descendants.push_back(pereh);
            std::vector<char> vec(sel);
            vec.erase(std::find(vec.begin(), vec.end(), symbol));
            createTree(pereh, vec);
        }
    }
}


void Tree::makePermutations(Node* kernel, std::vector<char> variation) {
    if (kernel != nullptr && kernel->ch != '#')
        variation.push_back(kernel->ch);
    if (kernel->descendants.empty())
        permutations.push_back(variation);
    for (Node* child : kernel->descendants) {
        makePermutations(child, variation);
    }
}

void Tree::createTreePermutations(const std::vector<char>& vector_) {
    createTree(kernel, vector_);
    makePermutations(kernel, {});
}

Tree::Tree(const std::vector<char>& vector_) {
    kernel = new Node;
    createTreePermutations(vector_);
}

std::vector<std::vector<char>> Tree::getPermutations() const {
    return permutations;
}
#endif  // INCLUDE_TREE_H_
