#ifndef ESTRATEGIA_ELEVADOR_H
#define ESTRATEGIA_ELEVADOR_H

#include <vector>

using namespace std;

// Interface das estrategias
class EstrategiaElevador {

public:

    // Organiza chamadas
    virtual vector<int> organizar(
        vector<int> chamadas,
        int andarAtual
    ) = 0;

    virtual ~EstrategiaElevador() {}
};

#endif