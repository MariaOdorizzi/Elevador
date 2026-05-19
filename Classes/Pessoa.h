#ifndef PESSOA_H
#define PESSOA_H

class Pessoa {
private:
    int id;
    int andarAtual;
    int andarDestino;
    bool dentroElevador;

public:
    // Cria pessoa
    Pessoa(int id, int atual, int destino);

    // Retorna id
    int getId();

    // Retorna andar atual
    int getAndarAtual();

    // Retorna destino
    int getAndarDestino();

    // Marca entrada
    void entrarElevador();

    // Marca saída
    void sairElevador();

    // Verifica elevador
    bool estaNoElevador();
};

#endif