// #include "servicos_conta.hpp"
// #include <iostream>
// #include <string>

// int main() {
//     try {
//         ServicosConta servicosConta("database.db");

//         std::string emailTeste = "pedro@example.com";
//         auto conta = servicosConta.visualizarUsuario(emailTeste);

//         if (conta) {
//             std::cout << "Conta encontrada: " << (*conta).getNome() << std::endl;
//         } else {
//             std::cout << "Conta não encontrada." << std::endl;
//         }

//     } catch (const std::exception& e) {
//         std::cerr << "Erro: " << e.what() << std::endl;
//         return 1;
//      }

//     return 0;
// }


// #include "DatabaseManager.hpp"
// #include <iostream>

// int main() {
//     try {
//         std::string dbPath = "database.db";
//         DatabaseManager dbManager(dbPath);

//         dbManager.abrirConexao();   // Abre a conexão com o banco de dados
//         dbManager.criarTabelas();   // Cria as tabelas no banco de dados

//         std::cout << "Banco de dados criado e configurado com sucesso." << std::endl;

//     } catch (const std::exception& e) {
//         std::cerr << "Erro ao configurar o banco de dados: " << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }



// #include "DatabaseManager.hpp"
// #include "servicos_conta.hpp"
// #include <iostream>
// #include <string>
// #include <optional>

// int main() {
//     try {
//         std::string dbPath = "database.db";
//         ServicosConta servicosConta(dbPath);

//         std::string email = "user@example.com";
//         std::string nome = "Pedro";
//         std::string senha = "B1.b!";

//         // Tenta criar um usuário
//         // try {
//         //     // servicosConta.excluirUsuario(email);
//         //     servicosConta.criarUsuario(email, nome, senha);
//         //     std::cout << "Usuário excluido com sucesso." << std::endl;
//         // } catch (const std::exception& e) {
//         //     std::cerr << "Erro ao excluir usuário: " << e.what() << std::endl;
//         //     return 1;  // Encerra se não conseguir criar usuário
//         // }

//         // Tenta visualizar o usuário criado
//         auto conta = servicosConta.visualizarUsuario(email);
//         if (conta) {
//             std::cout << "Detalhes do usuário:" << std::endl;
//             std::cout << "Email: " << conta->getEmail() << std::endl;
//             std::cout << "Nome: " << conta->getNome() << std::endl;
//             std::cout << "Senha: " << conta->getSenha() << std::endl;
//         } else {
//             std::cout << "Usuário não encontrado." << std::endl;
//         }

//     } catch (const std::exception& e) {
//         std::cerr << "Erro geral: " << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }




#include "DatabaseManager.hpp"
#include "servicos_quadro.hpp"
#include <iostream>
#include <string>

// Função para testar a criação de um quadro
void testarCriacaoQuadro(ServicosQuadro& servicosQuadro) {
    std::string codigo, emailConta, nome, descricao;
    int limite;

    std::cout << "Informe o código do quadro (ex: AB12): ";
    std::cin >> codigo;

    std::cout << "Informe o email da conta associada: ";
    std::cin >> emailConta;

    std::cout << "Informe o nome do quadro: ";
    std::cin.ignore(); // Ignora o '\n' que sobrou da entrada anterior
    std::getline(std::cin, nome); // Usa getline para permitir espaços no nome

    std::cout << "Informe a descrição do quadro: ";
    std::getline(std::cin, descricao);

    std::cout << "Informe o limite de tarefas (5, 10, 15 ou 20): ";
    std::cin >> limite;

    try {
        servicosQuadro.criarQuadro(codigo, emailConta, nome, descricao, limite);
        std::cout << "Quadro criado com sucesso!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao criar quadro: " << e.what() << std::endl;
    }
}

int main() {
    try {
        std::string dbPath = "database.db";
        ServicosQuadro servicosQuadro(dbPath);

        // Testar a criação de um quadro
        testarCriacaoQuadro(servicosQuadro);

    } catch (const std::exception& e) {
        std::cerr << "Erro geral: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}







