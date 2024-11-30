//
// Created by 강민재 on 2024. 11. 30..
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node* left;
    struct Node* right;
    int id;
} Node;

typedef struct Tree {
    struct Node* root;
} Tree;

Node* makeNode(int id);
void setChild(Node* parent, Node* left, Node* right);
Node* searchNode(Node* root, int id);

Tree initTree();
void searchTree(Tree* tree);

int main() {
    Tree tree = initTree();
    searchTree(&tree);

    return 0;
}

Node* makeNode(int id) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->id = id;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void setChild(Node* parent, Node* left, Node* right) {
    if (left->id != 0) parent->left = left;
    if (right->id != 0) parent->right = right;

    return;
}

Node* searchNode(Node* root, int id) {
    if (root == NULL) return NULL;

    if (root->id == id) {
        return root;
    }

    Node* left_child = searchNode(root->left, id);
    if (left_child != NULL)
        return left_child;

    Node* right_child = searchNode(root->right, id);
    if (right_child != NULL)
        return right_child;

    return NULL;
}

Tree initTree() {
    Tree tree;
    tree.root = NULL;

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int parent, left, right;
        scanf("%d %d %d", &parent, &left, &right);

        Node* left_node = makeNode(left);
        Node* right_node = makeNode(right);

        if (i == 0) {
            tree.root = makeNode(parent);
            setChild(tree.root, left_node, right_node);
        } else {
            Node* parent_node = searchNode(tree.root, parent);
            setChild(parent_node, left_node, right_node);
        }

    }

    return tree;
}

void searchTree(Tree* tree) {
    int s;
    scanf("%d", &s);
    getchar();
    for (int i = 0; i < s; i++) {
        char cmd[100];
        gets(cmd);

        int len_cmd = strlen(cmd);

        Node* p = tree->root;
        for (int j = 0; j < len_cmd; j++) {
            printf(" %d", p->id);
            switch (cmd[j]) {
                case 'R':
                    p = p->right;
                    break;
                case 'L':
                    p = p->left;
                    break;
            }
        }
        printf(" %d\n", p->id);
    }
}