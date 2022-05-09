#include"tree.h"
#include"dataType.h"
#include<stdlib.h>
#include"debug.h"
#include<stdio.h>

struct Node{
    struct Node* left;
    struct Node* right;
    DataType type;
    int times;//該資料出現幾次
    void* value;
};
typedef struct Node Node;

struct BST{
    DataType type;
    int size;
    Node* root;
    
};
BST* newBinarySearchTree(DataType type){
    BST* tree = malloc(sizeof(BST));
    tree->type = type;
    tree->size = 0;
    tree->root = NULL;
    return tree;
}
Node* newNode(DataType type, void* value){
    Node* node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->type = type;
    node->times = 1;
    node->value = value;
    return node;
}
boolean isEmptyTree(const BST* tree){
    if(tree->root)return False;
    return True;
}
int tree_lengeth(const BST* tree){
    return tree->size;
}
void tree_add(BST* tree, void* value){
    DataType type = tree->type;
    Node* node = newNode(tree->type,value);
    debugMsg("Node constructed",__FILE__,__LINE__);

    if(isEmptyTree(tree)){
        tree->root = node;
    }else{
        Node* focus = tree->root;
        while(True){
            if(compareTo(tree->type,value,focus->value) == -1){
                if(focus->left != NULL){
                    focus = focus->left;
                }else{
                    focus->left = node;
                    break;
                }
            }else if(compareTo(tree->type,value,focus->value) == 1){
                if(focus->right != NULL){
                    focus = focus->right;
                }else{
                    focus->right = node;
                    break;
                }
            }else{
                focus->times+=1;
                break;
            }
        }
    }
    tree->size+=1;
}
static void preOrderFunc(Node* node){
    if(node == NULL)return;
    printf("%d\n",*(int*)node->value);//do something
    
    preOrderFunc(node->left);
    preOrderFunc(node->right);
}
static void inOrderFunc(Node* node){
    if(node == NULL)return;
    preOrderFunc(node->left);

    printf("%d\n",*(int*)node->value);//do something

    preOrderFunc(node->right);
}
static void postOrderFunc(Node* node){
    if(node == NULL)return;
    preOrderFunc(node->left);
    preOrderFunc(node->right);

    printf("%d\n",*(int*)node->value);//do something
}
void preOrder(BST* tree){
    preOrderFunc(tree->root);
}
void inOrder(BST* tree){
    inOrderFunc(tree->root);
}
void postOrder(BST* tree){
    postOrderFunc(tree->root);
}

