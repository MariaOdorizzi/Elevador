#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Calcula quantidade de movimentos
int calcularMovimentos(
    vector<int> chamadas
) {

    int posicao = 0;
    int movimentos = 0;

    for(int chamada : chamadas) {

        movimentos += abs(
            chamada - posicao
        );

        posicao = chamada;
    }

    return movimentos;
}

// Imprime percurso
void imprimirPercurso(
    vector<int> chamadas
) {

    cout << "0";

    for(int chamada : chamadas) {

        cout << " -> "
             << chamada;
    }
}

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
    int posMenor,

    string estadoFIFO,
    string estadoSCAN,
    string estadoMenor,

    int movFIFO,
    int movSCAN,
    int movMenor
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
    cout << "Estado: "
         << estadoFIFO;

    cout << "         ";

    cout << "Estado: "
         << estadoSCAN;

    cout << "         ";

    cout << "Estado: "
         << estadoMenor;

    cout << endl << endl;

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

    // Movimentos
    cout << "Movimentos: "
         << movFIFO;

    cout << "      ";

    cout << "Movimentos: "
         << movSCAN;

    cout << "      ";

    cout << "Movimentos: "
         << movMenor;

    cout << endl << endl;

    // Percursos
    cout << "FIFO: ";
    imprimirPercurso(fifo);

    cout << endl;

    cout << "SCAN: ";
    imprimirPercurso(scan);

    cout << endl;

    cout << "MENOR: ";
    imprimirPercurso(menor);

    cout << endl << endl;

    // Desenha predio
    for(int andar = 8; andar >= 0; andar--) {

        imprimirLinha(
            andar,
            posFIFO
        );

        cout << "            ";

        imprimirLinha(
            andar,
            posSCAN
        );

        cout << "            ";

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
    vector<int> fifo = {
        4, 1, 6, 2, 8
    };

    // SCAN
    vector<int> scan = {
        1, 2, 4, 6, 8
    };

    // Menor Distancia
    vector<int> menor = {
        1, 2, 4, 6, 8
    };

    // Posicoes finais
    int posFIFO = fifo.back();
    int posSCAN = scan.back();
    int posMenor = menor.back();

    // Estados
    string estadoFIFO = "PARADO";
    string estadoSCAN = "PARADO";
    string estadoMenor = "PARADO";

    // Movimentos calculados
    int movFIFO =
        calcularMovimentos(fifo);

    int movSCAN =
        calcularMovimentos(scan);

    int movMenor =
        calcularMovimentos(menor);

    // Exibe comparacao
    mostrarComparacao(

        fifo,
        scan,
        menor,

        posFIFO,
        posSCAN,
        posMenor,

        estadoFIFO,
        estadoSCAN,
        estadoMenor,

        movFIFO,
        movSCAN,
        movMenor
    );

    return 0;
}