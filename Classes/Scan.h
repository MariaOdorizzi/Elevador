#ifndef SCAN_H
#define SCAN_H

#include <algorithm>
#include <vector>
#include "EstrategiaElevador.h"

using namespace std;

class SCAN : public EstrategiaElevador {

private:
    enum { ANDAR_MAXIMO = 8 };

public:

    vector<int> organizar(vector<int> chamadas, int andarAtual) override {

        vector<int> acima;
        vector<int> abaixo;
        vector<int> resultado;

        for(int andar : chamadas) {
            if(andar >= andarAtual)
                acima.push_back(andar);
            else
                abaixo.push_back(andar);
        }

        sort(acima.begin(), acima.end());
        sort(abaixo.begin(), abaixo.end(), greater<int>());

        resultado.insert(resultado.end(), acima.begin(), acima.end());

        if(!abaixo.empty()) {
            if(resultado.empty() || resultado.back() != ANDAR_MAXIMO) {
                resultado.push_back(ANDAR_MAXIMO);
            }
        }

        resultado.insert(resultado.end(), abaixo.begin(), abaixo.end());

        return resultado;
    }
};

#endif