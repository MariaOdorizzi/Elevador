#include "Classes/Elevador.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;


// Limpa a tela do terminal
void limparTelaElevador() {

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Inicializa elevador
Elevador::Elevador(int capacidade) {

    this->capacidade = capacidade;

    andarAtual = 0;

    estado = PARADO;

    estrategia = nullptr;
}

// Retorna andar atual
int Elevador::getAndarAtual() {

    return andarAtual;
}

// Define andar atual
void Elevador::setAndarAtual(int andar) {

    andarAtual = andar;
}

// Define estrategia
void Elevador::setEstrategia(
    EstrategiaElevador* estrategia
) {

    this->estrategia = estrategia;
}

// Move elevador
void Elevador::mover() {

    andarAtual++;
}

// Move ate um andar especifico, animando a movimentacao
void Elevador::moverPara(
    int destino
) {

    int origem = andarAtual;

    while(andarAtual != destino) {

        if(andarAtual < destino) {
            estado = SUBINDO;
            andarAtual++;
        } else {
            estado = DESCENDO;
            andarAtual--;
        }

        limparTelaElevador();

        mostrarMovimento(
            origem,
            andarAtual
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(400)
        );
    }

    estado = PARADO;
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

// Executa FIFO
void Elevador::executarFIFO() {

    mostrarCabecalho("FIFO");

    for(int andar : chamadas) {

        int origem = andarAtual;

        if(andar > andarAtual)
            estado = SUBINDO;
        else if(andar < andarAtual)
            estado = DESCENDO;
        else
            estado = PARADO;

        andarAtual = andar;

        mostrarMovimento(
            origem,
            andarAtual
        );
    }

    cout << endl;

    cout << "Movimentos: "
         << calcularMovimentos(
                chamadas
            )
         << endl;

    estado = PARADO;
}

// Executa SCAN
void Elevador::executarSCAN() {

    mostrarCabecalho("SCAN");

    vector<int> acima;
    vector<int> abaixo;

    for(int chamada : chamadas) {

        if(chamada >= andarAtual)
            acima.push_back(chamada);
        else
            abaixo.push_back(chamada);
    }

    sort(
        acima.begin(),
        acima.end()
    );

    sort(
        abaixo.begin(),
        abaixo.end(),
        greater<int>()
    );

    vector<int> ordem;

    for(int andar : acima) {

        int origem = andarAtual;

        if(andar > andarAtual)
            estado = SUBINDO;
        else
            estado = PARADO;

        andarAtual = andar;

        ordem.push_back(
            andar
        );

        mostrarMovimento(
            origem,
            andarAtual
        );
    }

    for(int andar : abaixo) {

        int origem = andarAtual;

        if(andar < andarAtual)
            estado = DESCENDO;
        else
            estado = PARADO;

        andarAtual = andar;

        ordem.push_back(
            andar
        );

        mostrarMovimento(
            origem,
            andarAtual
        );
    }

    cout << endl;

    cout << "Movimentos: "
         << calcularMovimentos(
                ordem
            )
         << endl;

    estado = PARADO;
}

// Executa menor distancia
void Elevador::executarMenorDistancia() {

    mostrarCabecalho(
        "MENOR DISTANCIA"
    );

    vector<int> restantes = chamadas;

    vector<int> ordem;

    while(!restantes.empty()) {

        int melhorIndice = 0;

        int menorDistancia =
            abs(
                restantes[0] - andarAtual
            );

        for(
            int i = 1;
            i < restantes.size();
            i++
        ) {

            int distancia =
                abs(
                    restantes[i] - andarAtual
                );

            if(distancia < menorDistancia) {

                menorDistancia = distancia;

                melhorIndice = i;
            }
        }

        int proximo =
            restantes[melhorIndice];

        int origem = andarAtual;

        if(proximo > andarAtual)
            estado = SUBINDO;
        else if(proximo < andarAtual)
            estado = DESCENDO;
        else
            estado = PARADO;

        andarAtual = proximo;

        ordem.push_back(
            proximo
        );

        mostrarMovimento(
            origem,
            andarAtual
        );

        restantes.erase(
            restantes.begin()
            + melhorIndice
        );
    }

    cout << endl;

    cout << "Movimentos: "
         << calcularMovimentos(
                ordem
            )
         << endl;

    estado = PARADO;
}

// Executa estrategia atual
void Elevador::executar() {

    if(estrategia == nullptr) {

        cout << "Estrategia nao definida"
             << endl;

        return;
    }

    vector<int> ordem =
        estrategia->organizar(
            chamadas,
            andarAtual
        );

    for(int andar : ordem) {

        int origem = andarAtual;

        if(andar > andarAtual)
            estado = SUBINDO;
        else if(andar < andarAtual)
            estado = DESCENDO;
        else
            estado = PARADO;

        andarAtual = andar;

        mostrarMovimento(
            origem,
            andarAtual
        );
    }

    cout << endl;

    cout << "Movimentos: "
         << calcularMovimentos(
                ordem
            )
         << endl;

    estado = PARADO;
}

// Calcula movimentos totais
int Elevador::calcularMovimentos(
    vector<int> ordem
) {

    int atual = 0;

    int total = 0;

    for(int andar : ordem) {

        total += abs(
            andar - atual
        );

        atual = andar;
    }

    return total;
}