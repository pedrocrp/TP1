#ifndef SERVICOS_CONTA_HPP_INCLUDED
#define SERVICOS_CONTA_HPP_INCLUDED

#include "interfaces.hpp"
#include <optional>
#include <string>
#include "entidades.h"
#include "DatabaseManager.hpp"

class ServicosConta : public IGerenciamentoUsuario {
private:
    DatabaseManager dbManager;  // Declarando o campo dbManager
public:
    ServicosConta(const std::string& dbPath);
    void criarUsuario(const std::string& nome, const std::string& email, const std::string& senha) override;
    void editarUsuario(const std::string& email, const std::string& novoNome, const std::string& novaSenha) override;
    void excluirUsuario(const std::string& email) override;
    std::optional<Conta> visualizarUsuario(const std::string& email);
};

#endif // SERVICOS_CONTA_HPP_INCLUDED
