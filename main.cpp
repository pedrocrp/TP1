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
#include "apresentacao.hpp"


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
            std::cout << "Conta visualizada: " << std::endl;
            std::cout << "Email: " << contaVisualizada->getEmail() << std::endl;
            std::cout << "Nome: " << contaVisualizada->getNome() << std::endl;
            std::cout << "Senha: " << contaVisualizada->getSenha() << std::endl;
        } else {
            std::cout << "Conta não encontrada." << std::endl;
        }

        // // Editar uma conta
        // std::string novoNome = "Usuario Atualizado";
        // std::string novaSenha = "NEw.1";
        // servicosConta.editarUsuario("usuario@example.com", novoNome, novaSenha);
        // std::cout << "Conta editada com sucesso." << std::endl;

        // // Excluir uma conta
        // servicosConta.excluirUsuario("usuario@example.com");
        // std::cout << "Conta excluída com sucesso." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }
}

// Testes para Quadro
void testeQuadro(ServicosQuadro& servicosQuadro, const std::string& emailUsuario) {
    try {
        // Criar um quadro
        Codigo codigoQuadro;
        codigoQuadro.setCodigo("QD01");
        Texto nomeQuadro;
        nomeQuadro.setTexto("Quadro Teste");
        Texto descricaoQuadro;
        descricaoQuadro.setTexto("Descricao do Quadro");
        Limite limiteQuadro;
        limiteQuadro.setLimite(5);

        Quadro quadro(codigoQuadro, nomeQuadro, descricaoQuadro, limiteQuadro);
        servicosQuadro.criarQuadro(emailUsuario, quadro);
        std::cout << "Quadro criado com sucesso." << std::endl;

        // Visualizar um quadro
        auto quadroVisualizado = servicosQuadro.visualizarQuadro(emailUsuario, "QD01");
        if (quadroVisualizado) {
            std::cout << "Quadro visualizado: " << quadroVisualizado->getNome() << std::endl;
        } else {
            std::cout << "Quadro não encontrado." << std::endl;
        }

        // Editar um quadro
        std::optional<std::string> novoNome = "Quadro Atualizado";
        std::optional<std::string> novaDescricao = std::nullopt; // Sem alteração na descrição
        std::optional<int> novoLimite = 10;
        servicosQuadro.editarQuadro(emailUsuario, "QD01", novoNome, novaDescricao, novoLimite);
        std::cout << "Quadro editado com sucesso." << std::endl;

        // Excluir um quadro
        servicosQuadro.excluirQuadro(emailUsuario, "QD01");
        std::cout << "Quadro excluído com sucesso." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro em testeQuadro: " << e.what() << std::endl;
    }
}

// Testes para Cartao
void testeCartao(ServicosCartao& servicosCartao, const std::string& emailUsuario, const std::string& codigoQuadro) {
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
        servicosCartao.criarCartao(cartao, codigoQuadro, emailUsuario);
        std::cout << "Cartão criado com sucesso." << std::endl;

        // Visualizar um cartão
        auto cartaoVisualizado = servicosCartao.visualizarCartao("CD34", emailUsuario);
        if (cartaoVisualizado) {
            std::cout << "Cartão visualizado: " << cartaoVisualizado->getNome() << std::endl;
        } else {
            std::cout << "Cartão não encontrado." << std::endl;
        }

        // Mover um cartão
        servicosCartao.moverCartao("CD34", "CONCLUIDO", emailUsuario);
        std::cout << "Cartão movido com sucesso." << std::endl;

        // Excluir um cartão
        servicosCartao.excluirCartao("CD34", emailUsuario);
        std::cout << "Cartão excluído com sucesso." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro em testeCartao: " << e.what() << std::endl;
    }
}


void testarFluxoCompleto() {
    // Instância da tela inicial
    TelaInicial telaInicial;

    // Exibir tela inicial
    // A lógica interna da TelaInicial cuidará de chamar as telas de Cadastro, Login e Quadros conforme necessário.
    telaInicial.exibir();

    // O controle retorna aqui após a conclusão do fluxo na tela inicial.
}

int main() {
    try {
        testarFluxoCompleto();
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}


