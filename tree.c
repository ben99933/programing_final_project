#include"tree.h"
#include"dataType.h"
#include<stdlib.h>
#include"debug.h"
#include<stdio.h>
#include"spend.h"
#include"spendList.h"

static LLNode* LLNodeBuffer;
static void clearLLNodeBuffer(){
    LLNodeBuffer = NULL;
}

struct Node{
    struct Node* left;
    struct Node* right;
    struct Node* perant;
    DataType type;
    int times;//該資料出現幾次
    void* value;
};
typedef struct Node Node;
struct Tree{
    DataType type;
    int size;
    Node* root;
};
Tree* newBinarySearchTree(DataType type){
    Tree* tree = malloc(sizeof(Tree));
    tree->type = type;
    tree->size = 0;
    tree->root = NULL;
    return tree;
}
Node* newNode(DataType type, void* value){
    Node* node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->perant = NULL;
    node->type = type;
    node->times = 1;
    node->value = value;
    return node;
}
boolean isEmptyTree(const Tree* tree){
    if(tree->root)return False;
    return True;
}
int tree_lengeth(const Tree* tree){
    return tree->size;
}
static boolean isLeaf(Node* node){
    if(node->left == NULL && node->right == NULL)return True;
    return False;
}
static Node* getNode(Tree* tree, void* value){
    Node* focus = tree->root;
    while(focus != NULL){
        int cmp = compareTo(tree->type, value, focus->value);
        if( cmp < 0){
            focus = focus->left;
        }else if(cmp > 0){
            focus = focus->right;
        }else return focus;
    }
    errorMsg("Node is null",__FILE__,__LINE__);
    return NULL;
}
static Node* getNodeParent(Tree* tree,void* value){
    Node* focus = tree->root;
    Node* parent = NULL;
    while(focus != NULL){
        int cmp = compareTo(tree->type, value, focus->value);
        if( cmp < 0){
            parent = focus;
            focus = focus->left;
        }else if(cmp > 0){
            parent = focus;
            focus = focus->right;
        }else return parent;
    }
    errorMsg("Node is null",__FILE__,__LINE__);
    return NULL;
}
static Node* getMinChild(Node* node){
    Node* focus = node;
    while (focus && focus->left) {
        focus = focus->left;
    }
    return focus;
}

void tree_add(Tree* tree, void* value){
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
                    node->perant = focus;
                    break;
                }
            }else if(compareTo(tree->type,value,focus->value) == 1){
                if(focus->right != NULL){
                    focus = focus->right;
                }else{
                    focus->right = node;
                    node->perant = focus;
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

static void pushToList(DataType type, void* value){
    if(type == SpendType){
        Spend spend = *(Spend*)value;
        linkedList_add(listBuffer, newSpend(spend.cost,spend.category,spend.date,spend.note));
    }else if(type==Int){
        linkedList_add(listBuffer, newInt(*(int*)value));
    }
}
static void pushToSpendList(DataType type,void* value){
    if(type != SpendType)return;
    LLNode* node = malloc(sizeof(LLNode));
    node->spend = *(Spend*)value;
    node->next = NULL;
    node->prev = NULL;
    if(LLNodeBuffer == NULL){
        LLNodeBuffer = node;
        return;
    }else{
        sortedInsert(LLNodeBuffer, NULL, node, intBuffer[15]);
        intBuffer[15]++;
    }

}
LinkedList* tree_toList(Tree* tree){
    if(isEmptyTree(tree))return NULL;
    LinkedList* list = newLinkedList(tree->type);
    listBuffer = list;
    tree_inOrder(tree,pushToList);
    return list;
}
/**
 * 為了要和"SpendList"相容 
 */
LLNode* tree_toSpendList(Tree* tree){
    if(isEmptyTree(tree)){
        debugMsg("Tree is emtpy",__FILE__,__LINE__);
        return NULL;
    }
    LLNode* head = malloc(sizeof(LLNode));
    clearIntBuffer();
    clearLLNodeBuffer();
    tree_inOrder(tree,pushToSpendList);
    head = LLNodeBuffer;
    return head;
}
static void destoryNode(Node* node){
    if(node == NULL)return;
    if(node->left != NULL)destoryNode(node->left);
    if(node->right != NULL)destoryNode(node->right);
    free(node->value);
    free(node);
}
void tree_destory(Tree* tree){
    destoryNode(tree->root);
    tree->root = NULL;
    tree->size = 0;
    free(tree);
}

static void preOrderFunc(Node* node, void (*action)(DataType type,void* value)){
    if(node == NULL)return;
    for(int i = 0;i<node->times;i++)action(node->type,node->value);
    
    preOrderFunc(node->left, action);
    preOrderFunc(node->right, action);
}
static void inOrderFunc(Node* node, void (*action)(DataType type,void* value)){
    if(node == NULL)return;
    inOrderFunc(node->left, action);

    for(int i = 0;i<node->times;i++)action(node->type,node->value);

    inOrderFunc(node->right,action);
}
static void postOrderFunc(Node* node, void (*action)(DataType type,void* value)){
    if(node == NULL)return;
    postOrderFunc(node->left, action);
    postOrderFunc(node->right, action);

    for(int i = 0;i<node->times;i++)action(node->type,node->value);
}
void tree_preOrder(Tree* tree, void (*action)(DataType type,void* value)){
    preOrderFunc(tree->root,action);
}
void tree_inOrder(Tree* tree, void (*action)(DataType type,void* value)){
    inOrderFunc(tree->root,action);
}
void tree_postOrder(Tree* tree, void (*action)(DataType type,void* value)){
    postOrderFunc(tree->root,action);
}

