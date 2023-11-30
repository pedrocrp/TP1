#include "servicos.hpp"
#include <stdexcept>
#include "entidades.h"
#include <iostream>


// SERVICOS CONTA

ServicosConta::ServicosConta(const std::string& dbPath) : dbManager(dbPath) {
    if (!dbManager.abrirConexao()) {
        throw std::runtime_error("Falha ao abrir conexão com o banco de dados.");
    }
}


void ServicosConta::criarUsuario(const Conta& conta) {
    // Verifica se o email já existe
    std::string sqlVerifica = "SELECT Email FROM Conta WHERE Email = '" + conta.getEmail() + "';";
    auto resultadoVerifica = dbManager.executarConsulta(sqlVerifica);
    if (resultadoVerifica && !resultadoVerifica->empty()) {
        throw std::runtime_error("Email já está em uso.");
    }


    std::string sql = "INSERT INTO Conta (Email, Nome, Senha) VALUES ('" + conta.getEmail() + "', '" + conta.getNome() + "', '" + conta.getSenha() + "');";
    dbManager.executarConsulta(sql);
}


void ServicosConta::editarUsuario(const std::string& email, const std::string& novoNome, const std::string& novaSenha) {
    // Verificar se a conta existe
    std::string sqlVerificacao = "SELECT Email FROM Conta WHERE Email = '" + email + "';";
    auto resultadoVerificacao = dbManager.executarConsulta(sqlVerificacao);
    if (!resultadoVerificacao || resultadoVerificacao->empty()) {
        throw std::runtime_error("Conta não encontrada para edição.");
    }
    
    std::string sqlAtualizacao = "UPDATE Conta SET ";
    bool primeiroCampo = true;

    if (!novoNome.empty()) {
        sqlAtualizacao += (primeiroCampo ? "" : ", ") + std::string("Nome = '") + novoNome + "'";
        primeiroCampo = false;
    }

    if (!novaSenha.empty()) {
        sqlAtualizacao += (primeiroCampo ? "" : ", ") + std::string("Senha = '") + novaSenha + "'";
        primeiroCampo = false;
    }

    if (primeiroCampo) {
        throw std::runtime_error("Nenhum campo fornecido para atualização.");
    }

    sqlAtualizacao += " WHERE Email = '" + email + "';";
    dbManager.executarConsulta(sqlAtualizacao);
}


void ServicosConta::excluirUsuario(const std::string& email) {
    // Verificar se a conta existe
    std::string sqlVerificacao = "SELECT Email FROM Conta WHERE Email = '" + email + "';";
    auto resultadoVerificacao = dbManager.executarConsulta(sqlVerificacao);
    if (!resultadoVerificacao || resultadoVerificacao->empty()) {
        throw std::runtime_error("Conta não encontrada para exclusão.");
    }

    // Executar exclusão
    std::string sqlExclusao = "DELETE FROM Conta WHERE Email = '" + email + "';";
    dbManager.executarConsulta(sqlExclusao);
}


std::optional<Conta> ServicosConta::visualizarUsuario(const std::string& email) {
    // Verificar se a conta existe
    std::string sqlVerificacao = "SELECT Email FROM Conta WHERE Email = '" + email + "';";
    auto resultadoVerificacao = dbManager.executarConsulta(sqlVerificacao);
    if (!resultadoVerificacao || resultadoVerificacao->empty()) {
        return std::nullopt; // Conta não encontrada.
    }

    // Buscar informações da conta
    std::string sql = "SELECT Nome, Senha FROM Conta WHERE Email = '" + email + "';";
    auto resultado = dbManager.executarConsulta(sql);

    // Verifica se o resultado é válido e não vazio
    if (!resultado || resultado->empty()) {
        return std::nullopt; // Conta não encontrada.
    }

    Email emailObjeto;
    Texto nome;
    Senha senha;

    // Configura os valores dos objetos de domínio
    emailObjeto.setEmail(email);
    nome.setTexto((*resultado)[0]["Nome"]);
    senha.setSenha((*resultado)[0]["Senha"]);

    // Cria e retorna um objeto Conta
    Conta conta(emailObjeto, nome, senha);
    return conta;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////


// SERVICOS QUADRO


ServicosQuadro::ServicosQuadro(const std::string& dbPath) : dbManager(dbPath) {
    if (!dbManager.abrirConexao()) {
        throw std::runtime_error("Falha ao abrir conexão com o banco de dados.");
    }
}


void ServicosQuadro::criarQuadro(const std::string& emailConta, const Quadro& quadro) {
    std::string sql = "INSERT INTO Quadro (Codigo, EmailConta, Nome, Descricao, Limite) VALUES ('" + quadro.getCodigo() + "', '" + emailConta + "', '" + quadro.getNome() + "', '" + quadro.getDescricao() + "', " + std::to_string(quadro.getLimite()) + ");";
    dbManager.executarConsulta(sql);
}


void ServicosQuadro::editarQuadro(const std::string& codigo, const std::optional<std::string>& novoNome, const std::optional<std::string>& novaDescricao, const std::optional<int>& novoLimite) {
    std::string sqlAtualizacao = "UPDATE Quadro SET ";
    bool primeiroCampo = true;

    if (novoNome) {
        sqlAtualizacao += (primeiroCampo ? "" : ", ") + std::string("Nome = '") + *novoNome + "'";
        primeiroCampo = false;
    }

    if (novaDescricao) {
        sqlAtualizacao += (primeiroCampo ? "" : ", ") + std::string("Descricao = '") + *novaDescricao + "'";
        primeiroCampo = false;
    }

    if (novoLimite) {
        sqlAtualizacao += (primeiroCampo ? "" : ", ") + std::string("Limite = ") + std::to_string(*novoLimite);
        primeiroCampo = false;
    }

    if (primeiroCampo) {
        throw std::runtime_error("Nenhum campo fornecido para atualização.");
    }

    sqlAtualizacao += " WHERE Codigo = '" + codigo + "';";
    dbManager.executarConsulta(sqlAtualizacao);
}


void ServicosQuadro::excluirQuadro(const std::string& codigo) {
    std::string sql = "DELETE FROM Quadro WHERE Codigo = '" + codigo + "';";
    dbManager.executarConsulta(sql);
}


std::optional<Quadro> ServicosQuadro::visualizarQuadro(const std::string& codigo) {
    // Prepara e executa a consulta SQL
    std::string sql = "SELECT Nome, Descricao, Limite FROM Quadro WHERE Codigo = '" + codigo + "';";
    auto resultado = dbManager.executarConsulta(sql);

    // Verifica se o resultado é válido e não vazio
    if (!resultado || resultado->empty()) {
        return std::nullopt; // Quadro não encontrado.
    }

    // Configura os objetos de domínio com base nos resultados da consulta
    Texto nome, descricao;
    Limite limite;
    Codigo id;

    id.setCodigo(codigo);
    nome.setTexto((*resultado)[0]["Nome"]);
    descricao.setTexto((*resultado)[0]["Descricao"]);
    limite.setLimite(std::stoi((*resultado)[0]["Limite"]));


    // Cria e retorna um objeto Quadro
    Quadro quadro(id, nome, descricao, limite);
    return quadro;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////


// SERVICOS CARTAO


ServicosCartao::ServicosCartao(const std::string& dbPath) : dbManager(dbPath) {
    if (!dbManager.abrirConexao()) {
        throw std::runtime_error("Falha ao abrir conexão com o banco de dados.");
    }
}

void ServicosCartao::criarCartao(const Cartao& cartao, const std::string& codigoQuadro) {
    std::string sql = "INSERT INTO Cartao (Codigo, CodigoQuadro, Nome, Descricao, Coluna) VALUES ('" +
                      cartao.getCodigo() + "', '" + codigoQuadro + "', '" + cartao.getNome() + "', '" +
                      cartao.getDescricao() + "', '" + cartao.getColuna() + "');";

    try {
        dbManager.executarConsulta(sql);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao criar cartão: " + std::string(e.what()));
    }
}


std::optional<Cartao> ServicosCartao::visualizarCartao(const std::string& codigo) {
    std::string sql = "SELECT Nome, Descricao, Coluna FROM Cartao WHERE Codigo = '" + codigo + "';";
    auto resultado = dbManager.executarConsulta(sql);

    if (!resultado || resultado->empty()) {
        return std::nullopt; // Cartão não encontrado.
    }

    Texto nome, descricao;
    Coluna coluna;
    nome.setTexto(resultado->at(0)["Nome"]);
    descricao.setTexto(resultado->at(0)["Descricao"]);
    coluna.setEstado(resultado->at(0)["Coluna"]);

    Codigo codigoObj;
    codigoObj.setCodigo(codigo);

    Cartao cartao(codigoObj, nome, descricao, coluna);
    return cartao;
}


void ServicosCartao::moverCartao(const std::string& codigo, const std::string& novaColuna) {
    std::string sql = "UPDATE Cartao SET Coluna = '" + novaColuna + "' WHERE Codigo = '" + codigo + "';";
    try {
        dbManager.executarConsulta(sql);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao mover cartão: " + std::string(e.what()));
    }
}


void ServicosCartao::excluirCartao(const std::string& codigo) {
    std::string sql = "DELETE FROM Cartao WHERE Codigo = '" + codigo + "';";
    try {
        dbManager.executarConsulta(sql);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao excluir cartão: " + std::string(e.what()));
    }
}




