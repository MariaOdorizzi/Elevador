#ifndef ANDAR_H
#define ANDAR_H

#include <vector>
#include "Pessoa.h"

using namespace std;

class Andar {
private:
    int numero;
    vector<Pessoa> fila;

public:
    Andar(int numero) {
        this->numero = numero;
    }

    int getNumero() {
        return numero;
    }

    void adicionarPessoa(Pessoa p) {
        fila.push_back(p);
    }

    int quantidadePessoas() {
        return fila.size();
    }

};

#endif