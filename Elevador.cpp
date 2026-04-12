#include "Elevador.h"
#include <iostream>

Elevador::Elevador() {
    andarAtual = 0;
}

void Elevador::subir() {
    andarAtual++;
    std::cout << "Elevador subiu para o andar " << andarAtual << "\n";
}

void Elevador::descer() {
    andarAtual--;
    std::cout << "Elevador desceu para o andar " << andarAtual << "\n";
}

int Elevador::getAndarAtual() {
    return andarAtual;
}