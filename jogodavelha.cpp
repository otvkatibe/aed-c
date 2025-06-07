#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<vector<string>> jogo(3, vector<string>(3, " "));

    string jogador = "X"; // Jogador atual
    int linha, coluna;

    while (true) {
        // Exibe o tabuleiro
        cout << "Tabuleiro:\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << jogo[i][j] << " ";
            }
            cout << endl;
        }

        // Solicita a jogada do jogador
        cout << "Jogador " << jogador << ", escolha uma linha (0-2) e uma coluna (0-2): ";
        cin >> linha >> coluna;

        // Verifica se a jogada é válida
        if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || jogo[linha][coluna] != " ") {
            cout << "Jogada inválida! Tente novamente.\n";
            continue;
        }

        // Marca a jogada no tabuleiro
        jogo[linha][coluna] = jogador;

        // Verifica se o jogador venceu
        for (int i = 0; i < 3; i++) {
            if ((jogo[i][0] == jogador && jogo[i][1] == jogador && jogo[i][2] == jogador) ||
                (jogo[0][i] == jogador && jogo[1][i] == jogador && jogo[2][i] == jogador)) {
                cout << "Jogador " << jogador << " venceu!\n";
                return 0;
            }
        }
        if ((jogo[0][0] == jogador && jogo[1][1] == jogador && jogo[2][2] == jogador) ||
            (jogo[0][2] == jogador && jogo[1][1] == jogador && jogo[2][0] == jogador)) {
            cout << "Jogador " << jogador << " venceu!\n";
            return 0;
        }

        // Troca de jogador
        jogador = (jogador == "X") ? "O" : "X";
    }

    return 0;
}