#include "apresentacao.hpp"
#include "controle.hpp"
#include <iostream>
#include <string>
#include <optional>



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
                std::cout << "\nSaindo...\n";
                break;
            default:
                std::cout << "\nOpção inválida. Tente novamente.\n";
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
    std::string codigoQuadro, nomeQuadro, descricaoQuadro;
    int limiteQuadro;
    Quadro quadro;

    do {
        std::cout << "\nGerenciamento de Quadros\n";
        std::cout << "1. Criar Quadro\n";
        std::cout << "2. Editar Quadro\n";
        std::cout << "3. Excluir Quadro\n";
        std::cout << "4. Visualizar Quadro\n";
        std::cout << "5. Voltar\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: {
                // Lógica para criar um novo quadro
                std::string codigo, nome, descricao, limiteInput;
                int limite;
                std::cout << "\nInsira o código do quadro: ";
                std::cin >> codigo;
                std::cout << "Insira o nome do quadro: ";
                std::cin.ignore();
                std::getline(std::cin, nome);
                std::cout << "Insira a descrição do quadro: ";
                std::getline(std::cin, descricao);
                std::cout << "Insira o limite do quadro (5, 10, 15, 20): ";
                std::cin >> limiteInput;
                limite = std::stoi(limiteInput);  // Convertendo para inteiro

                controladorQuadros.criarQuadro(emailUsuario, codigo, nome, descricao, limite);
                break;
            }
            
            case 2: {
                // Lógica para editar um quadro existente
                std::cout << "\nDigite o código do quadro a ser editado: ";
                std::cin >> codigoQuadro;
                std::cin.ignore();

                std::cout << "Digite o novo nome do quadro (deixe em branco se não quiser alterar): ";
                std::getline(std::cin, nomeQuadro);

                std::cout << "Digite a nova descrição do quadro (deixe em branco se não quiser alterar): ";
                std::getline(std::cin, descricaoQuadro);

                std::cout << "Digite o novo limite do quadro (deixe em branco se não quiser alterar): ";
                std::string limiteInput;
                std::getline(std::cin, limiteInput);
                std::optional<int> novoLimite;
                if (!limiteInput.empty()) {
                    novoLimite = std::stoi(limiteInput);
                }

                controladorQuadros.editarQuadro(emailUsuario, codigoQuadro, nomeQuadro, descricaoQuadro, novoLimite);
                break;
            }
            
            case 3: {
                // Lógica para excluir um quadro
                std::cout << "\nDigite o código do quadro a ser excluído: ";
                std::cin >> codigoQuadro;
                std::cin.ignore();
                controladorQuadros.excluirQuadro(emailUsuario, codigoQuadro);
                break;
            }
            
            case 4: {
                // Lógica para visualizar um quadro
                std::cout << "\nDigite o código do quadro a ser visualizado: ";
                std::cin >> codigoQuadro;
                auto quadroComCartoes = controladorQuadros.visualizarQuadro(emailUsuario, codigoQuadro);

                if (quadroComCartoes) {
                    const Quadro& quadro = quadroComCartoes->quadro;
                    const std::vector<std::string>& codigosCartoes = quadroComCartoes->codigosCartoes;

                    std::cout << "Nome do Quadro: " << quadro.getNome() << "\n";
                    std::cout << "Descrição: " << quadro.getDescricao() << "\n";
                    std::cout << "Limite: " << quadro.getLimite() << "\n";

                    if (!codigosCartoes.empty()) {
                        std::cout << "Códigos dos Cartões associados:\n";
                        for (const auto& codigo : codigosCartoes) {
                            std::cout << "- " << codigo << "\n";
                        }
                    } else {
                        std::cout << "\nNão há cartões associados a este quadro.\n";
                    }
                } else {
                    std::cout << "Quadro não encontrado.\n";
                }
                break;
            }

            case 5:{
                std::cout << "\nVoltando...\n";
                break;
            }
            default:
                std::cout << "\nOpção inválida. Tente novamente.\n";
        }
    } while (opcao != 5);
}

