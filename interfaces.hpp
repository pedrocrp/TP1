#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include <string>
#include <vector>
#include "entidades.h"
#include <optional>

// Interface para autenticação
class IAutenticacao {
public:
    virtual bool autenticar(const std::string& email, const std::string& senha) = 0;
    virtual ~IAutenticacao() {}
};

// Interface para gerenciamento de usuários
class IGerenciamentoUsuario {
public:
    virtual void criarUsuario(const Conta& conta) = 0;
    virtual void editarUsuario(const std::string& email, const std::string& novoNome, const std::string& novaSenha) = 0;
    virtual void excluirUsuario(const std::string& email) = 0;
    virtual ~IGerenciamentoUsuario() {}
};

// Interface para gerenciamento de quadros (boards)
class IGerenciamentoQuadro {
public:
    virtual void criarQuadro(const std::string& emailConta, const Quadro& quadro) = 0;
    virtual std::optional<Quadro> visualizarQuadro(const std::string& emailUsuario, const std::string& codigo) = 0;
    virtual void editarQuadro(const std::string& emailUsuario, const std::string& codigo, const std::optional<std::string>& novoNome, const std::optional<std::string>& novaDescricao, const std::optional<int>& novoLimite) = 0;
    virtual void excluirQuadro(const std::string& emailUsuario, const std::string& codigo) = 0;
    virtual ~IGerenciamentoQuadro() {}
};

// Interface para gerenciamento de cartões (cards)
class IGerenciamentoCartao {
public:
    virtual void criarCartao(const Cartao& cartao, const std::string& codigoQuadro, const std::string& emailUsuario) = 0;
    virtual std::optional<Cartao> visualizarCartao(const std::string& codigoCartao, const std::string& emailUsuario) = 0;
    virtual void moverCartao(const std::string& codigoCartao, const std::string& novaColuna, const std::string& emailUsuario) = 0;
    virtual void excluirCartao(const std::string& codigoCartao, const std::string& emailUsuario) = 0;
    virtual ~IGerenciamentoCartao() {}
};

#endif // INTERFACES_HPP_INCLUDED
