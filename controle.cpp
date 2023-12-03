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
    : servicosQuadro(dbPath) {}

std::vector<Quadro> ControladorQuadros::obterQuadros(const std::string& emailUsuario) {
    // Aqui, você implementaria a lógica para obter os quadros do usuário.
    // Por exemplo, chamando um método do serviço `servicosQuadro` que
    // retorna os quadros associados ao email do usuário.
    return std::vector<Quadro>();  // Exemplo de retorno vazio. Substitua pela lógica real.
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