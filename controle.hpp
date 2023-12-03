#ifndef CONTROLADOR_HPP
#define CONTROLADOR_HPP

#include "servicos.hpp"
#include <string>


class ControladorLogin : public IControleLogin {
private:
    DatabaseManager dbManager;

public:
    ControladorLogin(const std::string& dbPath);
    bool autenticar(const std::string& email, const std::string& senha) override;
};


class ControladorCadastro : public IControleCadastro {
private:
    ServicosConta servicosConta;

public:
    ControladorCadastro(const std::string& dbPath);

    bool cadastrarUsuario(const std::string& emailStr, const std::string& nomeStr, const std::string& senhaStr);
};


class ControladorQuadros : public IControleQuadros {
private:
    ServicosQuadro servicosQuadro;

public:
    ControladorQuadros(const std::string& dbPath);
    std::vector<Quadro> obterQuadros(const std::string& emailUsuario) override;
    bool criarQuadro(const std::string& emailUsuario, 
                     const std::string& codigo, 
                     const std::string& nome, 
                     const std::string& descricao, 
                     int limite);
    bool editarQuadro(const std::string& emailUsuario, 
                      const std::string& codigoQuadro, 
                      const std::optional<std::string>& novoNome, 
                      const std::optional<std::string>& novaDescricao, 
                      const std::optional<int>& novoLimite) override;
    bool excluirQuadro(const std::string& emailUsuario, const std::string& codigoQuadro) override;
};










#endif // CONTROLADOR_HPP
