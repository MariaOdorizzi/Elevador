#ifndef SCAN_H
#define SCAN_H

#include <algorithm>

#include "EstrategiaElevador.h"

using namespace std;

// Estrategia SCAN
class SCAN : public EstrategiaElevador {

public:

    vector<int> organizar(
        vector<int> chamadas,
        int andarAtual
    ) override {

        vector<int> acima;
        vector<int> abaixo;

        for(int andar : chamadas) {

            if(andar >= andarAtual)
                acima.push_back(andar);
            else
                abaixo.push_back(andar);
        }

        sort(
            acima.begin(),
            acima.end()
        );

        sort(
            abaixo.begin(),
            abaixo.end(),
            greater<int>()
        );

        vector<int> resultado;

        resultado.insert(
            resultado.end(),
            acima.begin(),
            acima.end()
        );

        resultado.insert(
            resultado.end(),
            abaixo.begin(),
            abaixo.end()
        );

        return resultado;
    }
};

#endif