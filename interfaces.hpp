// interfaces.hpp

#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include "entidades.h"
#include <list>

// Interface de Serviço de Usuário
class IServicoUsuario {
public:
    virtual bool criarUsuario(const Conta& conta) = 0;
    virtual Conta obterUsuario(const Email& email) = 0;
    virtual Conta obterUsuarioPorNome(const Texto& nome) = 0;
    virtual bool excluirUsuario(const Email& email) = 0;
    virtual bool autenticarUsuario(const Email& email, const Senha& senha) = 0;
    virtual std::list<Conta> listarUsuarios() = 0;
    virtual bool redefinirSenha(const Email& email, const Senha& novaSenha) = 0;

    virtual ~IServicoUsuario() {}
};

// Interface de Serviço de Quadro
class IServicoQuadro {
public:
    virtual bool criarQuadro(const Quadro& quadro) = 0;
    virtual Quadro obterQuadro(const Codigo& codigo) = 0;
    virtual bool atualizarQuadro(const Quadro& quadro) = 0;
    virtual bool deletarQuadro(const Codigo& codigo) = 0;
    virtual std::list<Quadro> listarQuadros() = 0;
    virtual bool associarCartaoAoQuadro(const Cartao& cartao, const Codigo& codigoQuadro) = 0;
    virtual bool desassociarCartaoDoQuadro(const Codigo& codigoCartao, const Codigo& codigoQuadro) = 0;

    virtual ~IServicoQuadro() {}
};


// Interface de Serviço de Cartão
class IServicoCartao {
public:
    virtual bool adicionarCartao(const Cartao& cartao, const Codigo& codigoQuadro) = 0;
    // Outros métodos...
    virtual ~IServicoCartao() {}
};

// Interface de Serviço de Autenticação
class IServicoAutenticacao {
public:
    virtual bool autenticarUsuario(const Email& email, const Senha& senha) = 0;
    virtual ~IServicoAutenticacao() {}
};

// Interfaces adicionais podem ser declaradas aqui, como uma Interface de Gestão de Projetos, Interface de Controle de Sessão, etc.

#endif // INTERFACES_HPP
