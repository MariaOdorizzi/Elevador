#ifndef ANDAR_H
#define ANDAR_H

#include <vector>

#include "Pessoa.h"

using namespace std;

class Andar {

private:

    // Numero do andar
    int numero;

    // Pessoas esperando
    vector<Pessoa> pessoas;

public:

    // Construtor
    Andar(int numero);

    // Adiciona pessoa
    void adicionarPessoa(Pessoa pessoa);

    // Retorna pessoas
    vector<Pessoa>& getPessoas();

    // Verifica vazio
    bool vazio();

    // Remove pessoa
    Pessoa removerPessoa();
};

#endif