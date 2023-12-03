#ifndef APRESENTACAO_H
#define APRESENTACAO_H

#include "interfaces.hpp"
#include <iostream>
#include "controle.hpp"

class TelaInicial : public ITelaInicial {
public:
    TelaInicial();
    void exibir() override;
};

class TelaCadastro : public ITelaCadastro {
public:
    TelaCadastro();
    void exibir() override;
};

class TelaLogin : public ITelaLogin {
private:
    ControladorLogin controleLogin;

public:
    TelaLogin(const std::string& dbPath);
    void exibir() override;
};

class TelaGerenciamentoQuadros : public ITelaQuadros {
private:
    ControladorQuadros controladorQuadros;
    std::string emailUsuario;

public:
    TelaGerenciamentoQuadros(const std::string& dbPath, const std::string& emailUsuario);
    void exibir() override;
};

#endif // APRESENTACAO_H
