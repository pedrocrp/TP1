#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include <string>
#include <vector>

// Interface para autenticação
class IAutenticacao {
public:
    virtual bool autenticar(const std::string& email, const std::string& senha) = 0;
    virtual ~IAutenticacao() {}
};

// Interface para gerenciamento de usuários
class IGerenciamentoUsuario {
public:
    virtual void criarUsuario(const std::string& nome, const std::string& email, const std::string& senha) = 0;
    virtual void editarUsuario(const std::string& email, const std::string& novoNome, const std::string& novaSenha) = 0;
    virtual void excluirUsuario(const std::string& email) = 0;
    virtual ~IGerenciamentoUsuario() {}
};

// Interface para gerenciamento de quadros (boards)
class IGerenciamentoQuadro {
public:
    virtual void criarQuadro(const std::string& nomeQuadro, const std::string& usuario) = 0;
    virtual void visualizarQuadro(const std::string& codigoQuadro) = 0;
    virtual void excluirQuadro(const std::string& codigoQuadro, const std::string& usuario) = 0;
    virtual ~IGerenciamentoQuadro() {}
};

// Interface para gerenciamento de cartões (cards)
class IGerenciamentoCartao {
public:
    virtual void criarCartao(const std::string& titulo, const std::string& descricao, const std::string& codigoQuadro) = 0;
    virtual void visualizarCartao(const std::string& codigoCartao) = 0;
    virtual void moverCartao(const std::string& codigoCartao, const std::string& novaColuna) = 0;
    virtual void excluirCartao(const std::string& codigoCartao) = 0;
    virtual ~IGerenciamentoCartao() {}
};

#endif // INTERFACES_HPP_INCLUDED
