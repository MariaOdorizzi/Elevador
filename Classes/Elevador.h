#ifndef ELEVADOR_H
#define ELEVADOR_H

#include <vector>
#include <string>

#include "Pessoa.h"
#include "Andar.h"
#include "EstrategiaElevador.h"

using namespace std;

// Estados do elevador
enum EstadoElevador {
    PARADO,
    SUBINDO,
    DESCENDO
};

class Elevador {

private:

    // Identificador
    int id;

    // Andar atual
    int andarAtual;

    // Estado atual
    EstadoElevador estado;

    // Capacidade maxima
    int capacidade;

    // Pessoas embarcadas
    vector<Pessoa> pessoas;

    // Lista de chamadas
    vector<int> chamadas;

    // Estrategia atual
    EstrategiaElevador* estrategia;

public:

    // Inicializa elevador
    Elevador(int capacidade);

    // Retorna andar atual
    int getAndarAtual();

    // Define andar atual
    void setAndarAtual(
        int andar
    );

    // Define estrategia
    void setEstrategia(
        EstrategiaElevador* estrategia
    );

    // Move elevador
    void mover();

    // Embarca pessoas
    void embarcar(
        Andar& andar
    );

    // Desembarca pessoas
    void desembarcar();

    // Verifica vazio
    bool vazio();

    // Adiciona chamada
    void adicionarChamada(
        int andar
    );

    // Retorna estado
    string getEstadoTexto();

    // Mostra cabecalho
    void mostrarCabecalho(
        string algoritmo
    );

    // Mostra movimento
    void mostrarMovimento(
        int origem,
        int destino
    );

    // Executa FIFO
    void executarFIFO();

    // Executa SCAN
    void executarSCAN();

    // Executa menor distancia
    void executarMenorDistancia();

    // Executa estrategia
    void executar();

    // Calcula movimentos
    int calcularMovimentos(
        vector<int> ordem
    );
};

#endif