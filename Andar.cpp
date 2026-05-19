#include "Classes/Andar.h"

// Inicializa andar
Andar::Andar(int numero) {

    this->numero = numero;
}

// Adiciona pessoa
void Andar::adicionarPessoa(
    Pessoa pessoa
) {

    pessoas.push_back(pessoa);
}

// Retorna pessoas
vector<Pessoa>& Andar::getPessoas() {

    return pessoas;
}

// Verifica vazio
bool Andar::vazio() {

    return pessoas.empty();
}

// Remove pessoa
Pessoa Andar::removerPessoa() {

    Pessoa pessoa = pessoas.front();

    pessoas.erase(
        pessoas.begin()
    );

    return pessoa;
}