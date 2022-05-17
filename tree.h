#include"dataType.h"
#include"linkedList.h"
#include"spendList.h"

#ifndef TREE_H
    #define TREE_H
    struct Tree;
    typedef struct Tree Tree;
    Tree* newBinarySearchTree(DataType type);
    boolean isEmptyTree(const Tree* tree);
    int tree_lengeth(const Tree* tree);
    void tree_add(Tree* tree, void* value);
    LinkedList* tree_toList(Tree* tree);
    LLNode* tree_toSpendList(Tree* tree);
    void tree_destory(Tree* tree);
    void tree_preOrder(Tree* tree, void (*action)(DataType type,void* value));
    void tree_inOrder(Tree* tree, void (*action)(DataType type,void* value));
    void tree_postOrder(Tree* tree, void (*action)(DataType type,void* value));
#endif