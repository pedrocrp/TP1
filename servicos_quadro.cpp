#include "servicos_quadro.hpp"
#include <stdexcept>
#include <iostream>
#include "entidades.h"
#include "dominios.h"

ServicosQuadro::ServicosQuadro(const std::string& dbPath) : dbManager(dbPath) {
    if (!dbManager.abrirConexao()) {
        throw std::runtime_error("Falha ao abrir conexão com o banco de dados.");
    }
}

void ServicosQuadro::criarQuadro(const std::string& codigo, const std::string& emailConta, const std::string& nome, const std::string& descricao, int limite) {
    // Criar um objeto Quadro
    Quadro quadro;

    try {
        Codigo codigoObj;
        codigoObj.setCodigo(codigo); // Definindo o valor do código
        Texto nomeObj;
        nomeObj.setTexto(nome);
        Texto descricaoObj;
        descricaoObj.setTexto(descricao);
        Limite limiteObj;
        limiteObj.setLimite(limite);

        quadro.setCodigo(codigoObj);
        quadro.setNome(nomeObj);
        quadro.setDescricao(descricaoObj);
        quadro.setLimite(limiteObj);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro de validação: " + std::string(e.what()));
    }

    // Inserir o quadro no banco de dados
    try {
        std::string sqlInsercao = "INSERT INTO Quadro (Codigo, EmailConta, Nome, Descricao, Limite) VALUES (?, ?, ?, ?, ?);";
        dbManager.prepararConsulta(sqlInsercao);
        dbManager.vincularValor(1, quadro.getCodigo());
        dbManager.vincularValor(2, emailConta); // Assumindo que o email da conta está correto e não precisa de validação adicional
        dbManager.vincularValor(3, quadro.getNome());
        dbManager.vincularValor(4, quadro.getDescricao());
        dbManager.vincularValor(5, std::to_string(quadro.getLimite()));
        dbManager.executarConsultaPreparada();
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao criar quadro no banco de dados. Detalhe: " + std::string(e.what()));
    }
}



void ServicosQuadro::editarQuadro(const std::string& codigo, const std::optional<std::string>& novoNome, const std::optional<std::string>& novaDescricao, const std::optional<int>& novoLimite) {
    // Implementar a lógica para editar um quadro existente
    // Validar os novos dados e atualizar no banco de dados
}

void ServicosQuadro::excluirQuadro(const std::string& codigo) {
    // Implementar a lógica para excluir um quadro
    // Verificar relações e deletar do banco de dados
}

std::optional<Quadro> ServicosQuadro::visualizarQuadro(const std::string& codigo) {
    // Implementar a lógica para visualizar detalhes de um quadro
    // Consultar no banco de dados e retornar os dados
}

// Demais implementações conforme necessário...
