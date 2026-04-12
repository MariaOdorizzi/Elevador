#include "Predio.h"
#include <iostream>

void moverElevador(Elevador &elevador, int destino) {

    if (elevador.getAndarAtual() < destino) {
        std::cout << "Elevador vai subir\n";
        while (elevador.getAndarAtual() < destino) {
            elevador.subir();
        }
    } else if (elevador.getAndarAtual() > destino) {
        std::cout << "Elevador vai descer\n";
        while (elevador.getAndarAtual() > destino) {
            elevador.descer();
        }
    } else {
        std::cout << "Elevador ja esta no andar " << destino << "\n";
    }
}

Predio::Predio(int andares) {
    totalAndares = andares;
}

void Predio::iniciarSimulacao() {

    std::cout << "Simulacao iniciada!\n";

    Pessoa p1(1, 0, 5);

    p1.chamarElevador();

    // elevador vai até a pessoa
    moverElevador(elevador, p1.getAndarAtual());

    p1.entrarElevador();

    // elevador leva até o destino
    moverElevador(elevador, p1.getDestino());

    p1.sairElevador();

    std::cout << "Simulacao finalizada!\n";
}