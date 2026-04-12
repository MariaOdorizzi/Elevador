#ifndef PESSOA_H
#define PESSOA_H

class Pessoa {
private:
    int id;
    int andarAtual;
    int andarDestino;
    bool dentroElevador;

public:
    Pessoa(int id, int atual, int destino) {
        this->id = id;
        andarAtual = atual;
        andarDestino = destino;
        dentroElevador = false;
    }

    int getId() { return id; }
    int getAndarAtual() { return andarAtual; }
    int getAndarDestino() { return andarDestino; }

    void entrarElevador() {
        dentroElevador = true;
    }

    void sairElevador() {
        dentroElevador = false;
        andarAtual = andarDestino;
    }
};

#endif