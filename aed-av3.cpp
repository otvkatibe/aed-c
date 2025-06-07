#include <iostream>
#include "bst_cpp.hpp"

int main()
{
    BST<int> tree;                     // árvore vazia

    int v[] = { 1, 3, 8, 6, 4, 7, 10, 14, 13 };
    for (int x : v) tree.insert(x);

    std::cout << "Arvore (preordem) antes da troca:\n";
    tree.print_preorder();             // método helper

    tree.mirror();                     // espelha

    std::cout << "\nArvore (preordem) depois da troca:\n";
    tree.print_preorder();

    /* destruição automática via unique_ptr */
    return 0;
}
