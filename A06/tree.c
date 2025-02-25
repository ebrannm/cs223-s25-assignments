/*----------------------------------------------
 * Author: Elisabeth Brann 
 * Date: 02/28/25
 * Description: Implementation of a binary search tree
 ---------------------------------------------*/

#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

struct tree_node* find(const char* name, struct tree_node* root) {
  if (root == NULL || strcmp(root->data.name, name) == 0) {
    return root;
  }
  if (strcmp(name, root->data.name) < 0) {
    return find(name, root->left);
  }
  return find(name, root->right);
}

struct tree_node* insertHelper(struct tree_node* node, struct tree_node* root) {
  if (root == NULL) {
    return node;
  }
  if (strcmp(node->data.name, root->data.name) < 0) {
    root->left = insertHelper(node, root->left);
  }
  else if (strcmp(node->data.name, root->data.name) > 0) {
    root->right = insertHelper(node, root->right);
  }
  return root;
}

struct tree_node* insert(const char* name, struct tree_node* root) {
  struct tree_node* newNode = malloc(sizeof(struct tree_node));
  if (newNode == NULL) {
    printf("Memory allocation failed\n");
    return root;
  }
  strcpy(newNode->data.name, name);
  newNode->left = NULL;
  newNode->right = NULL;
  if (root == NULL) {
    root = newNode;
    return root;
  }
  else {
    root = insertHelper(newNode, root);
    return root;
  }
}

void clear(struct tree_node* root) {
  if (root == NULL) {
    return;
  }
  clear(root->left);
  clear(root->right);
  free(root);
}

void printHelper(struct tree_node* root, int depth) {
  if (root != NULL) {
    if (root->left != NULL) {
      for (int i = 0; i < depth + 1; i++) {
        printf(" ");
      }
      printf("l:%s\n", root->left->data.name);
      printHelper(root->left, depth + 1);
    }
    if (root->right != NULL) {
      for (int i = 0; i < depth + 1; i++) {
        printf(" ");
      }
      printf("r:%s\n", root->right->data.name);
      printHelper(root->right, depth + 1);
    }
  }
}

void print(struct tree_node* root) {
  if (root != NULL) {
    printf("%s\n", root->data.name);
    printHelper(root, 0);
  }
}

void printSorted(struct tree_node* root) {
  if (root != NULL) {
    printSorted(root->left);
    printf("%s\n", root->data.name);
    printSorted(root->right);
  }
}

