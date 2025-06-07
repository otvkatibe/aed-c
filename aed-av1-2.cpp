#include <array>
#include <vector>
#include <iostream>

using namespace std;

constexpr int N = 7;
using Grid   = array<array<int, N>, N>;
using Point  = pair<int,int>;

const Grid grid {{
    {0,1,2,4,5,8,9},
    {1,1,7,8,2,5,9},
    {2,4,6,5,1,3,1},
    {3,2,1,4,3,9,8},
    {10,2,1,5,8,4,9},
    {8,9,5,4,2,1,10},
    {5,2,3,1,5,6,7}
}};

constexpr array<int,4> DX{ 1,-1, 0, 0 };
constexpr array<int,4> DY{ 0, 0, 1,-1 };

bool dfs(int x, int y,
         int soma, int alvo,
         array<array<bool,N>,N>& vis,
         vector<Point>& caminho)
{
    if (x < 0 || x >= N || y < 0 || y >= N || vis[x][y]) 
    return false;

    soma += grid[x][y];
    if (soma > alvo) 
    return false;

    vis[x][y] = true;
    caminho.emplace_back(x,y);

    if (soma == alvo && caminho.size() >= 3) 
    return true;

    for (int k = 0; k < 4; ++k)
        if (dfs(x+DX[k], y+DY[k], soma, alvo, vis, caminho))
            return true;

    vis[x][y] = false;
    caminho.pop_back();
    return false;
}

int main() {
    const int alvo = 10;

    array<array<bool,N>,N> vis{};
    vector<Point> caminho;
    caminho.reserve(N*N);

    if (dfs(0,0,0,alvo,vis,caminho)) {
        cout << "Caminho encontrado (soma = " << alvo << "): ";
        for (size_t i = 0; i < caminho.size(); ++i) {
            auto [x,y] = caminho[i];
            cout << '(' << x << ',' << y << ')';
            if (i+1 < caminho.size()) cout << " -> ";
        }
        cout << '\n';
    } else {
        cout << "Nenhum caminho válido encontrado.\n";
    }
}
