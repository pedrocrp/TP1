#ifndef DOMINIOS_H_INCLUDED
#define DOMINIOS_H_INCLUDED

#include <string>
#include <stdexcept>

/**
 * @class Codigo
 * @brief Classe responsável por armazenar e validar um código alfanumérico.
 *
 * A classe Codigo é responsável por armazenar um código que consiste em uma combinação específica
 * de caracteres, incluindo duas letras maiúsculas seguidas por dois dígitos. A classe assegura que 
 * qualquer código armazenado atenda a esses critérios através de um método de validação.
 */
class Codigo {
private:
    std::string codigo; ///< Armazena o código alfanumérico após validação.

    /**
     * @brief Valida o código fornecido.
     * 
     * Verifica se o código fornecido tem exatamente quatro caracteres, com os dois primeiros sendo 
     * letras maiúsculas e os dois últimos, dígitos.
     * 
     * @param codigo O código a ser validado.
     * @throw std::invalid_argument Se o código não atender aos critérios especificados.
     */
    void validarCodigo(const std::string& codigo);

public:
    /**
     * @brief Define o código.
     * 
     * Valida e define o código. Se o código fornecido não for válido, uma exceção será lançada.
     * 
     * @param codigo O código a ser definido.
     * @throw std::invalid_argument Se o código não atender aos critérios especificados.
     */
    void setCodigo(const std::string& codigo);

    /**
     * @brief Obtém o código atual.
     * 
     * @return Uma string representando o código atual.
     */
    std::string getCodigo() const;
};

/**
 * @class Coluna
 * @brief Classe responsável por gerenciar o estado de uma coluna em um contexto específico (por exemplo, em um quadro de tarefas).
 *
 * Esta classe armazena e gerencia mudanças no "estado" de uma coluna, garantindo que qualquer valor atribuído ao estado
 * seja válido conforme definido pelo método de validação. Os estados possíveis são: "SOLICITADO", "EM EXECUCAO" e "CONCLUIDO".
 */
class Coluna {
private:
    std::string estado; ///< Armazena o estado atual da coluna. Deve ser um dos valores predefinidos válidos.

    /**
     * @brief Valida o estado fornecido.
     * 
     * Verifica se o estado fornecido corresponde a um dos estados válidos: "SOLICITADO", "EM EXECUCAO", "CONCLUIDO".
     * 
     * @param estado O estado a ser validado.
     * @throw std::invalid_argument Se o estado fornecido não for um dos valores predefinidos válidos.
     */
    void validarEstado(const std::string& estado);

public:
    /**
     * @brief Define o estado da coluna.
     * 
     * Valida e define o estado da coluna. Se o estado fornecido não for válido, uma exceção será lançada.
     * 
     * @param estado O estado a ser definido.
     * @throw std::invalid_argument Se o estado fornecido não for um dos valores predefinidos válidos.
     */
    void setEstado(const std::string& estado);

    /**
     * @brief Obtém o estado atual da coluna.
     * 
     * @return Uma string representando o estado atual da coluna.
     */
    std::string getEstado() const;
};

/**
 * @class Email
 * @brief Classe responsável por gerenciar e validar um endereço de e-mail.
 *
 * Esta classe mantém um endereço de e-mail e fornece métodos para validação e recuperação do e-mail.
 * A validação verifica se o formato do e-mail é válido, conforme as regras definidas no método validarEmail.
 */
class Email {
private:
    std::string email; ///< Armazena o endereço de e-mail.

    /**
     * @brief Valida o endereço de e-mail fornecido.
     * 
     * Verifica se o endereço de e-mail está no formato correto, incluindo a presença de '@', 
     * um domínio válido, e a ausência de caracteres inválidos. 
     * Lança uma exceção se o e-mail for inválido.
     *
     * @param email O endereço de e-mail a ser validado.
     * @throw std::invalid_argument Se o e-mail fornecido não está no formato correto.
     */
    void validarEmail(const std::string& email);

public:
    /**
     * @brief Define o endereço de e-mail.
     * 
     * Valida e define o endereço de e-mail. Se o e-mail fornecido não for válido, uma exceção será lançada.
     * 
     * @param email O endereço de e-mail a ser definido.
     * @throw std::invalid_argument Se o e-mail fornecido não está no formato correto.
     */
    void setEmail(const std::string& email);

    /**
     * @brief Obtém o endereço de e-mail atual.
     * 
     * @return Uma string representando o endereço de e-mail armazenado.
     */
    std::string getEmail() const;
};

// CLASSE LIMITE

/**
 * @class Limite
 * @brief Classe responsável por gerenciar e validar um limite numérico.
 *
 * Esta classe mantém um valor que representa um limite numérico e fornece métodos para
 * validação e recuperação desse limite. A validação assegura que o limite está dentro
 * de um conjunto específico de valores permitidos.
 */
class Limite {
private:
    int valor; ///< Armazena o valor do limite numérico.

    /**
     * @brief Valida o valor do limite fornecido.
     * 
     * Verifica se o valor está dentro dos limites aceitáveis, que são valores predefinidos.
     * Lança uma exceção se o valor for inválido.
     *
     * @param valor O valor do limite a ser validado.
     * @throw std::invalid_argument Se o valor fornecido não está dentro dos limites aceitáveis.
     */
    void validar(int valor);

public:
    /**
     * @brief Define o valor do limite.
     * 
     * Valida e define o valor do limite. Se o valor fornecido não for válido, uma exceção será lançada.
     * 
     * @param valor O valor do limite a ser definido.
     * @throw std::invalid_argument Se o valor fornecido não está dentro dos limites aceitáveis.
     */
    void setLimite(int valor);

    /**
     * @brief Obtém o valor do limite atual.
     * 
     * @return Um inteiro representando o valor do limite armazenado.
     */
    int getLimite() const;
};

// CLASSE SENHA

/**
 * @class Senha
 * @brief Classe responsável por gerenciar e validar senhas.
 *
 * Esta classe é responsável por armazenar uma senha, fornecendo métodos para
 * definir e recuperar essa senha. Ela assegura que a senha atenda a critérios específicos
 * de complexidade através de um método de validação.
 */
class Senha {
private:
    std::string valor; ///< Armazena a senha.

    /**
     * @brief Valida a senha fornecida.
     * 
     * Verifica se a senha atende a critérios específicos de complexidade, incluindo tamanho,
     * e a presença de letras maiúsculas, minúsculas, dígitos e pontuação. Lança uma exceção
     * se a senha não atender a esses critérios.
     *
     * @param valor A senha a ser validada.
     * @throw std::invalid_argument Se a senha fornecida não atender aos critérios de validação.
     */
    void validar(std::string valor);

public:
    /**
     * @brief Define a senha.
     * 
     * Valida e define a senha. Se a senha fornecida não for válida, uma exceção será lançada.
     * 
     * @param valor A senha a ser definida.
     * @throw std::invalid_argument Se a senha fornecida não atender aos critérios de validação.
     */
    void setSenha(const std::string &valor);

    /**
     * @brief Recupera a senha.
     * 
     * @return A senha atual armazenada.
     */
    std::string getSenha() const;
};

// CLASSE TEXTO

/**
 * @class Texto
 * @brief Classe responsável por gerenciar e validar objetos do tipo texto.
 *
 * Esta classe armazena uma string de texto e oferece métodos para configurar e 
 * recuperar o texto, garantindo que ele atenda a critérios específicos de formatação 
 * através de um método de validação.
 */
class Texto {
private:
    std::string valor; ///< Armazena o texto.

    /**
     * @brief Valida o texto fornecido.
     * 
     * Verifica se o texto atende a critérios específicos, como tamanho e características 
     * dos caracteres utilizados. Lança uma exceção se o texto não atender a esses critérios.
     *
     * @param valor O texto a ser validado.
     * @throw std::invalid_argument Se o texto fornecido não atender aos critérios de validação.
     */
    void validar(std::string valor);

public:
    /**
     * @brief Define o texto.
     * 
     * Valida e define o texto. Se o texto fornecido não for válido, uma exceção será lançada.
     * 
     * @param valor O texto a ser definido.
     * @throw std::invalid_argument Se o texto fornecido não atender aos critérios de validação.
     */
    void setTexto(std::string valor);

    /**
     * @brief Recupera o texto.
     * 
     * @return O texto atual armazenado.
     */
    std::string getTexto() const;
};



#endif // DOMINIOS_H_INCLUDED
