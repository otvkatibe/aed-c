#ifndef BST_C_H
#define BST_C_H

#include <stdio.h>
#include <stdlib.h>

typedef int  bst_item;

typedef struct bst_node {
    bst_item           key;
    struct bst_node   *left;
    struct bst_node   *right;
} bst_node;

typedef bst_node* bst_tree;

/* --- criação / destruição -------------------------- */

static inline bst_tree bst_create(void) { return NULL; }

void bst_free(bst_node *node)
{
    if (node == NULL) return;
    bst_free(node->left);
    bst_free(node->right);
    free(node);
}

static inline void bst_destroy(bst_tree *t) {
    bst_free(*t);
    *t = NULL;
}

/* --- busca ---------------------------------------- */

bst_node* bst_find(bst_tree t, bst_item key)
{
    while (t) {
        if      (key < t->key) t = t->left;
        else if (key > t->key) t = t->right;
        else                   return t;
    }
    return NULL;
}

bst_node* bst_find_rec(bst_tree t, bst_item key)
{
    if (!t)                   return NULL;
    if (key == t->key)        return t;
    if (key <  t->key)        return bst_find_rec(t->left,  key);
    /* key > t->key */        return bst_find_rec(t->right, key);
}

/* --- inserção ------------------------------------- */

int bst_insert(bst_tree *t, bst_item key)
{
    bst_node *parent = NULL, *curr = *t;

    /* procura posição de inserção */
    while (curr) {
        parent = curr;
        if      (key < curr->key) curr = curr->left;
        else if (key > curr->key) curr = curr->right;
        else                      return 0;          /* chave já existe */
    }

    /* cria nó */
    bst_node *node = (bst_node*)malloc(sizeof *node);
    if (!node) return 0;

    node->key = key;
    node->left = node->right = NULL;

    if (!parent)      *t = node;              /* árvore estava vazia */
    else if (key < parent->key) parent->left  = node;
    else                        parent->right = node;

    return 1;
}

/* --- percursos ------------------------------------ */

void bst_preorder (bst_node *n) { 
    if (n){ 
        printf("%d ", n->key); 
        bst_preorder(n->left); 
        bst_preorder(n->right);
    } 
}

void bst_inorder  (bst_node *n) { 
    if (n){ 
        bst_inorder (n->left); 
        printf("%d ", n->key); 
        bst_inorder (n->right);
    } 
}
void bst_postorder(bst_node *n) { 
    if (n){ bst_postorder(n->left); 
        bst_postorder(n->right); 
        printf("%d ", n->key);
    } 
}

/* --- altura e contagem ---------------------------- */

int bst_height(bst_node *n)
{
    if (!n) return 0;
    int hL = bst_height(n->left);
    int hR = bst_height(n->right);
    return (hL > hR ? hL : hR) + 1;
}

int bst_count(bst_node *n)
{
    return n ? 1 + bst_count(n->left) + bst_count(n->right) : 0;
}

/* --- remoção -------------------------------------- */

bst_node* bst_min(bst_node *n)              /* menor na subárvore */
{
    while (n && n->left) n = n->left;
    return n;
}

int bst_remove(bst_tree *t, bst_item key)
{
    bst_node *parent = NULL, *curr = *t;

    /* localiza nó */
    while (curr && curr->key != key) {
        parent = curr;
        curr = (key < curr->key) ? curr->left : curr->right;
    }
    if (!curr) return 0;                    /* não achou */

    /* caso 1: nó com 0 ou 1 filho */
    if (!curr->left || !curr->right) {
        bst_node *child = curr->left ? curr->left : curr->right;

        if (!parent)          *t = child;               /* era raiz */
        else if (parent->left == curr)  parent->left  = child;
        else                              parent->right = child;

        free(curr);
        return 1;
    }

    /* caso 2: 2 filhos – usa sucessor em ordem */
    bst_node *succ_parent = curr;
    bst_node *succ = curr->right;
    while (succ->left) { succ_parent = succ; succ = succ->left; }

    curr->key = succ->key;                               /* copia dado */

    /* remove sucessor */
    if (succ_parent->left == succ) succ_parent->left  = succ->right;
    else                           succ_parent->right = succ->right;

    free(succ);
    return 1;
}

/* --- espelhar árvore ------------------------------ */
void bst_mirror(bst_node *n)
{
    if (!n) return;
    bst_node *tmp = n->left;
    n->left  = n->right;
    n->right = tmp;
    bst_mirror(n->left);
    bst_mirror(n->right);
}

#endif /* BST_C_H */
