#ifndef MENOR_DISTANCIA_H
#define MENOR_DISTANCIA_H

#include <cmath>

#include "EstrategiaElevador.h"

using namespace std;

// Estrategia menor distancia
class MenorDistancia :
    public EstrategiaElevador {

public:

    vector<int> organizar(
        vector<int> chamadas,
        int andarAtual
    ) override {

        vector<int> resultado;

        while(!chamadas.empty()) {

            int melhorIndice = 0;

            int menor =
                abs(
                    chamadas[0]
                    - andarAtual
                );

            for(
                int i = 1;
                i < chamadas.size();
                i++
            ) {

                int distancia =
                    abs(
                        chamadas[i]
                        - andarAtual
                    );

                if(distancia < menor) {

                    menor = distancia;

                    melhorIndice = i;
                }
            }

            andarAtual =
                chamadas[melhorIndice];

            resultado.push_back(
                chamadas[melhorIndice]
            );

            chamadas.erase(
                chamadas.begin()
                + melhorIndice
            );
        }

        return resultado;
    }
};

#endif