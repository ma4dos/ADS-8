// Copyright 2025 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>

template <typename T>
class BST {
 public:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;
  };

 private:
  Node* root;

  Node* addNode(Node* node, const T& value) {
    if (node == nullptr) {
      node = new Node;
      node->value = value;
      node->count = 1;
      node->left = nullptr;
      node->right = nullptr;
      return node;
    }
    if (value < node->value) {
      node->left = addNode(node->left, value);
    } else if (value > node->value) {
      node->right = addNode(node->right, value);
    } else {
      node->count++;
    }
    return node;
  }

  int depthNode(Node* node) const {
    if (node == nullptr) return 0;
    int leftDepth = depthNode(node->left);
    int rightDepth = depthNode(node->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
  }

  Node* searchNode(Node* node, const T& value) const {
    if (node == nullptr || node->value == value) {
      return node;
    }
    if (value < node->value) {
      return searchNode(node->left, value);
    } else {
      return searchNode(node->right, value);
    }
  }

  void clearTree(Node* node) {
    if (node == nullptr) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}

  ~BST() {
    clearTree(root);
  }

  void add(const T& value) {
    root = addNode(root, value);
  }

  int depth() const {
    return depthNode(root);
  }

  int search(const T& value) const {
    Node* node = searchNode(root, value);
    if (node == nullptr) return 0;
    return node->count;
  }

  Node* getRoot() const {
    return root;
  }
};

#endif  // INCLUDE_BST_H_
