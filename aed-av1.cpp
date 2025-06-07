#include <iostream>
using namespace std;

bool pertenceDialeto(const string& s) {
    int n = s.size();

    // Regra 1: tamanho deve ser ímpar
    if (n % 2 == 0) 
    return false;

    int meio = n / 2;

    // Regra 2: letra do meio deve ser 'e'
    if (s[meio] != 'e') 
    return false;

    // Verificando os lados da letra 'e'
    int esquerda = meio - 1;
    int direita = meio + 1;

    while (esquerda >= 0 && direita < n) {
        char letraEsquerda = s[esquerda];
        char letraDireita = s[direita];

        // Regra 3: letras devem ser iguais
        if (letraEsquerda != letraDireita) 
        return false;

        // Regra 4: letras só podem ser 'd' ou 'f'
        if (letraEsquerda != 'd' && letraEsquerda != 'f') 
        return false;

        // Passa para o próximo par
        esquerda--;
        direita++;
    }

    return true;
}

int main() {
    string palavra;
    cout << "Digite uma palavra: ";
    cin >> palavra;

    if (pertenceDialeto(palavra))
        cout << "SIM\n";
    else
        cout << "NAO\n";

    return 0;
}
