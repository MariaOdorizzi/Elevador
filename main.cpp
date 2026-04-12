#include <iostream>
#include <vector>

#include "classes/Pessoa.h"
#include "classes/Elevador.h"
#include "classes/Andar.h"
#include "classes/Predio.h"

using namespace std;

int main() {

    vector<Andar> andares;
    for (int i = 0; i < 10; i++) {
        andares.push_back(Andar(i));
    }

    Pessoa p1(1, 0, 5);
    Pessoa p2(2, 2, 8);
    Pessoa p3(3, 3, 1);

    andares[0].adicionarPessoa(p1);
    andares[2].adicionarPessoa(p2);
    andares[3].adicionarPessoa(p3);

    vector<Elevador> elevadores;
    elevadores.push_back(Elevador(1));
    elevadores.push_back(Elevador(2));

    elevadores[0].subir();
    elevadores[0].subir();

    elevadores[0].status();

    cout << "Andar 0 tem " << andares[0].quantidadePessoas() << " pessoas na fila" << endl;

    return 0;
}