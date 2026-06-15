#ifndef FIFO_H
#define FIFO_H

#include "EstrategiaElevador.h"

// Estrategia FIFO
class FIFO : public EstrategiaElevador {

public:

    vector<int> organizar(
        vector<int> chamadas,
        int andarAtual
    ) override {

        return chamadas;
    }
};

#endif