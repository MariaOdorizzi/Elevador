#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "Classes/Fifo.h"
#include "Classes/Scan.h"
#include "Classes/MenorDistancia.h"

using namespace std;

const int ANDAR_INICIAL = 0;
const int TOTAL_ANDARES = 9;
const string NOME_ARQUIVO = "historico_simulacoes.csv";

// Gera uma unica sequencia aleatoria de chamadas
vector<int> gerarChamadasAleatorias(
    int quantidadeChamadas,
    int totalAndares
) {

    vector<int> chamadas;

    for(int i = 0; i < quantidadeChamadas; i++) {

        int andar = rand() % totalAndares;

        chamadas.push_back(andar);
    }

    return chamadas;
}

// Calcula quantidade de movimentos iniciando sempre do andar 0
int calcularMovimentos(
    vector<int> chamadas,
    int andarInicial = ANDAR_INICIAL
) {

    int posicao = andarInicial;
    int movimentos = 0;

    for(int chamada : chamadas) {

        movimentos += abs(
            chamada - posicao
        );

        posicao = chamada;
    }

    return movimentos;
}

// Converte vector<int> para texto para salvar no CSV
string vetorParaTexto(
    vector<int> lista
) {

    stringstream ss;

    for(int i = 0; i < lista.size(); i++) {

        ss << lista[i];

        if(i < lista.size() - 1)
            ss << " ";
    }

    return ss.str();
}

// Verifica se o arquivo existe
bool arquivoExiste(
    string nomeArquivo
) {

    ifstream arquivo(nomeArquivo);

    return arquivo.good();
}

// Cria cabecalho do CSV caso o arquivo ainda nao exista
void criarCabecalhoCSV() {

    if(!arquivoExiste(NOME_ARQUIVO)) {

        ofstream arquivo(NOME_ARQUIVO);

        arquivo
            << "simulacao,estrategia,chamadas_entrada,ordem_execucao,quantidade_chamadas,movimentos,andar_inicial,andar_final"
            << endl;

        arquivo.close();
    }
}

// Calcula o proximo numero de simulacao com base no historico
int obterProximaSimulacao() {

    if(!arquivoExiste(NOME_ARQUIVO))
        return 1;

    ifstream arquivo(NOME_ARQUIVO);

    string linha;
    int quantidadeLinhas = 0;

    // Ignora cabecalho
    getline(arquivo, linha);

    while(getline(arquivo, linha)) {
        if(!linha.empty())
            quantidadeLinhas++;
    }

    arquivo.close();

    // Cada simulacao grava 3 linhas: FIFO, SCAN e MENOR_DISTANCIA
    return (quantidadeLinhas / 3) + 1;
}

// Salva resultado da estrategia no CSV
void salvarCSV(
    int simulacao,
    string estrategia,
    vector<int> chamadasEntrada,
    vector<int> ordemExecucao,
    int movimentos,
    int andarInicial
) {

    ofstream arquivo;

    arquivo.open(
        NOME_ARQUIVO,
        ios::app
    );

    int andarFinal = andarInicial;

    if(!ordemExecucao.empty())
        andarFinal = ordemExecucao.back();

    arquivo
        << simulacao << ","
        << estrategia << ","
        << "\"" << vetorParaTexto(chamadasEntrada) << "\"" << ","
        << "\"" << vetorParaTexto(ordemExecucao) << "\"" << ","
        << chamadasEntrada.size() << ","
        << movimentos << ","
        << andarInicial << ","
        << andarFinal
        << endl;

    arquivo.close();
}

// Imprime lista simples
void imprimirLista(
    vector<int> lista
) {

    for(int valor : lista) {
        cout << valor << " ";
    }
}

// Imprime percurso completo
void imprimirPercurso(
    vector<int> chamadas
) {

    cout << ANDAR_INICIAL;

    for(int chamada : chamadas) {
        cout << " -> " << chamada;
    }
}

// Imprime linha do elevador
void imprimirLinha(
    int andar,
    int posicao
) {

    if(andar == posicao) {
        cout << "[" << andar << "] | E |";
    } else {
        cout << "[" << andar << "] |   |";
    }
}

// Retorna estado final da estrategia
string obterEstadoFinal(
    vector<int> ordem
) {

    if(ordem.empty())
        return "PARADO";

    int ultimo = ordem.back();

    if(ultimo > ANDAR_INICIAL)
        return "SUBINDO";

    if(ultimo < ANDAR_INICIAL)
        return "DESCENDO";

    return "PARADO";
}

// Mostra comparacao das estrategias lado a lado
void mostrarComparacao(
    vector<int> entrada,

    vector<int> fifo,
    vector<int> scan,
    vector<int> menor,

    int movFIFO,
    int movSCAN,
    int movMenor
) {

    int posFIFO = fifo.empty() ? ANDAR_INICIAL : fifo.back();
    int posSCAN = scan.empty() ? ANDAR_INICIAL : scan.back();
    int posMenor = menor.empty() ? ANDAR_INICIAL : menor.back();

    cout << endl;
    cout << "COMPARACAO DAS ESTRATEGIAS" << endl;

    cout << "Chamadas geradas aleatoriamente: ";
    imprimirLista(entrada);
    cout << endl << endl;

    cout << "FIFO                    "
         << "SCAN                    "
         << "MENOR DISTANCIA"
         << endl;

    cout << "---------------------------------------------------------------------------" << endl;

    cout << "Estado: " << obterEstadoFinal(fifo);
    cout << "         ";
    cout << "Estado: " << obterEstadoFinal(scan);
    cout << "         ";
    cout << "Estado: " << obterEstadoFinal(menor);
    cout << endl << endl;

    cout << "Ordem:                  ";
    cout << "Ordem:                  ";
    cout << "Ordem:" << endl;

    imprimirLista(fifo);
    cout << "            ";
    imprimirLista(scan);
    cout << "            ";
    imprimirLista(menor);
    cout << endl << endl;

    cout << "Movimentos: " << movFIFO;
    cout << "      ";
    cout << "Movimentos: " << movSCAN;
    cout << "      ";
    cout << "Movimentos: " << movMenor;
    cout << endl << endl;

    cout << "FIFO: ";
    imprimirPercurso(fifo);
    cout << endl;

    cout << "SCAN: ";
    imprimirPercurso(scan);
    cout << endl;

    cout << "MENOR: ";
    imprimirPercurso(menor);
    cout << endl << endl;

    for(int andar = TOTAL_ANDARES - 1; andar >= 0; andar--) {

        imprimirLinha(andar, posFIFO);
        cout << "            ";
        imprimirLinha(andar, posSCAN);
        cout << "            ";
        imprimirLinha(andar, posMenor);
        cout << endl;
    }

    cout << "---------------------------------------------------------------------------" << endl;
}

int main() {

    srand(time(NULL));

    int quantidadeChamadas;

    cout << "Quantidade de chamadas aleatorias: ";
    cin >> quantidadeChamadas;

    if(quantidadeChamadas <= 0) {
        cout << "Quantidade invalida." << endl;
        return 0;
    }

    // A sequencia aleatoria e gerada apenas uma vez
    vector<int> chamadas = gerarChamadasAleatorias(
        quantidadeChamadas,
        TOTAL_ANDARES
    );

    // As tres estrategias recebem exatamente a mesma entrada
    FIFO estrategiaFIFO;
    SCAN estrategiaSCAN;
    MenorDistancia estrategiaMenor;

    vector<int> fifo = estrategiaFIFO.organizar(
        chamadas,
        ANDAR_INICIAL
    );

    vector<int> scan = estrategiaSCAN.organizar(
        chamadas,
        ANDAR_INICIAL
    );

    vector<int> menor = estrategiaMenor.organizar(
        chamadas,
        ANDAR_INICIAL
    );

    int movFIFO = calcularMovimentos(
        fifo,
        ANDAR_INICIAL
    );

    int movSCAN = calcularMovimentos(
        scan,
        ANDAR_INICIAL
    );

    int movMenor = calcularMovimentos(
        menor,
        ANDAR_INICIAL
    );

    criarCabecalhoCSV();

    int simulacao = obterProximaSimulacao();

    salvarCSV(
        simulacao,
        "FIFO",
        chamadas,
        fifo,
        movFIFO,
        ANDAR_INICIAL
    );

    salvarCSV(
        simulacao,
        "SCAN",
        chamadas,
        scan,
        movSCAN,
        ANDAR_INICIAL
    );

    salvarCSV(
        simulacao,
        "MENOR_DISTANCIA",
        chamadas,
        menor,
        movMenor,
        ANDAR_INICIAL
    );

    mostrarComparacao(
        chamadas,
        fifo,
        scan,
        menor,
        movFIFO,
        movSCAN,
        movMenor
    );

    cout << endl;
    cout << "Historico salvo no arquivo: " << NOME_ARQUIVO << endl;
    cout << "Simulacao numero: " << simulacao << endl;

    return 0;
}
