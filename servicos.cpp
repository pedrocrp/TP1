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
    // Verificar se a conta existe
    std::string sqlVerificacaoConta = "SELECT Email FROM Conta WHERE Email = '" + emailConta + "';";
    auto resultadoVerificacaoConta = dbManager.executarConsulta(sqlVerificacaoConta);
    if (!resultadoVerificacaoConta || resultadoVerificacaoConta->empty()) {
        throw std::runtime_error("Conta associada ao quadro não encontrada.");
    }

    // Verificar se o código do quadro já está em uso
    std::string sqlVerificaCodigo = "SELECT Codigo FROM Quadro WHERE Codigo = '" + quadro.getCodigo() + "';";
    auto resultadoVerificaCodigo = dbManager.executarConsulta(sqlVerificaCodigo);
    if (resultadoVerificaCodigo && !resultadoVerificaCodigo->empty()) {
        throw std::runtime_error("Código do quadro já está em uso.");
    }

    // Inserir quadro no banco de dados
    std::string sql = "INSERT INTO Quadro (Codigo, EmailConta, Nome, Descricao, Limite) VALUES ('" + 
                      quadro.getCodigo() + "', '" + emailConta + "', '" + quadro.getNome() + "', '" + 
                      quadro.getDescricao() + "', " + std::to_string(quadro.getLimite()) + ");";
    dbManager.executarConsulta(sql);
}


void ServicosQuadro::editarQuadro(const std::string& emailUsuario, const std::string& codigo, const std::optional<std::string>& novoNome, const std::optional<std::string>& novaDescricao, const std::optional<int>& novoLimite) {
    // Verificar se o quadro pertence ao usuário
    std::string sqlVerificaPropriedade = "SELECT EmailConta FROM Quadro WHERE Codigo = '" + codigo + "' AND EmailConta = '" + emailUsuario + "';";
    auto resultadoPropriedade = dbManager.executarConsulta(sqlVerificaPropriedade);
    if (!resultadoPropriedade || resultadoPropriedade->empty()) {
        throw std::runtime_error("Quadro não encontrado ou não pertence ao usuário.");
    }

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


void ServicosQuadro::excluirQuadro(const std::string& emailUsuario, const std::string& codigo) {
    // Verificar se o quadro pertence ao usuário
    std::string sqlVerificaPropriedade = "SELECT EmailConta FROM Quadro WHERE Codigo = '" + codigo + "' AND EmailConta = '" + emailUsuario + "';";
    auto resultadoPropriedade = dbManager.executarConsulta(sqlVerificaPropriedade);
    if (!resultadoPropriedade || resultadoPropriedade->empty()) {
        throw std::runtime_error("Quadro não encontrado ou não pertence ao usuário.");
    }

    // Excluir quadro
    std::string sqlExclusao = "DELETE FROM Quadro WHERE Codigo = '" + codigo + "';";
    dbManager.executarConsulta(sqlExclusao);
}


std::optional<Quadro> ServicosQuadro::visualizarQuadro(const std::string& emailUsuario, const std::string& codigo) {
    // Verificar se o quadro pertence ao usuário
    std::string sqlVerificaPropriedade = "SELECT EmailConta FROM Quadro WHERE Codigo = '" + codigo + "' AND EmailConta = '" + emailUsuario + "';";
    auto resultadoPropriedade = dbManager.executarConsulta(sqlVerificaPropriedade);
    if (!resultadoPropriedade || resultadoPropriedade->empty()) {
        return std::nullopt; // Quadro não encontrado ou não pertence ao usuário.
    }

    // Executar consulta para buscar informações do quadro
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

void ServicosCartao::criarCartao(const Cartao& cartao, const std::string& codigoQuadro, const std::string& emailUsuario) {
    // Verificar se o quadro existe e pertence ao usuário
    std::string sqlVerificaQuadro = "SELECT Codigo FROM Quadro WHERE Codigo = '" + codigoQuadro + "' AND EmailConta = '" + emailUsuario + "';";
    auto resultadoVerificaQuadro = dbManager.executarConsulta(sqlVerificaQuadro);
    if (!resultadoVerificaQuadro || resultadoVerificaQuadro->empty()) {
        throw std::runtime_error("Quadro não encontrado ou não pertence ao usuário.");
    }

    // Verificar se o código do cartão já está em uso
    std::string sqlVerificaCodigo = "SELECT Codigo FROM Cartao WHERE Codigo = '" + cartao.getCodigo() + "';";
    auto resultadoVerificaCodigo = dbManager.executarConsulta(sqlVerificaCodigo);
    if (resultadoVerificaCodigo && !resultadoVerificaCodigo->empty()) {
        throw std::runtime_error("Código do cartão já está em uso.");
    }

    // Inserir cartão no banco de dados
    std::string sql = "INSERT INTO Cartao (Codigo, CodigoQuadro, Nome, Descricao, Coluna) VALUES ('" +
                      cartao.getCodigo() + "', '" + codigoQuadro + "', '" + cartao.getNome() + "', '" +
                      cartao.getDescricao() + "', '" + cartao.getColuna() + "');";
    dbManager.executarConsulta(sql);
}


std::optional<Cartao> ServicosCartao::visualizarCartao(const std::string& codigoCartao, const std::string& emailUsuario) {
    // Verificar se o cartão existe e pertence a um quadro do usuário
    std::string sqlVerificaCartao = "SELECT Cartao.Codigo, Cartao.Nome, Cartao.Descricao, Cartao.Coluna FROM Cartao "
                                    "INNER JOIN Quadro ON Cartao.CodigoQuadro = Quadro.Codigo "
                                    "WHERE Cartao.Codigo = '" + codigoCartao + "' AND Quadro.EmailConta = '" + emailUsuario + "';";
    auto resultado = dbManager.executarConsulta(sqlVerificaCartao);

    if (!resultado || resultado->empty()) {
        return std::nullopt; // Cartão não encontrado ou não pertence ao quadro do usuário.
    }

    Texto nome, descricao;
    Coluna coluna;
    nome.setTexto(resultado->at(0)["Nome"]);
    descricao.setTexto(resultado->at(0)["Descricao"]);
    coluna.setEstado(resultado->at(0)["Coluna"]);

    Codigo codigoObj;
    codigoObj.setCodigo(codigoCartao);

    Cartao cartao(codigoObj, nome, descricao, coluna);
    return cartao;
}


void ServicosCartao::moverCartao(const std::string& codigoCartao, const std::string& novaColuna, const std::string& emailUsuario) {
    // Verificar se o cartão existe e pertence a um quadro do usuário
    std::string sqlVerificaCartao = "SELECT Cartao.Codigo FROM Cartao "
                                    "INNER JOIN Quadro ON Cartao.CodigoQuadro = Quadro.Codigo "
                                    "WHERE Cartao.Codigo = '" + codigoCartao + "' AND Quadro.EmailConta = '" + emailUsuario + "';";
    auto resultadoVerificaCartao = dbManager.executarConsulta(sqlVerificaCartao);
    if (!resultadoVerificaCartao || resultadoVerificaCartao->empty()) {
        throw std::runtime_error("Cartão não encontrado ou não pertence ao quadro do usuário.");
    }

    // Atualizar a coluna do cartão no banco de dados
    std::string sqlAtualizacao = "UPDATE Cartao SET Coluna = '" + novaColuna + "' WHERE Codigo = '" + codigoCartao + "';";
    dbManager.executarConsulta(sqlAtualizacao);
}


void ServicosCartao::excluirCartao(const std::string& codigoCartao, const std::string& emailUsuario) {
    // Verificar se o cartão existe e pertence a um quadro do usuário
    std::string sqlVerificaCartao = "SELECT Cartao.Codigo FROM Cartao "
                                    "INNER JOIN Quadro ON Cartao.CodigoQuadro = Quadro.Codigo "
                                    "WHERE Cartao.Codigo = '" + codigoCartao + "' AND Quadro.EmailConta = '" + emailUsuario + "';";
    auto resultadoVerificaCartao = dbManager.executarConsulta(sqlVerificaCartao);
    if (!resultadoVerificaCartao || resultadoVerificaCartao->empty()) {
        throw std::runtime_error("Cartão não encontrado ou não pertence ao quadro do usuário.");
    }

    // Excluir o cartão do banco de dados
    std::string sqlExclusao = "DELETE FROM Cartao WHERE Codigo = '" + codigoCartao + "';";
    dbManager.executarConsulta(sqlExclusao);
}




