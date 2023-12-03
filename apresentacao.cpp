#include "apresentacao.hpp"
#include <iostream>
#include "controle.hpp"

TelaCadastro::TelaCadastro() {
    // Inicializações, se necessário
}

void TelaCadastro::exibir() {
    std::string email, nome, senha;

    std::cout << "Tela de Cadastro\n";
    std::cout << "Por favor, informe os seguintes dados:\n";

    std::cout << "Email: ";
    std::cin >> email;

    std::cout << "Nome: ";
    std::cin.ignore();
    std::getline(std::cin, nome); 

    std::cout << "Senha: ";
    std::cin >> senha;

    ControladorCadastro controlador("database.db");

    if (controlador.cadastrarUsuario(email, nome, senha)) {
        std::cout << "Cadastro realizado com sucesso!\n";
    } else {
        std::cout << "Falha no cadastro. Verifique os dados e tente novamente.\n";
    }
}


TelaInicial::TelaInicial() {
    // Inicializações, se necessário
}

void TelaInicial::exibir() {
    int escolha;

    do {
        std::cout << "Bem-vindo ao Sistema de Gerenciamento de Quadros!\n";
        std::cout << "1. Login\n";
        std::cout << "2. Cadastro\n";
        std::cout << "3. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> escolha;

        switch (escolha) {
            case 1: {
                // Lógica para tela de login
                TelaLogin telaLogin("database.db");
                telaLogin.exibir();
                break;
            }
            case 2: {
                TelaCadastro telaCadastro;
                telaCadastro.exibir();
                break;
            }
            case 3:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != 3);
}


TelaLogin::TelaLogin(const std::string& dbPath) : controleLogin(dbPath) {}

void TelaLogin::exibir() {
    std::string email, senha;

    std::cout << "Tela de Login\n";
    std::cout << "Por favor, informe seus dados de login:\n";

    std::cout << "Email: ";
    std::cin >> email;

    std::cout << "Senha: ";
    std::cin >> senha;

    // Chama o método de autenticação
    if (controleLogin.autenticar(email, senha)) {
        std::cout << "Login realizado com sucesso!\n";

        // Cria a tela de gerenciamento de quadros passando o caminho do banco de dados e o email do usuário
        TelaGerenciamentoQuadros telaQuadros("database.db", email);
        telaQuadros.exibir();

    } else {
        std::cout << "Credenciais inválidas. Por favor, tente novamente.\n";
        // Opção para tentar novamente ou voltar ao menu anterior
    }
}


TelaGerenciamentoQuadros::TelaGerenciamentoQuadros(const std::string& dbPath, const std::string& emailUsuario)
    : controladorQuadros(dbPath), emailUsuario(emailUsuario) {}

void TelaGerenciamentoQuadros::exibir() {
    int opcao;

    do {
        std::cout << "Gerenciamento de Quadros\n";
        std::cout << "1. Criar Quadro\n";
        std::cout << "2. Editar Quadro\n";
        std::cout << "3. Excluir Quadro\n";
        std::cout << "4. Visualizar Quadro\n";
        std::cout << "5. Voltar\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                // Lógica para criar um novo quadro
                break;
            case 2:
                // Lógica para editar um quadro existente
                break;
            case 3:
                // Lógica para excluir um quadro
                break;
            case 4:
                // Lógica para visualizar um quadro
                break;
            case 5:
                std::cout << "Voltando...\n";
                break;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
        }
    } while (opcao != 5);
}

