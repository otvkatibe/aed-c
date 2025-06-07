#include <stdio.h>
#include <stdbool.h>

#define N 7

int grid[N][N] = {
    {0,1,2,4,5,8,9},
    {1,1,7,8,2,5,9},
    {2,4,6,5,1,3,1},
    {3,2,1,4,3,9,8},
    {10,2,1,5,8,4,9},
    {8,9,5,4,2,1,10},
    {5,2,3,1,5,6,7}
};

typedef struct { int x, y; } Point;

const int DX[4] = { 1,-1, 0, 0 };
const int DY[4] = { 0, 0, 1,-1 };

bool dfs(int x, int y,
         int soma, int alvo,
         bool visited[N][N],
         Point path[], int *tam)
{
    if (x < 0 || x >= N || y < 0 || y >= N)    
    return false;

    if (visited[x][y])                         
    return false;
    
    soma += grid[x][y];
    if (soma > alvo)                          
    return false;   

    path[(*tam)++] = (Point){x, y};
    visited[x][y] = true;

    if (soma == alvo && *tam >= 3)  return true;

    for (int k = 0; k < 4; ++k)
        if (dfs(x + DX[k], y + DY[k], soma, alvo, visited, path, tam))
            return true;   

    visited[x][y] = false;
    --(*tam);
    return false;
}

int main(void)
{
    const int alvo = 10;

    bool visited[N][N] = { false };
    Point path[N*N];
    int tam = 0;

    if (dfs(0, 0, 0, alvo, visited, path, &tam)) {
        printf("Caminho encontrado (soma = %d): ", alvo);
        for (int i = 0; i < tam; ++i) {
            printf("(%d,%d)", path[i].x, path[i].y);
            if (i < tam-1) printf(" -> ");
        }
        putchar('\n');
    } else {
        puts("Nenhum caminho válido encontrado.");
    }
    return 0;
}
