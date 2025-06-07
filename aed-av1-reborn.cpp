#include <array>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

constexpr int N    = 7;
constexpr int ALVO = 10;

using Grade  = array<array<int,N>,N>;
using Ponto  = pair<int,int>;
using Caminho= vector<Ponto>;

static const Grade grade {{
    {0, 1, 2, 4, 5, 8, 9},
    {1, 1, 7, 8, 2, 5, 9},
    {2, 4, 6, 5, 1, 3, 1},
    {3, 2, 1, 4, 3, 9, 8},
    {10,2, 1, 5, 8, 4, 9},
    {8, 9, 5, 4, 2, 1,10},
    {5, 2, 3, 1, 5, 6, 7}
}};

constexpr array<int,4> DR{ 1,-1, 0, 0 };
constexpr array<int,4> DC{ 0, 0, 1,-1 };

bool dfs(int r, int c,
         int soma,
         array<array<bool,N>,N>& vis,
         Caminho& cam)
{
    if (r < 0 || r >= N || c < 0 || c >= N || vis[r][c]) 
    return false;

    soma += grade[r][c];
    if (soma > ALVO) 
    return false;

    vis[r][c] = true;
    cam.emplace_back(r,c);

    if (soma == ALVO && cam.size() >= 3) 
    return true;

    for (int k = 0; k < 4; ++k)
        if (dfs(r+DR[k], c+DC[k], soma, vis, cam))
            return true;

    vis[r][c] = false;
    cam.pop_back();
    return false;
}

int main() {
    array<array<bool,N>,N> vis{};
    Caminho cam;
    cam.reserve(N*N);

    if (dfs(1,1,0,vis,cam)) {
        cout << "Caminho com soma " << ALVO << ":\n";
        for (size_t i = 0; i < cam.size(); ++i) {
            auto [r,c] = cam[i];
            cout << '(' << r << ',' << c << ')';
            if (i+1 < cam.size()) cout << " -> ";
        }
        cout << '\n';
    } else {
        cout << "Nenhum caminho encontrado.\n";
    }
}
