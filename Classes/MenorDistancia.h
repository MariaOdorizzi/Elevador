#ifndef MENOR_DISTANCIA_H
#define MENOR_DISTANCIA_H

#include <vector>
#include <cmath>

#include "EstrategiaElevador.h"

using namespace std;

// Estrategia menor distancia
class MenorDistancia : public EstrategiaElevador {

public:

    vector<int> organizar(
        vector<int> chamadas,
        int andarAtual
    ) override {

        vector<int> resultado;

        while (!chamadas.empty()) {

            size_t melhorIndice = 0;

            int menor = abs(chamadas[0] - andarAtual);

            for (size_t i = 1; i < chamadas.size(); i++) {

                int distancia = abs(chamadas[i] - andarAtual);

                if (distancia < menor) {
                    menor = distancia;
                    melhorIndice = i;
                }
            }

            resultado.push_back(chamadas[melhorIndice]);

            andarAtual = chamadas[melhorIndice];

            chamadas.erase(chamadas.begin() + melhorIndice);
        }

        return resultado;
    }
};

#endif