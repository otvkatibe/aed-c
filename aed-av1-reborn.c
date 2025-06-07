#include <stdio.h>
#include <stdbool.h>

#define N 7
#define ALVO 10

static const int grade[N][N] = {
    {0, 1, 2, 4, 5, 8, 9},
    {1, 1, 7, 8, 2, 5, 9},
    {2, 4, 6, 5, 1, 3, 1},
    {3, 2, 1, 4, 3, 9, 8},
    {10,2, 1, 5, 8, 4, 9},
    {8, 9, 5, 4, 2, 1,10},
    {5, 2, 3, 1, 5, 6, 7}
};

typedef struct { int r, c; } Ponto;
static const int DR[4] = { 1,-1, 0, 0 };
static const int DC[4] = { 0, 0, 1,-1 };

static bool dfs(int r, int c,
                int soma,
                bool visit[N][N],
                Ponto caminho[], int *tam)
{
    if (r < 0 || r >= N || c < 0 || c >= N || visit[r][c])
        return false;

    soma += grade[r][c];
    if (soma > ALVO) return false;          

    caminho[(*tam)++] = (Ponto){r,c};
    visit[r][c] = true;

    if (soma == ALVO && *tam >= 3)        
        return true;

    for (int k = 0; k < 4; ++k)
        if (dfs(r+DR[k], c+DC[k], soma, visit, caminho, tam))
            return true;

    visit[r][c] = false;
    --(*tam);
    return false;
}

static void imprime_caminho(const Ponto caminho[], int n)
{
    for (int i = 0; i < n; ++i) {
        printf("(%d,%d)", caminho[i].r, caminho[i].c);
        if (i+1 < n) printf(" -> ");
    }
    putchar('\n');
}

int main(void)
{
    bool visit[N][N] = { false };
    Ponto caminho[N*N];
    int tam = 0;

    if (dfs(1,1,0,visit,caminho,&tam)) {
        printf("Caminho encontrado (soma = %d):\n", ALVO);
        imprime_caminho(caminho, tam);
    } else {
        puts("Nenhum caminho encontrado.");
    }
    return 0;
}
