#ifndef ELEVADOR_H
#define ELEVADOR_H

#include <vector>
#include "Pessoa.h"

using namespace std;

class Elevador {
private:
    int id;
    int andarAtual;
    int capacidade;
    vector<Pessoa> pessoas;

public:
    Elevador(int id) {
        this->id = id;
        andarAtual = 0;
        capacidade = 5;
    }

    int getAndarAtual() {
        return andarAtual;
    }

    void subir() {
        andarAtual++;
    }

    void descer() {
        andarAtual--;
    }

    void entrarPessoa(Pessoa p) {
        if (pessoas.size() < capacidade) {
            pessoas.push_back(p);
        }
    }

    void status() {
        cout << "Elevador " << id << " no andar " << andarAtual << endl;
        cout << "Pessoas dentro: " << pessoas.size() << endl;
    }

    // TODO: remover pessoas no andar correto
};

#endif