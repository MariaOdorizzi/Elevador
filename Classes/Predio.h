#ifndef PREDIO_H
#define PREDIO_H

#include <vector>

#include "Andar.h"
#include "Elevador.h"
#include "Pessoa.h"

using namespace std;

class Predio {

private:

    // Lista de andares
    vector<Andar> andares;

    // Elevador principal
    Elevador elevador;

public:

    // Construtor
    Predio(int quantidadeAndares);

    // Adiciona pessoa
    void adicionarPessoa(
        Pessoa pessoa
    );

    // Simula sistema
    void simular();
};

#endif