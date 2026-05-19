#include "Classes/Pessoa.h"

// Inicializa atributos
Pessoa::Pessoa(int id, int atual, int destino) {
    this->id = id;
    this->andarAtual = atual;
    this->andarDestino = destino;
    this->dentroElevador = false;
}

// Retorna id
int Pessoa::getId() {
    return id;
}

// Retorna andar atual
int Pessoa::getAndarAtual() {
    return andarAtual;
}

// Retorna destino
int Pessoa::getAndarDestino() {
    return andarDestino;
}

// Pessoa entra no elevador
void Pessoa::entrarElevador() {
    dentroElevador = true;
}

// Pessoa sai do elevador
void Pessoa::sairElevador() {
    dentroElevador = false;
}

// Verifica presença no elevador
bool Pessoa::estaNoElevador() {
    return dentroElevador;
}