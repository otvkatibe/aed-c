#include <stdio.h>
#include "bst_c.h"       

int main(void)
{
    bst_tree t = bst_create();          /* cria árvore vazia */

    /* insere os nós */
    int v[] = { 1, 3, 8, 6, 4, 7, 10, 14, 13 };
    for (size_t i = 0; i < sizeof v/sizeof v[0]; ++i)
        bst_insert(&t, v[i]);

    puts("Arvore (preordem) antes da troca:");
    bst_preorder(t);   putchar('\n');

    bst_mirror(t);                     /* troca esq ↔ dir */

    puts("\nArvore (preordem) depois da troca:");
    bst_preorder(t);   putchar('\n');

    bst_destroy(&t);                   /* libera memória */
    return 0;
}
