#ifndef PREDIO_H
#define PREDIO_H

#include "Elevador.h"
#include "Pessoa.h"

class Predio {

private:
    int totalAndares;
    Elevador elevador;

public:
    Predio(int andares);

    void iniciarSimulacao();
};

#endif