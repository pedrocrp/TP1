#include "servicos.hpp"
#include "entidades.h"
#include "dominios.h"
#include <iostream>
#include "controle.hpp"

ControladorCadastro::ControladorCadastro(const std::string& dbPath) : servicosConta(dbPath) {}

bool ControladorCadastro::cadastrarUsuario(const std::string& emailStr, const std::string& nomeStr, const std::string& senhaStr) {
    try {
        Email email;
        email.setEmail(emailStr);

        Texto nome;
        nome.setTexto(nomeStr);

        Senha senha;
        senha.setSenha(senhaStr);

        Conta novaConta(email, nome, senha);
        servicosConta.criarUsuario(novaConta);

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao cadastrar usuário: " << e.what() << std::endl;
        return false;
    }
}


ControladorLogin::ControladorLogin(const std::string& dbPath) : dbManager(dbPath) {
    if (!dbManager.abrirConexao()) {
        throw std::runtime_error("Erro ao abrir conexão com o banco de dados.");
    }
}

bool ControladorLogin::autenticar(const std::string& email, const std::string& senha) {
    // Preparar a consulta SQL para verificar se existe uma conta com o email e senha fornecidos
    std::string sql = "SELECT * FROM Conta WHERE Email = '" + email + "' AND Senha = '" + senha + "';";

    auto resultado = dbManager.executarConsulta(sql);
    
    // Se o resultado não for nulo e não estiver vazio, a autenticação é bem-sucedida
    if (resultado && !resultado->empty()) {
        return true;
    } else {
        std::cerr << "Credenciais inválidas ou conta não encontrada." << std::endl;
        return false;
    }
}


// Construtor
ControladorQuadros::ControladorQuadros(const std::string& dbPath)
    : servicosQuadro(dbPath), dbManager(dbPath) {}

std::optional<QuadroComCartoes> ControladorQuadros::visualizarQuadro(const std::string& emailUsuario, const std::string& codigoQuadro) {
    auto quadroOpt = servicosQuadro.visualizarQuadro(emailUsuario, codigoQuadro);

    if (!quadroOpt) {
        return std::nullopt; // Quadro não encontrado ou não pertence ao usuário.
    }

    // Recupera os códigos dos cartões associados ao quadro
    std::vector<std::string> codigosCartoes;
    std::string sqlCartoes = "SELECT Codigo FROM Cartao WHERE CodigoQuadro = '" + codigoQuadro + "';";
    auto resultadoCartoes = dbManager.executarConsulta(sqlCartoes);

    if (resultadoCartoes) {
        for (const auto& linha : *resultadoCartoes) {
            auto it = linha.find("Codigo");
            if (it != linha.end()) {
                codigosCartoes.push_back(it->second);
            } else {
                std::cerr << "Erro: Código do cartão não encontrado para o quadro '" << codigoQuadro << "'.\n";
            }
        }
    }

    QuadroComCartoes quadroComCartoes;
    quadroComCartoes.quadro = *quadroOpt;
    quadroComCartoes.codigosCartoes = codigosCartoes;

    return quadroComCartoes;
}

bool ControladorQuadros::criarQuadro(const std::string& emailUsuario, 
                                     const std::string& codigoStr, 
                                     const std::string& nomeStr, 
                                     const std::string& descricaoStr, 
                                     int limiteVal) {
    try {
        Codigo codigo;
        codigo.setCodigo(codigoStr);

        Texto nome;
        nome.setTexto(nomeStr);

        Texto descricao;
        descricao.setTexto(descricaoStr);

        Limite limite;
        limite.setLimite(limiteVal);

        Quadro novoQuadro(codigo, nome, descricao, limite);
        servicosQuadro.criarQuadro(emailUsuario, novoQuadro);

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao criar quadro: " << e.what() << std::endl;
        return false;
    }
}

// Método para editar um quadro
bool ControladorQuadros::editarQuadro(const std::string& emailUsuario, 
                                      const std::string& codigoQuadro, 
                                      const std::optional<std::string>& novoNome, 
                                      const std::optional<std::string>& novaDescricao, 
                                      const std::optional<int>& novoLimite) {
    try {
        // Validar e preparar dados para atualização
        Texto nome;
        Texto descricao;
        Limite limite;

        // Verifica e valida cada campo opcional
        if (novoNome.has_value()) {
            nome.setTexto(novoNome.value());
        }
        if (novaDescricao.has_value()) {
            descricao.setTexto(novaDescricao.value());
        }
        if (novoLimite.has_value()) {
            limite.setLimite(novoLimite.value());
        }

        // Chamar a camada de serviço para editar o quadro
        servicosQuadro.editarQuadro(emailUsuario, codigoQuadro, novoNome, novaDescricao, novoLimite);

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao editar quadro: " << e.what() << std::endl;
        return false;
    }
}

bool ControladorQuadros::excluirQuadro(const std::string& emailUsuario, const std::string& codigoQuadro) {
    try {
        // Lógica para excluir o quadro
        servicosQuadro.excluirQuadro(emailUsuario, codigoQuadro);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao excluir quadro: " << e.what() << std::endl;
        return false;
    }
}



ControladorCartao::ControladorCartao(const std::string& dbPath)
    : servicosCartao(dbPath), dbManager(dbPath) {}

bool ControladorCartao::criarCartao(const std::string& codigoQuadro, const std::string& codigoCartao, 
                                     const std::string& nome, const std::string& descricao, const std::string& coluna) {
    // Implementação da lógica para criar um cartão
    // Utilize as classes de entidades e domínios para validações
    return true;
}

bool ControladorCartao::editarCartao(const std::string& codigoQuadro, const std::string& codigoCartao, 
                                      const std::optional<std::string>& novoNome, 
                                      const std::optional<std::string>& novaDescricao, 
                                      const std::optional<std::string>& novaColuna) {
    // Implementação da lógica para editar um cartão
    // Utilize as classes de entidades e domínios para validações
    return true;
}

bool ControladorCartao::excluirCartao(const std::string& codigoQuadro, const std::string& codigoCartao) {
    // Implementação da lógica para excluir um cartão
     return true;
}

// std::optional<Cartao> ControladorCartoes::visualizarCartao(const std::string& codigoQuadro, const std::string& codigoCartao) {
//     // Implementação da lógica para visualizar um cartão
//     // Retorne os detalhes do cartão ou std::nullopt se o cartão não for encontrado
// }

