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
//         // Substitua 'caminho_para_o_banco_de_dados.db' pelo caminho desejado para o banco de dados
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



#include "DatabaseManager.hpp"
#include "servicos_conta.hpp"
#include <iostream>
#include <string>
#include <optional>

int main() {
    try {
        std::string dbPath = "database.db";
        ServicosConta servicosConta(dbPath);

        std::string email = "user@example.com";
        std::string nome = "Pedro";
        std::string senha = "B1.b!";

        // Tenta criar um usuário
        try {
            servicosConta.criarUsuario(email, nome, senha);
            std::cout << "Usuário criado com sucesso." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Erro ao criar usuário: " << e.what() << std::endl;
            return 1;  // Encerra se não conseguir criar usuário
        }

        // Tenta visualizar o usuário criado
        auto conta = servicosConta.visualizarUsuario(email);
        if (conta) {
            std::cout << "Detalhes do usuário:" << std::endl;
            std::cout << "Email: " << conta->getEmail() << std::endl;
            std::cout << "Nome: " << conta->getNome() << std::endl;
            std::cout << "Senha: " << conta->getSenha() << std::endl;
        } else {
            std::cout << "Usuário não encontrado." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Erro geral: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
