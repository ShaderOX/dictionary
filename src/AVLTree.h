#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include <iostream>
#include "LinkedList.h"

template <typename T, typename K>
class AVLTree {
public:
  struct TreeNode;

  AVLTree() {
    root = nullptr;
  }

  TreeNode *Search(T word) {

    TreeNode *p = root;
    while (p != nullptr) {
      if (word == p->word) {
        return p;
      }
      else if (word < p->word) {
        p = p->left;
      }
      else {
        p = p->right;
      }
    }
    return nullptr;
  }

  void Insert(T word, K meaning) {
    root = Insert(word, meaning, root);
  }

  void Remove(T x) {
    root = Remove(x, root);
  }

  void Display() {
    InOrder(root);
    std::cout << std::endl;
  }

  ~AVLTree() {
    MakeEmpty(root);
  }

  struct TreeNode {
    T word;
    LinkedList<K> meaning;

    TreeNode *left;
    TreeNode *right;
    int height;
  };

private:
  TreeNode *root;

  void MakeEmpty(TreeNode *t) {
    if (t == nullptr)
      return;
    MakeEmpty(t->left);
    MakeEmpty(t->right);
    delete t;
  }

  TreeNode *Insert(T word, K meaning, TreeNode *t) {
    if (t == nullptr) {
      t = new TreeNode;

      t->word = word;
      t->meaning.Insert(meaning);

      t->height = 0;
      t->left = t->right = nullptr;
    }
    else if (word < t->word) {
      t->left = Insert(word, meaning, t->left);
      if (Height(t->left) - Height(t->right) == 2) {
        if (word < t->left->word)
          t = SingleRightRotate(t);
        else
          t = DoubleRightRotate(t);
      }
    }
    else if (word > t->word) {
      t->right = Insert(word, meaning, t->right);
      if (Height(t->right) - Height(t->left) == 2) {
        if (word >= t->right->word)
          t = SingleLeftRotate(t);
        else
          t = DoubleLeftRotate(t);
      }
    }
    else if (word == t->word) {
      t->meaning.Insert(meaning);
    }

    t->height = std::max(Height(t->left), Height(t->right)) + 1;
    return t;
  }

  TreeNode *SingleRightRotate(TreeNode *&t) {
    TreeNode *u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = std::max(Height(t->left), Height(t->right)) + 1;
    u->height = std::max(Height(u->left), t->height) + 1;
    return u;
  }

  TreeNode *SingleLeftRotate(TreeNode *&t) {
    TreeNode *u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = std::max(Height(t->left), Height(t->right)) + 1;
    u->height = std::max(Height(t->right), t->height) + 1;
    return u;
  }

  TreeNode *DoubleLeftRotate(TreeNode *&t) {
    t->right = SingleRightRotate(t->right);
    return SingleLeftRotate(t);
  }

  TreeNode *DoubleRightRotate(TreeNode *&t) {
    t->left = SingleLeftRotate(t->left);
    return SingleRightRotate(t);
  }

  TreeNode *FindMin(TreeNode *t)
  {
    if (t == nullptr)
      return nullptr;
    else if (t->left == nullptr)
      return t;
    else
      return FindMin(t->left);
  }

  TreeNode *FindMax(TreeNode *t) {
    if (t == nullptr)
      return nullptr;
    else if (t->right == nullptr)
      return t;
    else
      return FindMax(t->right);
  }

  TreeNode *Remove(int x, TreeNode *t) {
    TreeNode *temp;

    // Element not found
    if (t == nullptr)
      return nullptr;

    // Searching for element
    else if (x < t->word)
      t->left = Remove(x, t->left);
    else if (x > t->word)
      t->right = Remove(x, t->right);

    // Element found
    // With 2 children
    else if (t->left && t->right) {
      temp = FindMin(t->right);
      t->word = temp->word;
      t->right = Remove(t->word, t->right);
    }
    // With one or zero child
    else {
      temp = t;
      if (t->left == nullptr)
        t = t->right;
      else if (t->right == nullptr)
        t = t->left;
      delete temp;
    }
    if (t == nullptr)
      return t;

    t->height = std::max(Height(t->left), Height(t->right)) + 1;

    // If node is unbalanced
    // If left node is deleted, right case
    if (Height(t->left) - Height(t->right) == 2) {
      // right right case
      if (Height(t->left->left) - Height(t->left->right) == 1)
        return SingleLeftRotate(t);
      // right left case
      else
        return DoubleLeftRotate(t);
    }
    // If right node is deleted, left case
    else if (Height(t->right) - Height(t->left) == 2) {
      // left left case
      if (Height(t->right->right) - Height(t->right->left) == 1)
        return SingleRightRotate(t);
      // left right case
      else
        return DoubleRightRotate(t);
    }
    return t;
  }

  int Height(TreeNode *t) {
    return (t == nullptr ? -1 : t->height);
  }

  int GetBalance(TreeNode *t) {
    if (t == nullptr)
      return 0;
    else
      return Height(t->left) - Height(t->right);
  }

  void InOrder(TreeNode *t) {
    if (t == nullptr)
      return;
    InOrder(t->left);
    std::cout << t->word << " ";
    InOrder(t->right);
  }

};

#endif
