#include "servicos_conta.hpp"
#include <stdexcept>
#include "entidades.h"

ServicosConta::ServicosConta(const std::string& dbPath) : dbManager(dbPath) {
    if (!dbManager.abrirConexao()) {
        throw std::runtime_error("Falha ao abrir conexão com o banco de dados.");
    }
}

void ServicosConta::criarUsuario(const std::string& nome, const std::string& email, const std::string& senha) {
    Conta conta;

    try {
        // Criando e validando os domínios
        Email emailObj;
        emailObj.setEmail(email);
        conta.setEmail(emailObj);

        Texto nomeObj;
        nomeObj.setTexto(nome);
        conta.setNome(nomeObj);

        Senha senhaObj;
        senhaObj.setSenha(senha);
        conta.setSenha(senhaObj);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro de validação: " + std::string(e.what()));
    }

    std::string sql = "INSERT INTO Conta (Email, Nome, Senha) VALUES ('" + 
                      conta.getEmail() + "', '" + conta.getNome() + "', '" + conta.getSenha() + "');";

    try {
        dbManager.executarConsulta(sql);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao criar conta no banco de dados. Detalhe: " + std::string(e.what()));
    }
}

void ServicosConta::editarUsuario(const std::string& email, const std::string& novoNome, const std::string& novaSenha) {
    std::string sql = "UPDATE Conta SET Nome = '" + novoNome + "', Senha = '" + novaSenha + "' WHERE Email = '" + email + "';";
    auto resultado = dbManager.executarConsulta(sql);
    if (!resultado) {
        throw std::runtime_error("Erro ao editar conta.");
    }
}

void ServicosConta::excluirUsuario(const std::string& email) {
    std::string sql = "DELETE FROM Conta WHERE Email = '" + email + "';";
    auto resultado = dbManager.executarConsulta(sql);
    if (!resultado) {
        throw std::runtime_error("Erro ao excluir conta.");
    }
}

std::optional<Conta> ServicosConta::visualizarUsuario(const std::string& email) {
    std::string sql = "SELECT Nome, Senha FROM Conta WHERE Email = '" + email + "';";
    auto resultado = dbManager.executarConsulta(sql);

    if (!resultado || resultado->empty()) {
        return std::nullopt; // Conta não encontrada.
    }

    Email emailObjeto;
    Texto nome;
    Senha senha;

    emailObjeto.setEmail(email);
    nome.setTexto(resultado->at(0).at("Nome"));
    senha.setSenha(resultado->at(0).at("Senha"));

    Conta conta(emailObjeto, nome, senha);
    return conta;
    }

