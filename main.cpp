#include <iostream>
#include <string>
#include "DatabaseManager.hpp"
#include "interfaces.hpp"

using namespace std;

int main() {
    DatabaseManager dbManager("projeto_kanban.db");
    if (!dbManager.abrirConexao()) {
        cerr << "Falha ao abrir conexão com o banco de dados." << endl;
        return 1;
    }

    dbManager.criarTabelas();

    // Criando instâncias de domínio para teste
    Email emailTeste;
    Texto nomeTeste;
    Senha senhaTeste;

    try {
        emailTeste.setEmail("usuario@teste.com");
        nomeTeste.setTexto("Usuario Teste");
        senhaTeste.setSenha("Senha123!");

        // Criando uma conta de teste
        Conta contaTeste(emailTeste, nomeTeste, senhaTeste);

        // Criando ServicoUsuario e testando a criação de usuário
        ServicoUsuario servicoUsuario(dbManager);
        if (servicoUsuario.criarUsuario(contaTeste)) {
            cout << "Usuário criado com sucesso." << endl;
        } else {
            cout << "Falha ao criar usuário." << endl;
        }

        // Testando a busca por usuário
        try {
            Conta contaEncontrada = servicoUsuario.obterUsuario(emailTeste);
            cout << "Usuário encontrado: " << contaEncontrada.getNome() << endl;
        } catch (const runtime_error& e) {
            cout << "Erro ao buscar usuário: " << e.what() << endl;
        }

        // Adicione mais testes conforme necessário

    } catch (const invalid_argument& e) {
        cerr << "Erro na criação dos dados de teste: " << e.what() << endl;
    }

    return 0;
}
