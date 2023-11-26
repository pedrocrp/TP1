#include "testes.h"
#include <iostream>

// -------------------------------------------------------------------------------- //

//// INICIO TESTE CODIGO ////

void TUCodigo::setUp() {
    codigo = new Codigo();
    estado = true;
}

void TUCodigo::tearDown() {
    delete codigo;
}

void TUCodigo::testarCenarioSucesso() {
    try {
        codigo->setCodigo(CODIGO_VALIDO);
        if (codigo->getCodigo() != CODIGO_VALIDO) {
            estado = false;
        }
    } catch (std::invalid_argument &e) {
        estado = false;
    }
}

void TUCodigo::testarCenarioFalha() {
    try {
        codigo->setCodigo(CODIGO_INVALIDO);
        estado = false; // Se nenhuma exceção for lançada, há um erro.
    } catch (std::invalid_argument &e) {
        // Se uma exceção foi lançada, o teste de falha foi bem-sucedido.
        return;
    }
}

bool TUCodigo::run() {
    setUp();
    testarCenarioSucesso();
    testarCenarioFalha();
    tearDown();
    return estado;
}

//// FIM TESTE CODIGO ////

// -------------------------------------------------------------------------------- //

//// INICIO TESTE COLUNA ////

void TUColuna::setUp() {
    coluna = new Coluna();
    estado = true;
}

void TUColuna::tearDown() {
    delete coluna;
}

void TUColuna::testarCenarioSucesso() {
    try {
        coluna->setEstado("SOLICITADO");
        if (coluna->getEstado() != "SOLICITADO") {
            estado = false;
        }
    } catch (std::invalid_argument &excecao) {
        estado = false;
    }
}

void TUColuna::testarCenarioFalha() {
    try {
        coluna->setEstado("INVALIDO");
        estado = false;
    } catch (std::invalid_argument &excecao) {
        // Se uma exceção foi lançada, o teste de falha foi bem-sucedido.
    }
}

bool TUColuna::run() {
    setUp();
    testarCenarioSucesso();
    testarCenarioFalha();
    tearDown();
    return estado;
}

//// FIM TESTE COLUNA ////

// -------------------------------------------------------------------------------- //

//// INICIO TESTE EMAIL ////

void TUEmail::setUp() {
    email = new Email();
    estado = true;
}

void TUEmail::tearDown() {
    delete email;
}

void TUEmail::testarCenarioSucesso() {
    try {
        email->setEmail(EMAIL_VALIDO);
        if (email->getEmail() != EMAIL_VALIDO) {
            estado = false;
        }
    } catch (std::invalid_argument &excecao) {
        estado = false;
    }
}

void TUEmail::testarCenarioFalha() {
    try {
        email->setEmail(EMAIL_INVALIDO);
        estado = false; // Se aceitar um email inválido, o teste falha.
    } catch (std::invalid_argument &excecao) {
        // Se uma exceção foi lançada, o teste de falha foi bem-sucedido.
        return;
    }
}

bool TUEmail::run() {
    setUp();
    testarCenarioSucesso();
    testarCenarioFalha();
    tearDown();
    return estado;
}

//// FIM TESTE EMAIL ////

// -------------------------------------------------------------------------------- //

//// INICIO TESTE LIMITE ////

void TULimite::setUp() {
    limite = new Limite();
    estado = true;
}

void TULimite::tearDown() {
    delete limite;
}

void TULimite::testarCenarioSucesso() {
    try {
        limite->setLimite(VALOR_VALIDO);
        if (limite->getLimite() != VALOR_VALIDO) {
            estado = false;
        }
    } catch (std::invalid_argument &excecao) {
        estado = false;
    }
}

void TULimite::testarCenarioFalha() {
    try {
        limite->setLimite(VALOR_INVALIDO);
        estado = false; // Se aceitar um limite inválido, o teste falha.
    } catch (std::invalid_argument &excecao) {
        // Se uma exceção foi lançada, o teste de falha foi bem-sucedido.
        return;
    }
}

bool TULimite::run() {
    setUp();
    testarCenarioSucesso();
    testarCenarioFalha();
    tearDown();
    return estado;
}

//// FIM TESTE LIMITE ////

// -------------------------------------------------------------------------------- //

//// INICIO TESTE SENHA ////

void TUSenha::setUp() {
    senha = new Senha();
    estado = false;
}

void TUSenha::tearDown() {
    delete senha;
}

void TUSenha::testarCenarioSucesso() {
    try {
        senha->setSenha(SENHA_VALIDA);
        if (senha->getSenha() == SENHA_VALIDA) {
            estado = true;
        }
    } catch (std::invalid_argument &e) {
        estado = false;
    }
}

void TUSenha::testarCenarioFalha() {
    try {
        senha->setSenha(SENHA_INVALIDA);
        estado = false; // Se aceitar uma senha inválida, o teste falha.
    } catch (std::invalid_argument &e) {
        // A exceção era esperada, então o teste passa.
        estado = true;
    }
}

bool TUSenha::run() {
    setUp();
    testarCenarioSucesso();
    if(estado) // só executa o segundo teste se o primeiro passar
        testarCenarioFalha();
    tearDown();
    return estado;
}

//// FIM TESTE LIMITE ////

// -------------------------------------------------------------------------------- //

//// INICIO TESTE TEXTO

void TUTexto::setUp() {
    texto = new Texto();
    estado = false;
}

void TUTexto::tearDown() {
    delete texto;
}

void TUTexto::testarCenarioSucesso() {
    try {
        texto->setTexto(TEXTO_VALIDO);
        if (texto->getTexto() == TEXTO_VALIDO) {
            estado = true;
        }
    } catch (std::invalid_argument &e) {
        estado = false;
    }
}

void TUTexto::testarCenarioFalha() {
    try {
        texto->setTexto(TEXTO_INVALIDO);
        estado = false; // Se aceitar um texto inválido, o teste falha.
    } catch (std::invalid_argument &e) {
        // A exceção era esperada, então o teste passa.
        estado = true;
    }
}

bool TUTexto::run() {
    setUp();
    testarCenarioSucesso();
    if(estado) // só executa o segundo teste se o primeiro passar
        testarCenarioFalha();
    tearDown();
    return estado;
}

//// FIM TESTE TEXTO ////

// -------------------------------------------------------------------------------- //

void TUConta::setUp() {
    conta = new Conta();
    estado = false;
}

void TUConta::tearDown() {
    delete conta;
}

void TUConta::testarCenarioSucesso() {
    try {
        Email email;
        email.setEmail(EMAIL_VALIDO);

        Texto nome;
        nome.setTexto(NOME_VALIDO);

        Senha senha;
        senha.setSenha(SENHA_VALIDA);

        conta->setEmail(email);

        conta->setNome(nome);

        conta->setSenha(senha);

        if (conta->getEmail() == EMAIL_VALIDO && 
            conta->getNome() == NOME_VALIDO && 
            conta->getSenha() == SENHA_VALIDA) {
            estado = true;
        } else {
        }
    } catch (std::invalid_argument &e) {
        estado = false;
    }
}

void TUConta::testarCenarioFalha() {
    try {
        Email email;
        email.setEmail(EMAIL_INVALIDO);

        Texto nome;
        nome.setTexto(NOME_INVALIDO);

        Senha senha;
        senha.setSenha(SENHA_INVALIDA);

        conta->setEmail(email);
        conta->setNome(nome);
        conta->setSenha(senha);

        estado = false;
    } catch (std::invalid_argument &e) {
        estado = true;
    }
}


bool TUConta::run() {
    setUp();
    testarCenarioSucesso();
    if (estado) {
        testarCenarioFalha();
    }
    
    tearDown();

    return estado;
}



// -------------------------------------------------------------------------------- //

//// INICIO TESTE QUADRO ////

void TUQuadro::setUp() {
    quadro = new Quadro();
    estado = true;
}

void TUQuadro::tearDown() {
    delete quadro;
}

void TUQuadro::testarCenarioSucesso() {
    try {
        Texto nome;
        nome.setTexto(NOME_VALIDO);
        
        Limite limite;
        limite.setLimite(LIMITE_VALIDO);

        quadro->setNome(nome);
        quadro->setLimite(limite);

        if (quadro->getNome() != NOME_VALIDO || 
            quadro->getLimite() != LIMITE_VALIDO) {
            estado = false;
        }
    } catch (std::invalid_argument &e) {
        estado = false;
    }
}

void TUQuadro::testarCenarioFalha() {
    try {
        Texto nome;
        nome.setTexto(NOME_INVALIDO);
        
        Limite limite;
        limite.setLimite(LIMITE_INVALIDO);

        quadro->setNome(nome);
        quadro->setLimite(limite);

        estado = false; // Se aceitar valores inválidos, o teste falha.
    } catch (std::invalid_argument &e) {
        // A exceção era esperada, então o teste passa.
        estado = true;
    }
}

bool TUQuadro::run() {
    setUp();
    testarCenarioSucesso();
    if (estado) {
        testarCenarioFalha();
    }
    
    tearDown();

    return estado;
}

//// FIM TESTE QUADRO ////

// -------------------------------------------------------------------------------- //


void TUCartao::setUp() {
    cartao = new Cartao();
    estado = true;
}

void TUCartao::tearDown() {
    delete cartao;
}

void TUCartao::testarCenarioSucesso() {
    try {
        Codigo codigo;
        codigo.setCodigo(CODIGO_VALIDO); // Asumindo que o método para definir o código é setValor

        Texto nome;
        nome.setTexto(NOME_VALIDO); // Asumindo que o método para definir o texto é setValor

        Texto descricao;
        descricao.setTexto(DESCRICAO_VALIDA); // Asumindo que o método para definir o texto é setValor

        Coluna coluna;
        coluna.setEstado(COLUNA_VALIDA); // Asumindo que o método para definir a coluna é setEstado

        cartao->setCodigo(codigo);
        cartao->setNome(nome);
        cartao->setDescricao(descricao);
        cartao->setColuna(coluna);

        // Verifica se os valores foram corretamente atribuídos
        if (cartao->getCodigo() != CODIGO_VALIDO ||
            cartao->getNome() != NOME_VALIDO ||
            cartao->getDescricao() != DESCRICAO_VALIDA ||
            cartao->getColuna() != COLUNA_VALIDA) {
            estado = false;
        }
    } catch (std::invalid_argument &e) {
        estado = false; // Se uma exceção for lançada, o teste falha
    }
}

void TUCartao::testarCenarioFalha() {
    try {
        Codigo codigo;
        codigo.setCodigo(CODIGO_INVALIDO); // Asumindo que o método para definir o código é setValor

        Texto nome;
        nome.setTexto(NOME_INVALIDO); // Asumindo que o método para definir o texto é setValor

        Texto descricao;
        descricao.setTexto(DESCRICAO_INVALIDA); // Asumindo que o método para definir o texto é setValor

        Coluna coluna;
        coluna.setEstado(COLUNA_INVALIDA); // Asumindo que o método para definir a coluna é setEstado

        cartao->setCodigo(codigo); // Isso deve lançar uma exceção
        cartao->setNome(nome); // Isso deve lançar uma exceção
        cartao->setDescricao(descricao); // Isso deve lançar uma exceção
        cartao->setColuna(coluna); // Isso deve lançar uma exceção

        estado = false; // Se chegar aqui, significa que não lançou exceção onde deveria
    } catch (std::invalid_argument &e) {
        // A exceção era esperada, então o teste passa
    }
}

bool TUCartao::run() {
    setUp();
    testarCenarioSucesso();
    if (estado) {
        testarCenarioFalha();
    }
    tearDown();

    return estado;
}



