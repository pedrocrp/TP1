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


#include "servicos.hpp"
#include <iostream>
#include <stdexcept>
#include "entidades.h"

void testeConta(ServicosConta& servicosConta) {
    try {
        // Criar uma conta
        Email email;
        email.setEmail("usuario@example.com");
        Texto nome;
        nome.setTexto("Usuario Teste");
        Senha senha;
        senha.setSenha("AB.c1");

        Conta conta(email, nome, senha);
        servicosConta.criarUsuario(conta);
        std::cout << "Conta criada com sucesso." << std::endl;

        // Visualizar uma conta
        auto contaVisualizada = servicosConta.visualizarUsuario("usuario@example.com");
        if (contaVisualizada) {
            std::cout << "Conta visualizada:" << std::endl;
            std::cout << "Email: " << contaVisualizada->getEmail() << std::endl;
            std::cout << "Nome: " << contaVisualizada->getNome() << std::endl;
            std::cout << "Senha: " << contaVisualizada->getSenha() << std::endl;
        } else {
            std::cout << "Conta não encontrada." << std::endl;
        }

        // Editar uma conta
        std::string novoNome = "Usuario Atualizado";
        std::string novaSenha = "NEw.1";
        servicosConta.editarUsuario("usuario@example.com", novoNome, novaSenha);
        std::cout << "Conta editada com sucesso." << std::endl;

        // Excluir uma conta
        servicosConta.excluirUsuario("usuario@example.com");
        std::cout << "Conta excluída com sucesso." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }
}


void testeCartao(ServicosCartao& servicosCartao) {
    try {
        // Criar um cartão
        Codigo codigoCartao;
        codigoCartao.setCodigo("CD34");
        Texto nomeCartao;
        nomeCartao.setTexto("Cartao Teste");
        Texto descricaoCartao;
        descricaoCartao.setTexto("Descricao do Cartao");
        Coluna colunaCartao;
        colunaCartao.setEstado("EM EXECUCAO");
        Cartao cartao(codigoCartao, nomeCartao, descricaoCartao, colunaCartao);

        // Supondo que QD01 é o código de um quadro existente
        servicosCartao.criarCartao(cartao, "QD01"); 
        std::cout << "Cartão criado com sucesso." << std::endl;

        // Visualizar um cartão
        auto cartaoVisualizado = servicosCartao.visualizarCartao("CD34");
        if (cartaoVisualizado) {
            std::cout << "Cartão visualizado: " << cartaoVisualizado->getNome() << std::endl;
        } else {
            std::cout << "Cartão não encontrado." << std::endl;
        }

        // Mover um cartão
        servicosCartao.moverCartao("CD34", "CONCLUIDO");
        std::cout << "Cartão movido com sucesso." << std::endl;

        // Excluir um cartão
        servicosCartao.excluirCartao("CD34");
        std::cout << "Cartão excluído com sucesso." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }
}


int main() {
    try {
        std::string dbPath = "database.db";
        ServicosConta servicosConta(dbPath);
        ServicosCartao servicosCartao(dbPath);

        //testeConta(servicosConta);
        testeCartao(servicosCartao);

    } catch (const std::exception& e) {
        std::cerr << "Erro geral: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
