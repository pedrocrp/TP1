#ifndef SERVICOS_HPP_INCLUDED
#define SERVICOS_HPP_INCLUDED

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
    void criarUsuario(const Conta& conta) override; // Correção aqui
    void editarUsuario(const std::string& email, const std::string& novoNome, const std::string& novaSenha) override;
    void excluirUsuario(const std::string& email) override;
    std::optional<Conta> visualizarUsuario(const std::string& email);
};


class ServicosQuadro {
public:
    
    ServicosQuadro(const std::string& dbPath);
    void criarQuadro(const std::string& emailConta, const Quadro& quadro);
    void editarQuadro(const std::string& codigo, const std::optional<std::string>& novoNome, const std::optional<std::string>& novaDescricao, const std::optional<int>& novoLimite);
    void excluirQuadro(const std::string& codigo);
    std::optional<Quadro> visualizarQuadro(const std::string& codigo);

private:
    DatabaseManager dbManager;
};


class ServicosCartao : public IGerenciamentoCartao {
private:
    DatabaseManager dbManager;

public:
    ServicosCartao(const std::string& dbPath);
    void criarCartao(const Cartao& cartao, const std::string& codigoQuadro) override;
    std::optional<Cartao> visualizarCartao(const std::string& codigo) override;
    void moverCartao(const std::string& codigo, const std::string& novaColuna) override;
    void excluirCartao(const std::string& codigo) override;
};




#endif // SERVICOS_HPP_INCLUDED
