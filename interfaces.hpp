#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include <string>
#include <vector>
#include "entidades.h"
#include <optional>


class IControleLogin {
public:
    virtual bool autenticar(const std::string& email, const std::string& senha) = 0;
    virtual ~IControleLogin() {}
};

class IControleCadastro {
public:
    virtual bool cadastrarUsuario(const std::string& emailStr, const std::string& nomeStr, const std::string& senhaStr) = 0;
    virtual ~IControleCadastro() {}
    
};

class IControleQuadros {
public:
    virtual std::vector<Quadro> obterQuadros(const std::string& emailUsuario) = 0;
    virtual bool criarQuadro(const std::string& emailUsuario, 
                     const std::string& codigo, 
                     const std::string& nome, 
                     const std::string& descricao, 
                     int limite) = 0;
    virtual bool editarQuadro(const std::string& emailUsuario, 
                      const std::string& codigoQuadro, 
                      const std::optional<std::string>& novoNome, 
                      const std::optional<std::string>& novaDescricao, 
                      const std::optional<int>& novoLimite) = 0;
    virtual bool excluirQuadro(const std::string& emailUsuario, const std::string& codigoQuadro) = 0;
    virtual ~IControleQuadros() {}
    
};



// ---------------------------------------------------- CAMADA DE SERVICOS --------------------------------------------------- //

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

// ---------------------------------------------------- CAMADA DE APRESENTACAO --------------------------------------------------- //

class ITelaInicial {
public:
    virtual void exibir() = 0;
    virtual ~ITelaInicial() {}
};

class ITelaCadastro {
public:
    virtual void exibir() = 0;
    virtual ~ITelaCadastro() {}
};

class ITelaLogin {
public:
    virtual void exibir() = 0;
    virtual ~ITelaLogin() {}
};

class ITelaQuadros {
public:
    virtual void exibir() = 0;
    virtual ~ITelaQuadros() {}
};












#endif // INTERFACES_HPP_INCLUDED
