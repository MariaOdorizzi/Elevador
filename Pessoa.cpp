#include "Pessoa.h"
#include <iostream>

Pessoa::Pessoa(int id, int atual, int destino) {
    this->id = id;
    andarAtual = atual;
    andarDestino = destino;
    dentroElevador = false;
}

int Pessoa::getAndarAtual() {
    return andarAtual;
}

int Pessoa::getDestino() {
    return andarDestino;
}

bool Pessoa::estaNoElevador() {
    return dentroElevador;
}

void Pessoa::chamarElevador() {
    std::cout << "Pessoa " << id << " chamou o elevador no andar " << andarAtual << "\n";
}

void Pessoa::entrarElevador() {
    dentroElevador = true;
    std::cout << "Pessoa " << id << " entrou no elevador\n";
}

void Pessoa::sairElevador() {
    dentroElevador = false;
    std::cout << "Pessoa " << id << " saiu no andar " << andarDestino << "\n";
}