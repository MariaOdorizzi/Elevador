#include "Classes/Elevador.h"

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

// Inicializa elevador
Elevador::Elevador(int capacidade) {

    this->capacidade = capacidade;

    andarAtual = 0;

    estado = PARADO;
}

// Retorna andar atual
int Elevador::getAndarAtual() {

    return andarAtual;
}

// Define andar atual
void Elevador::setAndarAtual(int andar) {

    andarAtual = andar;
}

// Move elevador
void Elevador::mover() {

    andarAtual++;
}

// Embarca pessoas
void Elevador::embarcar(
    Andar &andar
) {

    while(
        !andar.vazio()
        && pessoas.size() < capacidade
    ) {

        pessoas.push_back(
            andar.removerPessoa()
        );
    }
}

// Desembarca pessoas
void Elevador::desembarcar() {

    vector<Pessoa> restantes;

    for(Pessoa p : pessoas) {

        if(
            p.getAndarDestino()
            != andarAtual
        ) {

            restantes.push_back(p);
        }
    }

    pessoas = restantes;
}

// Verifica vazio
bool Elevador::vazio() {

    return pessoas.empty();
}

// Adiciona chamada
void Elevador::adicionarChamada(
    int andar
) {

    chamadas.push_back(andar);
}

// Retorna estado em texto
string Elevador::getEstadoTexto() {

    switch(estado) {

        case SUBINDO:
            return "SUBINDO";

        case DESCENDO:
            return "DESCENDO";

        default:
            return "PARADO";
    }
}

// Mostra cabecalho
void Elevador::mostrarCabecalho(
    string algoritmo
) {

    cout << endl;

    cout << "========================"
         << endl;

    cout << "ALGORITMO: "
         << algoritmo
         << endl;

    cout << "========================"
         << endl;
}

// Mostra movimento
void Elevador::mostrarMovimento(
    int origem,
    int destino
) {

    cout << endl;

    cout << "Estado: "
         << getEstadoTexto()
         << endl;

    cout << origem
         << " -> "
         << destino
         << endl;

    // Desenha predio
    for(int i = 8; i >= 0; i--) {

        // Mostra elevador
        if(i == destino) {

            cout << "["
                 << i
                 << "] | E |"
                 << endl;

        } else {

            cout << "["
                 << i
                 << "] |   |"
                 << endl;
        }
    }
}

// Executa FIFO: First In, First Out - Primeiro que entra, primeiro que sai
void Elevador::executarFIFO() {

    mostrarCabecalho("FIFO");

    // Percorre chamadas
    for(int andar : chamadas) {

        int origem = andarAtual;

        // Atualiza estado
        if(andar > andarAtual)
            estado = SUBINDO;
        else
            estado = DESCENDO;

        // Move elevador
        andarAtual = andar;

        // Mostra resultado
        mostrarMovimento(
            origem,
            andarAtual
        );
    }

    estado = PARADO;
}

// Executa SCAN: Atende por direção; varrer, examinar ou percorrer procurando algo.
void Elevador::executarSCAN() {

    mostrarCabecalho("SCAN");

    // Copia fila
    vector<int> fila = chamadas;

    // Ordena fila
    sort(
        fila.begin(),
        fila.end()
    );

    // Percorre fila
    for(int andar : fila) {

        int origem = andarAtual;

        estado = SUBINDO;

        // Atualiza andar
        andarAtual = andar;

        // Mostra resultado
        mostrarMovimento(
            origem,
            andarAtual
        );
    }

    estado = PARADO;
}

// Executa menor distancia
void Elevador::executarMenorDistancia() {

    mostrarCabecalho(
        "MENOR DISTANCIA"
    );

    // Copia chamadas
    vector<int> restantes = chamadas;

    // Continua ate acabar
    while(!restantes.empty()) {

        int melhorIndice = 0;

        // Primeira distancia
        int menorDistancia =
            abs(
                restantes[0] - andarAtual
            );

        // Busca menor distancia
        for(
            int i = 1;
            i < restantes.size();
            i++
        ) {

            int distancia =
                abs(
                    restantes[i]
                    - andarAtual
                );

            // Atualiza menor distancia
            if(
                distancia < menorDistancia
            ) {

                menorDistancia = distancia;

                melhorIndice = i;
            }
        }

        // Define proximo andar
        int proximo =
            restantes[melhorIndice];

        int origem = andarAtual;

        // Atualiza estado
        if(proximo > andarAtual)
            estado = SUBINDO;
        else
            estado = DESCENDO;

        // Atualiza andar
        andarAtual = proximo;

        // Mostra resultado
        mostrarMovimento(
            origem,
            andarAtual
        );

        // Remove chamada
        restantes.erase(
            restantes.begin()
            + melhorIndice
        );
    }

    estado = PARADO;
}