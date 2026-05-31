// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <utility>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::string altPath = std::string("../") + filename;
    file.open(altPath);
    if (!file) {
      altPath = std::string("../src/") + filename;
      file.open(altPath);
    }
    if (!file) {
      std::cout << "File error!" << std::endl;
      return;
    }
  }

  std::string word;
  int ch;
  while ((ch = file.get()) != EOF) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += static_cast<char>(
          std::tolower(static_cast<unsigned char>(ch)));
    } else if (!word.empty()) {
      tree.add(word);
      word.clear();
    }
  }
  if (!word.empty()) {
    tree.add(word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> freq;

  std::vector<typename BST<std::string>::Node*> stack;
  typename BST<std::string>::Node* current = tree.getRoot();
  while (current != nullptr || !stack.empty()) {
    while (current != nullptr) {
      stack.push_back(current);
      current = current->left;
    }
    current = stack.back();
    stack.pop_back();
    freq.push_back({current->value, current->count});
    current = current->right;
  }

  std::sort(freq.begin(), freq.end(),
    [](const std::pair<std::string, int>& a,
       const std::pair<std::string, int>& b) {
      if (a.second == b.second) return a.first < b.first;
      return a.second > b.second;
    });

  std::ofstream out("result/freq.txt");
  for (const auto& p : freq) {
    std::cout << p.first << " " << p.second << std::endl;
    out << p.first << " " << p.second << std::endl;
  }
  out.close();
}
