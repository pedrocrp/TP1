#include "dominios.h"
#include <cctype>
#include <iostream>
#include <algorithm>

using namespace std;

// CLASSE CODIGO

void Codigo::validarCodigo(const std::string& codigo) {
    // Verifica se o tamanho do código é exatamente 4
    if (codigo.size() != 4) {
        throw std::invalid_argument("Código deve ter 4 caracteres.");
    }
    // Verifica se os dois primeiros caracteres são letras maiúsculas
    if (!isupper(codigo[0]) || !isupper(codigo[1])) {
        throw std::invalid_argument("Os dois primeiros caracteres devem ser letras maiúsculas.");
    }
    // Verifica se os dois últimos caracteres são dígitos
    if (!isdigit(codigo[2]) || !isdigit(codigo[3])) {
        throw std::invalid_argument("Os dois últimos caracteres devem ser dígitos.");
    }
}

void Codigo::setCodigo(const std::string& codigo) {
    validarCodigo(codigo);
    this->codigo = codigo;
}

std::string Codigo::getCodigo() const {
    return codigo;
}

// CLASSE COLUNA

void Coluna::validarEstado(const std::string& estado) {
    if (estado != "SOLICITADO" && estado != "EM EXECUCAO" && estado != "CONCLUIDO") {
        throw std::invalid_argument("Estado inválido.");
    }
}

void Coluna::setEstado(const std::string& estado) {
    validarEstado(estado);
    this->estado = estado;
}

std::string Coluna::getEstado() const {
    return estado;
}


// CLASSE EMAIL

void Email::validarEmail(const std::string& email) {
    std::size_t at_pos = email.find('@');
    std::size_t dot_pos = email.find('.');

    // Verifica se o '@' está presente e não é o primeiro ou último caractere
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.size() - 1) {
        throw std::invalid_argument("Email deve conter '@' entre caracteres.");
    }

    // Verifica se existe algum ponto, e não está imediatamente antes ou depois de '@'
    if (dot_pos == std::string::npos || email[at_pos - 1] == '.' || email[at_pos + 1] == '.' ) {
        throw std::invalid_argument("Posição do ponto é inválida.");
    }

    // Verifica se não existem pontos em sequência
    if (email.find("..") != std::string::npos) {
        throw std::invalid_argument("Email não deve conter pontos em sequência.");
    }

    // Separa o nome e o domínio
    std::string nome = email.substr(0, at_pos);
    std::string dominio = email.substr(at_pos + 1);

    // Verifica os tamanhos do nome e do domínio
    if (nome.length() < 2 || nome.length() > 10 || dominio.length() < 2 || dominio.length() > 20) {
        throw std::invalid_argument("Nome deve ter entre 2 e 10 caracteres e domínio entre 2 e 20 caracteres.");
    }

    // Verifica se todos os caracteres são válidos
    for (char c : email) {
        if (!(std::isalnum(c) || c == '.' || c == '@')) {
            throw std::invalid_argument("Caracteres inválidos no email.");
        }
    }
}

void Email::setEmail(const std::string& email) {
    validarEmail(email);
    this->email = email;
}

std::string Email::getEmail() const {
    return email;
}


// CLASSE LIMITE

void Limite::validar(int valor) {
    // Verifica se o valor está dentro dos limites aceitáveis
    if (valor != 5 && valor != 10 && valor != 15 && valor != 20) {
        throw std::invalid_argument("Limite inválido. Os valores aceitáveis são: 5, 10, 15, 20.");
    }
}

void Limite::setLimite(int valor) {
    validar(valor); // Valida o valor antes de atribuir
    this->valor = valor; // Atribui o valor se for válido
}

int Limite::getLimite() const {
    return valor;
}


// CLASSE SENHA

void Senha::validar(std::string valor) {
    if (valor.length() != 5) {
        throw std::invalid_argument("Senha precisa ter 5 caracteres.");
    }

    bool has_upper = false, has_lower = false, has_digit = false, has_punctuation = false;

    for (char &c : valor) {
        if (std::isupper(c)) has_upper = true;
        else if (std::islower(c)) has_lower = true;
        else if (std::isdigit(c)) has_digit = true;
        else if (c == '.' || c == ',' || c == ';' || c == '?' || c == '!') has_punctuation = true;
        else throw std::invalid_argument("Caracteres inválidos na senha.");

        if (std::count(valor.begin(), valor.end(), c) > 1) {
            throw std::invalid_argument("Senha não pode conter caracteres duplicados.");
        }
    }

    if (!has_upper || !has_lower || !has_digit || !has_punctuation) {
        throw std::invalid_argument("Senha deve ter pelo menos uma letra maiúscula, uma minúscula, um dígito e um sinal de pontuação.");
    }
}

void Senha::setSenha(const std::string &valor) {
    validar(valor); // Valida o valor antes de atribuir
    this->valor = valor; // Atribui o valor se for válido
}

std::string Senha::getSenha() const {
    return valor;
}


// CLASSE TEXTO

void Texto::validar(std::string valor) {
    // Verifica o tamanho do texto.
    if (valor.size() < 5 || valor.size() > 30) {
        throw std::invalid_argument("Texto deve ter entre 5 e 30 caracteres.");
    }

    // Verifica se o primeiro caractere é uma letra maiúscula.
    if (!std::isupper(static_cast<unsigned char>(valor[0]))) {
        throw std::invalid_argument("O primeiro caractere deve ser uma letra maiúscula.");
    }

    // Verifica caracteres inválidos, espaços em sequência e sinais de pontuação em sequência.
    bool prevSpace = false;
    bool prevPunct = false;
    for (char c : valor) {
        if (c == ' ') {
            if (prevSpace) {
                throw std::invalid_argument("Não podem haver espaços em branco em sequência.");
            }
            prevSpace = true;
            continue;
        } else {
            prevSpace = false;
        }

        if (std::ispunct(c)) {
            if (prevPunct) {
                throw std::invalid_argument("Não podem haver sinais de pontuação em sequência.");
            }
            prevPunct = true;
        } else {
            prevPunct = false;
        }

        if (!std::isalnum(static_cast<unsigned char>(c)) && !std::ispunct(c) && c != ' ') {
            throw std::invalid_argument("Caractere inválido detectado.");
        }

        // Verifica se há acentuação.
        if ((c & 0xc3) == 0xc3) {
            throw std::invalid_argument("Não é permitida a acentuação.");
        }
    }
}

void Texto::setTexto(std::string valor) {
    validar(valor);
    this->valor = valor;
}

std::string Texto::getTexto() const {
    return valor;
}



