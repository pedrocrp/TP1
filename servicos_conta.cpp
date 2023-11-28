#include "servicos_conta.hpp"
#include <stdexcept>
#include "entidades.h"
#include <iostream>

ServicosConta::ServicosConta(const std::string& dbPath) : dbManager(dbPath) {
    if (!dbManager.abrirConexao()) {
        throw std::runtime_error("Falha ao abrir conexão com o banco de dados.");
    }
}

void ServicosConta::criarUsuario(const std::string& email, const std::string& nome,const std::string& senha) {
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

    // Verificar se o email já está em uso
    std::string sqlVerificacao = "SELECT Email FROM Conta WHERE Email = '" + email + "';";
    auto resultadoVerificacao = dbManager.executarConsulta(sqlVerificacao);
    if (resultadoVerificacao && !resultadoVerificacao->empty()) {
        throw std::runtime_error("Email já está em uso.");
    }

    try {
        // Inserir a nova conta
        std::string sqlInsercao = "INSERT INTO Conta (Email, Nome, Senha) VALUES (?, ?, ?);";
        std::cout << "Email: " << conta.getEmail() << std::endl;
        dbManager.prepararConsulta(sqlInsercao);
        dbManager.vincularValor(1, conta.getEmail());
        dbManager.vincularValor(2, conta.getNome());
        dbManager.vincularValor(3, conta.getSenha());
        dbManager.executarConsultaPreparada();
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao criar conta no banco de dados. Detalhe: " + std::string(e.what()));
    }
}


void ServicosConta::editarUsuario(const std::string& email, const std::string& novoNome, const std::string& novaSenha) {
    // Verificar se a conta existe
    std::string sqlVerificacao = "SELECT * FROM Conta WHERE Email = '" + email + "';";
    auto resultadoVerificacao = dbManager.executarConsulta(sqlVerificacao);
    if (!resultadoVerificacao || resultadoVerificacao->empty()) {
        throw std::runtime_error("Conta não encontrada para edição.");
    }

    // Preparar a consulta SQL de atualização
    std::string sqlAtualizacao = "UPDATE Conta SET ";
    std::vector<std::string> valores;

    // Atualizar o nome se fornecido
    if (!novoNome.empty()) {
        Texto nomeObj;
        nomeObj.setTexto(novoNome);
        sqlAtualizacao += "Nome = ?, ";
        valores.push_back(nomeObj.getTexto());
    }

    // Atualizar a senha se fornecida
    if (!novaSenha.empty()) {
        Senha senhaObj;
        senhaObj.setSenha(novaSenha);
        sqlAtualizacao += "Senha = ?, ";
        valores.push_back(senhaObj.getSenha());
    }

    // Remover a última vírgula e adicionar a cláusula WHERE
    if (!valores.empty()) {
        sqlAtualizacao.pop_back(); // Remove o último espaço
        sqlAtualizacao.pop_back(); // Remove a última vírgula
        sqlAtualizacao += " WHERE Email = ?";
        valores.push_back(email);

        // Executar a consulta
        try {
            dbManager.prepararConsulta(sqlAtualizacao);
            int posicao = 1;
            for (const auto& valor : valores) {
                dbManager.vincularValor(posicao++, valor);
            }
            dbManager.executarConsultaPreparada();
        } catch (const std::exception& e) {
            throw std::runtime_error("Erro ao editar conta: " + std::string(e.what()));
        }
    } else {
        throw std::runtime_error("Nenhum campo para atualizar.");
    }
}


void ServicosConta::excluirUsuario(const std::string& email) {
    // Verificar se a conta existe
    std::string sqlVerificacao = "SELECT Email FROM Conta WHERE Email = '" + email + "';";
    auto resultadoVerificacao = dbManager.executarConsulta(sqlVerificacao);

    if (!resultadoVerificacao || resultadoVerificacao->empty()) {
        throw std::runtime_error("Conta não encontrada para exclusão.");
    }

    // Se a conta existir, proceder com a exclusão
    std::string sqlExclusao = "DELETE FROM Conta WHERE Email = ?;";
    dbManager.prepararConsulta(sqlExclusao);
    dbManager.vincularValor(1, email);
    if (!dbManager.executarConsultaPreparada()) {
        throw std::runtime_error("Erro ao excluir conta.");
    }
}



std::optional<Conta> ServicosConta::visualizarUsuario(const std::string& email) {
    std::string sql = "SELECT Nome, Senha FROM Conta WHERE Email = '" + email + "';";
    auto resultado = dbManager.executarConsulta(sql);

    if (!resultado.has_value() || resultado.value().empty()) {
        return std::nullopt; // Conta não encontrada.
    }

    Email emailObjeto;
    Texto nome;
    Senha senha;

    emailObjeto.setEmail(email);
    nome.setTexto(resultado.value().at(0).at("Nome"));
    senha.setSenha(resultado.value().at(0).at("Senha"));

    Conta conta(emailObjeto, nome, senha);
    return conta;
}

