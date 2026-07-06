#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#include "Classes/Fifo.h"
#include "Classes/Scan.h"
#include "Classes/MenorDistancia.h"

using namespace std;

const int TOTAL_ANDARES = 9;
const string NOME_ARQUIVO = "historico_simulacoes.csv";

// Limpa a tela do terminal
void limparTela() {

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Mostra o elevador em uma posicao especifica
void mostrarElevadorAnimado(
    string estrategia,
    int andarAtual,
    int origem,
    int destino,
    int movimentos
) {

    cout << "==============================" << endl;
    cout << "ESTRATEGIA: " << estrategia << endl;
    cout << "==============================" << endl;

    cout << "Origem: " << origem << endl;
    cout << "Destino: " << destino << endl;
    cout << "Andar atual: " << andarAtual << endl;

    if(andarAtual < destino)
        cout << "Estado: SUBINDO" << endl;
    else if(andarAtual > destino)
        cout << "Estado: DESCENDO" << endl;
    else
        cout << "Estado: PARADO" << endl;

    cout << "Movimentos realizados: " << movimentos << endl;
    cout << endl;

    for(int andar = TOTAL_ANDARES - 1; andar >= 0; andar--) {

        if(andar == andarAtual) {
            cout << "[" << andar << "] | E |" << endl;
        } else {
            cout << "[" << andar << "] |   |" << endl;
        }
    }
}

// Anima o elevador andando de andar em andar
void animarEstrategia(
    string estrategia,
    vector<int> ordem,
    int andarInicial
) {

    int andarAtual = andarInicial;
    int movimentos = 0;

    for(int destino : ordem) {

        int origem = andarAtual;

        limparTela();
        mostrarElevadorAnimado(
            estrategia,
            andarAtual,
            origem,
            destino,
            movimentos
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );

        while(andarAtual != destino) {

            if(andarAtual < destino)
                andarAtual++;
            else
                andarAtual--;

            movimentos++;

            limparTela();
            mostrarElevadorAnimado(
                estrategia,
                andarAtual,
                origem,
                destino,
                movimentos
            );

            std::this_thread::sleep_for(
                std::chrono::milliseconds(500)
            );
        }
    }

    cout << endl;
    cout << "Fim da estrategia " << estrategia << endl;
    cout << "Total de movimentos: " << movimentos << endl;
    cout << endl;

    std::this_thread::sleep_for(
        std::chrono::milliseconds(1000)
    );
}


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

// Calcula quantidade de movimentos a partir do andar inicial informado
int calcularMovimentos(
    vector<int> chamadas,
    int andarInicial
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
    vector<int> chamadas,
    int andarInicial
) {

    cout << andarInicial;

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


// Estrutura usada para controlar cada elevador na animacao simultanea
struct AnimacaoElevador {
    string nome;
    vector<int> ordem;
    int andarAtual;
    int indiceDestino;
    int movimentos;
    bool finalizado;
};

// Retorna o destino atual da estrategia
int obterDestinoAtual(
    AnimacaoElevador elevador
) {

    if(elevador.finalizado || elevador.indiceDestino >= elevador.ordem.size())
        return elevador.andarAtual;

    return elevador.ordem[elevador.indiceDestino];
}

// Retorna o estado atual da animacao
string obterEstadoAnimacao(
    AnimacaoElevador elevador
) {

    if(elevador.finalizado)
        return "PARADO";

    int destino = obterDestinoAtual(elevador);

    if(elevador.andarAtual < destino)
        return "SUBINDO";

    if(elevador.andarAtual > destino)
        return "DESCENDO";

    return "PARADO";
}

// Avanca um andar em uma estrategia
void avancarElevador(
    AnimacaoElevador &elevador
) {

    if(elevador.finalizado)
        return;

    if(elevador.indiceDestino >= elevador.ordem.size()) {
        elevador.finalizado = true;
        return;
    }

    int destino = elevador.ordem[elevador.indiceDestino];

    if(elevador.andarAtual < destino) {
        elevador.andarAtual++;
        elevador.movimentos++;
    } else if(elevador.andarAtual > destino) {
        elevador.andarAtual--;
        elevador.movimentos++;
    }

    // Se chegou no destino, passa para a proxima chamada
    if(elevador.andarAtual == destino) {
        elevador.indiceDestino++;

        if(elevador.indiceDestino >= elevador.ordem.size())
            elevador.finalizado = true;
    }
}

// Imprime uma linha da animacao simultanea
void imprimirLinhaAnimacao(
    int andar,
    AnimacaoElevador fifo,
    AnimacaoElevador scan,
    AnimacaoElevador menor
) {

    imprimirLinha(andar, fifo.andarAtual);
    cout << "            ";

    imprimirLinha(andar, scan.andarAtual);
    cout << "            ";

    imprimirLinha(andar, menor.andarAtual);
    cout << endl;
}

// Mostra os tres elevadores andando ao mesmo tempo
void mostrarAnimacaoSimultanea(
    vector<int> chamadas,
    AnimacaoElevador fifo,
    AnimacaoElevador scan,
    AnimacaoElevador menor
) {

    cout << "ANIMACAO SIMULTANEA DAS ESTRATEGIAS" << endl;
    cout << "Chamadas: ";
    imprimirLista(chamadas);
    cout << endl << endl;

    cout << "FIFO                    "
         << "SCAN                    "
         << "MENOR DISTANCIA"
         << endl;

    cout << "---------------------------------------------------------------------------" << endl;

    cout << "Destino: " << obterDestinoAtual(fifo);
    cout << "             ";
    cout << "Destino: " << obterDestinoAtual(scan);
    cout << "             ";
    cout << "Destino: " << obterDestinoAtual(menor);
    cout << endl;

    cout << "Estado: " << obterEstadoAnimacao(fifo);
    cout << "          ";
    cout << "Estado: " << obterEstadoAnimacao(scan);
    cout << "          ";
    cout << "Estado: " << obterEstadoAnimacao(menor);
    cout << endl;

    cout << "Movimentos: " << fifo.movimentos;
    cout << "       ";
    cout << "Movimentos: " << scan.movimentos;
    cout << "       ";
    cout << "Movimentos: " << menor.movimentos;
    cout << endl << endl;

    for(int andar = TOTAL_ANDARES - 1; andar >= 0; andar--) {
        imprimirLinhaAnimacao(
            andar,
            fifo,
            scan,
            menor
        );
    }

    cout << "---------------------------------------------------------------------------" << endl;
}

// Anima FIFO, SCAN e Menor Distancia lado a lado, ao mesmo tempo
void animarTresEstrategias(
    vector<int> chamadas,
    vector<int> ordemFIFO,
    vector<int> ordemSCAN,
    vector<int> ordemMenor,
    int andarInicial
) {

    AnimacaoElevador fifo = {
        "FIFO",
        ordemFIFO,
        andarInicial,
        0,
        0,
        ordemFIFO.empty()
    };

    AnimacaoElevador scan = {
        "SCAN",
        ordemSCAN,
        andarInicial,
        0,
        0,
        ordemSCAN.empty()
    };

    AnimacaoElevador menor = {
        "MENOR DISTANCIA",
        ordemMenor,
        andarInicial,
        0,
        0,
        ordemMenor.empty()
    };

    while(
        !fifo.finalizado
        || !scan.finalizado
        || !menor.finalizado
    ) {

        limparTela();

        mostrarAnimacaoSimultanea(
            chamadas,
            fifo,
            scan,
            menor
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(450)
        );

        avancarElevador(fifo);
        avancarElevador(scan);
        avancarElevador(menor);
    }

    limparTela();

    mostrarAnimacaoSimultanea(
        chamadas,
        fifo,
        scan,
        menor
    );

    std::this_thread::sleep_for(
        std::chrono::milliseconds(1200)
    );
}

// Retorna estado final da estrategia
string obterEstadoFinal(
    vector<int> ordem,
    int andarInicial
) {

    if(ordem.empty())
        return "PARADO";

    int ultimo = ordem.back();

    if(ultimo > andarInicial)
        return "SUBINDO";

    if(ultimo < andarInicial)
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
    int movMenor,

    int andarInicial
) {

    int posFIFO = fifo.empty() ? andarInicial : fifo.back();
    int posSCAN = scan.empty() ? andarInicial : scan.back();
    int posMenor = menor.empty() ? andarInicial : menor.back();

    cout << endl;
    cout << "COMPARACAO DAS ESTRATEGIAS" << endl;

    cout << "Andar inicial: " << andarInicial << endl;

    cout << "Chamadas geradas aleatoriamente: ";
    imprimirLista(entrada);
    cout << endl << endl;

    cout << "FIFO                    "
         << "SCAN                    "
         << "MENOR DISTANCIA"
         << endl;

    cout << "---------------------------------------------------------------------------" << endl;

    cout << "Estado: " << obterEstadoFinal(fifo, andarInicial);
    cout << "         ";
    cout << "Estado: " << obterEstadoFinal(scan, andarInicial);
    cout << "         ";
    cout << "Estado: " << obterEstadoFinal(menor, andarInicial);
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
    imprimirPercurso(fifo, andarInicial);
    cout << endl;

    cout << "SCAN: ";
    imprimirPercurso(scan, andarInicial);
    cout << endl;

    cout << "MENOR: ";
    imprimirPercurso(menor, andarInicial);
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
    int andarInicial;

    cout << "Andar inicial do elevador (0 a " << TOTAL_ANDARES - 1 << "): ";
    cin >> andarInicial;

    if(andarInicial < 0 || andarInicial >= TOTAL_ANDARES) {
        cout << "Andar inicial invalido." << endl;
        return 0;
    }

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
        andarInicial
    );

    vector<int> scan = estrategiaSCAN.organizar(
        chamadas,
        andarInicial
    );

    vector<int> menor = estrategiaMenor.organizar(
        chamadas,
        andarInicial
    );

    int movFIFO = calcularMovimentos(
        fifo,
        andarInicial
    );

    int movSCAN = calcularMovimentos(
        scan,
        andarInicial
    );

    int movMenor = calcularMovimentos(
        menor,
        andarInicial
    );

    criarCabecalhoCSV();

    int simulacao = obterProximaSimulacao();

    salvarCSV(
        simulacao,
        "FIFO",
        chamadas,
        fifo,
        movFIFO,
        andarInicial
    );

    salvarCSV(
        simulacao,
        "SCAN",
        chamadas,
        scan,
        movSCAN,
        andarInicial
    );

    salvarCSV(
        simulacao,
        "MENOR_DISTANCIA",
        chamadas,
        menor,
        movMenor,
        andarInicial
    );

    // Mostra as tres estrategias se movimentando ao mesmo tempo
    animarTresEstrategias(
        chamadas,
        fifo,
        scan,
        menor,
        andarInicial
    );

    limparTela();

    mostrarComparacao(
        chamadas,
        fifo,
        scan,
        menor,
        movFIFO,
        movSCAN,
        movMenor,
        andarInicial
    );

    cout << endl;
    cout << "Historico salvo no arquivo: " << NOME_ARQUIVO << endl;
    cout << "Simulacao numero: " << simulacao << endl;

    return 0;
}
