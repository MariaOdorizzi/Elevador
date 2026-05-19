#include <iostream>
#include <vector>


using namespace std;

// Imprime lista
void imprimirLista(
    vector<int> lista
) {

    for(int valor : lista) {

        cout << valor << " ";
    }
}

// Imprime linha elevador
void imprimirLinha(
    int andar,
    int posicao
) {

    if(andar == posicao) {

        cout << "[" << andar << "] | E |";

    } else {

        cout << "[" << andar << "] |   |";
    }
}

// Mostra comparacao
void mostrarComparacao(

    vector<int> fifo,
    vector<int> scan,
    vector<int> menor,

    int posFIFO,
    int posSCAN,
    int posMenor
) {

    cout << endl;

    cout << "================================================================================"
         << endl;

    cout << "FIFO                    "
         << "SCAN                    "
         << "MENOR DISTANCIA"
         << endl;

    cout << "================================================================================"
         << endl;

    cout << endl;

    // Estados
    cout << "Estado: SUBINDO         ";
    cout << "Estado: SUBINDO         ";
    cout << "Estado: SUBINDO         ";
    cout << endl;

    cout << endl;

    // Chamadas
    cout << "Chamadas:               ";
    cout << "Chamadas:               ";
    cout << "Chamadas:";
    cout << endl;

    imprimirLista(fifo);

    cout << "            ";

    imprimirLista(scan);

    cout << "            ";

    imprimirLista(menor);

    cout << endl << endl;

    // Desenha predio
    for(int andar = 8; andar >= 0; andar--) {

        imprimirLinha(
            andar,
            posFIFO
        );

        cout << "      ";
        cout << "      ";

        imprimirLinha(
            andar,
            posSCAN
        );

        cout << "      ";
        cout << "      ";

        imprimirLinha(
            andar,
            posMenor
        );

        cout << endl;
    }

    cout << "================================================================================"
         << endl;
}

int main() {

    // FIFO
    vector<int> fifo = {4, 1, 6, 2, 8};

    // SCAN
    vector<int> scan = {1, 2, 4, 6, 8};

    // MENOR DISTANCIA
    vector<int> menor = {1, 2, 4, 6, 8};

    // Posicoes atuais
    int posFIFO = 6;

    int posSCAN = 2;

    int posMenor = 8;

    // Exibe comparacao
    mostrarComparacao(

        fifo,
        scan,
        menor,

        posFIFO,
        posSCAN,
        posMenor
    );

    return 0;
}