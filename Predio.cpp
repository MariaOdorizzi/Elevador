#include "Classes/Predio.h"

#include <iostream>

using namespace std;

// Inicializa predio
Predio::Predio(
    int quantidadeAndares
)
: elevador(5)
{

    // Cria andares
    for(
        int i = 0;
        i < quantidadeAndares;
        i++
    ) {

        andares.push_back(
            Andar(i)
        );
    }
}

// Adiciona pessoa
void Predio::adicionarPessoa(
    Pessoa pessoa
) {

    int andar =
        pessoa.getAndarAtual();

    andares[andar]
        .adicionarPessoa(pessoa);

    // Adiciona chamada
    elevador.adicionarChamada(
        andar
    );

    cout
        << "Pessoa "
        << pessoa.getId()
        << " chamou no andar "
        << andar
        << endl;
}

// Simula sistema
void Predio::simular() {

    cout << endl;

    cout << "===================="
         << endl;

    cout << "SIMULADOR"
         << endl;

    cout << "===================="
         << endl;

    // Executa FIFO
    elevador.executarFIFO();

    // Executa SCAN
    elevador.executarSCAN();

    // Executa menor distancia
    elevador.executarMenorDistancia();
}