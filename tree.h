#include"dataType.h"
#include"linkedList.h"

#ifndef TREE_H
    #define TREE_H
    struct BST;
    typedef struct BST BST;
    BST* newBinarySearchTree(DataType type);
    boolean isEmptyTree(const BST* tree);
    int tree_lengeth(const BST* tree);
    void tree_add(BST* tree, void* value);
    LinkedList* toList(const BST* tree);
#endif