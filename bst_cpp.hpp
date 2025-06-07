#pragma once
#include <memory>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class BST {
private:
    struct Node {
        T                     key;
        unique_ptr<Node> left;
        unique_ptr<Node> right;
        explicit Node(const T& k) : key(k) {}
    };

    unique_ptr<Node> root;

    /* ------------ helpers recursivos ----------------------------- */

    static void preorder (const Node* n) { 
        if(n){ 
            cout<<n->key<<' '; 
            preorder(n->left.get()); 
            preorder(n->right.get()); 
        } 
    }

    static void inorder  (const Node* n) { 
        if(n){ 
            inorder (n->left.get()); 
            cout<<n->key<<' '; 
            inorder (n->right.get()); 
        } 
    }

    static void postorder(const Node* n) { 
        if(n){ 
            postorder(n->left.get()); 
            postorder(n->right.get()); 
            cout<<n->key<<' '; 
        } 
    }

    static int  height (const Node* n){
        return n ? 1 + max(height(n->left.get()), height(n->right.get())) : 0;
    }

    static int  count  (const Node* n){
        return n ? 1 + count(n->left.get()) + count(n->right.get()) : 0;
    }
    
    static void mirror (Node* n){
        if(!n) return;
        swap(n->left, n->right);
        mirror(n->left.get());
        mirror(n->right.get());
    }

    /* Remove Nó e devolve ponteiro da (sub)raiz resultante */
    static unique_ptr<Node> remove(unique_ptr<Node> node, const T& key)
    {
        if (!node) return nullptr;

        if      (key < node->key) node->left  = remove(move(node->left),  key);
        else if (key > node->key) node->right = remove(move(node->right), key);
        else {
            /* nó com 0 ou 1 filho */
            if (!node->left)  return move(node->right);
            if (!node->right) return move(node->left);

            /* dois filhos: pega sucessor em ordem */
            Node* succ = node->right.get();
            while (succ->left) succ = succ->left.get();
            node->key = succ->key;
            node->right = remove(move(node->right), succ->key);
        }
        return node;
    }

public:
    /* ------------ interface pública ----------------------------- */

    bool insert(const T& key)
    {
        Node* parent = nullptr;
        Node* curr   = root.get();

        while (curr) {
            if (key == curr->key) 
            return false;        // duplicado
            parent = curr;
            curr   = (key < curr->key) ? curr->left.get() : curr->right.get();
        }

        auto newNode = make_unique<Node>(key);

        if (!parent)          root = move(newNode);
        else if (key < parent->key) parent->left  = move(newNode);
        else                        parent->right = move(newNode);

        return true;
    }

    const Node* find(const T& key) const
    {
        Node* curr = root.get();
        while (curr) {
            if      (key < curr->key) curr = curr->left.get();
            else if (key > curr->key) curr = curr->right.get();
            else                      return curr;
        }
        return nullptr;
    }

    bool remove(const T& key) { 
        root = remove(move(root), key); 
        return true; 
    }

    /* percursos e utilidades */
    void print_inorder()  const { 
        inorder (root.get());  
        cout<<'\n'; 
    }

    void print_preorder() const { 
        preorder(root.get());  
        cout<<'\n'; 
    }

    void print_postorder()const { 
        postorder(root.get()); 
        cout<<'\n'; 
    }

    int  height() const  { 
        return height(root.get()); 
    }

    int  count () const  { 
        return count (root.get()); 
    }

    void mirror()        { 
        mirror(root.get()); 
    }
    
};
