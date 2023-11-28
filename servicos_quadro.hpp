#ifndef SERVICOS_QUADRO_HPP
#define SERVICOS_QUADRO_HPP

#include "DatabaseManager.hpp"
#include "entidades.h"
#include <string>
#include <optional>

class ServicosQuadro {
public:
    explicit ServicosQuadro(const std::string& dbPath);

    void criarQuadro(const std::string& codigo, const std::string& emailConta, const std::string& nome, const std::string& descricao, int limite);
    void editarQuadro(const std::string& codigo, const std::optional<std::string>& novoNome, const std::optional<std::string>& novaDescricao, const std::optional<int>& novoLimite);
    void excluirQuadro(const std::string& codigo);
    std::optional<Quadro> visualizarQuadro(const std::string& codigo);

private:
    DatabaseManager dbManager;
};

#endif // SERVICOS_QUADRO_HPP
