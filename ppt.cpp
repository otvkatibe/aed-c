#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    string jogador;
    string adversario;
    int pontos_jogador = 0;
    int pontos_adversario = 0;

    srand((unsigned int) time(NULL));

    string ppt[3] = {"pedra", "papel", "tesoura"};

    while (true) {
        cout << "pedra, papel ou tesoura?:";
        getline(cin, jogador);

        if (jogador != "pedra" && jogador != "papel" && jogador != "tesoura") {
            cout << "jogo acabou" << endl;
            break;
        }
        adversario = ppt[rand() % 3];
        cout << "Adversario jogou: " << adversario << endl;

        if (jogador == adversario){
            cout << "Empate!" << endl;
        }
        else if (jogador == "pedra"){
            if (adversario == "tesoura") {
                cout << "Jogador venceu a rodada!" << endl;
                pontos_jogador++;
            }
            else if (adversario == "papel") {
                cout << "Adversario venceu a rodada!" << endl;
                pontos_adversario++;
            }
        }
        else if (jogador == "papel") {
            if (adversario == "pedra") {
                cout << "Jogador venceu a rodada!" << endl;
                pontos_jogador++;
            }
            else if (adversario == "tesoura") {
                cout << "Adversario venceu a rodada!" << endl;
                pontos_adversario++;
            }
        }
        else if (jogador == "tesoura") {
            if (adversario == "papel") {
                cout << "Jogador venceu a rodada!" << endl;
                pontos_jogador++;
            }
            else if (adversario == "pedra") {
                cout << "Adversario venceu a rodada!" << endl;
                pontos_adversario++;
            }
        }
        cout << "Pontos do jogador: " << pontos_jogador << endl;
        cout << "Pontos do adversario: " << pontos_adversario << endl;
    }
    cout << "jogador: " << pontos_jogador << "adversario: " << pontos_adversario << endl;
    if (pontos_jogador > pontos_adversario) {
        cout << "Jogador venceu!" << endl;
    } else if (pontos_jogador < pontos_adversario) {
        cout << "Adversario venceu!" << endl;
    } else {
        cout << "Empate!" << endl;
    } 
}