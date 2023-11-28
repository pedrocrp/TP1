/*
*===============================================================*
*            Trabalho 1 - Técnicas de programação               *
*===============================================================*
*===============================================================*
*                                                               *
*   Aluno: Pedro César Ribeiro Passos      Matrícula: 180139312 *
*                                                               *
*                                                               *
*===============================================================*
*/

#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "dominios.h"  // Inclui a definição das classes Email, Texto, Senha, etc.

/**
 * @class Conta
 * @brief Classe que representa uma conta de usuário.
 * 
 * A classe Conta gerencia as informações básicas de uma conta de usuário, incluindo email, nome e senha.
 * Ela utiliza objetos das classes Email, Texto e Senha para garantir que os dados atendam a certos critérios de validação.
 */
class Conta {
private:
    Email email; ///< Email associado à conta de usuário. Deve ser um endereço de email válido.
    Texto nome;  ///< Nome associado à conta de usuário. Deve ter entre 5 e 30 caracteres e começar com uma letra maiúscula.
    Senha senha; ///< Senha para a conta de usuário. Deve atender aos critérios de complexidade especificados pela classe Senha.

public:
    /**
     * @brief Construtor padrão.
     * 
     * Inicializa a conta com valores padrão.
     */
    Conta();  

    /**
     * @brief Construtor que inicializa os membros.
     * 
     * Inicializa a conta com um email, nome e senha fornecidos.
     * @param email Objeto da classe Email.
     * @param nome Objeto da classe Texto.
     * @param senha Objeto da classe Senha.
     */
    Conta(const Email& email, const Texto& nome, const Senha& senha);  

    /**
     * @brief Retorna o email associado à conta.
     * 
     * @return std::string O endereço de email.
     */
    std::string getEmail() const;

    /**
     * @brief Retorna o nome associado à conta.
     * 
     * @return std::string O nome do usuário.
     */
    std::string getNome() const;

    /**
     * @brief Retorna a senha associada à conta.
     * 
     * @return std::string A senha do usuário.
     */
    std::string getSenha() const;

    /**
     * @brief Define o email da conta.
     * 
     * @param email Objeto da classe Email.
     */
    void setEmail(const Email& email);

    /**
     * @brief Define o nome da conta.
     * 
     * @param nome Objeto da classe Texto.
     */
    void setNome(const Texto& nome);

    /**
     * @brief Define a senha da conta.
     * 
     * @param senha Objeto da classe Senha.
     */
    void setSenha(const Senha& senha);
};



/**
 * @class Quadro
 * @brief Classe que representa um quadro.
 * 
 * A classe Quadro gerencia as informações básicas de um quadro, incluindo código, nome e limite.
 * Ela utiliza objetos das classes Codigo, Texto e Limite para garantir que os dados atendam a certos critérios de validação.
 */
class Quadro {
private:
    Codigo codigo; ///< Código único identificador do quadro. Deve ser um código válido.
    Texto nome;    ///< Nome descritivo do quadro. Deve ser um texto válido.
    Limite limite; ///< Limite de tarefas, ou recursos no quadro. Deve ser um valor de limite válido.
    Texto descricao; 
public:
    /**
     * @brief Construtor padrão.
     * 
     * Inicializa o quadro com valores padrão.
     */
    Quadro();  

    /**
     * @brief Construtor com parâmetros.
     * 
     * Inicializa o quadro com um código, nome e limite fornecidos.
     * @param codigo Referência constante para um objeto da classe Codigo.
     * @param nome Referência constante para um objeto da classe Texto.
     * @param limite Referência constante para um objeto da classe Limite.
     */
    Quadro(const Codigo& codigo, const Texto& nome, const Texto& descricao ,const Limite& limite);  

    /**
     * @brief Recupera o código do quadro.
     * 
     * @return Uma string representando o código do quadro.
     */
    std::string getCodigo() const;

    /**
     * @brief Recupera o nome do quadro.
     * 
     * @return Uma string representando o nome do quadro.
     */
    std::string getNome() const;

    /**
     * @brief Recupera o limite do quadro.
     * 
     * @return Um inteiro representando o limite do quadro.
     */
    int getLimite() const;


    /**
     * @brief Recupera a descricao do quadro.
     * 
     * @return Uma string representando a descricao do quadro.
     */
    std::string getDescricao() const;


    /**
     * @brief Define o código do quadro.
     * 
     * @param codigo Referência constante para um objeto da classe Codigo.
     */
    void setCodigo(const Codigo& codigo);

    /**
     * @brief Define o nome do quadro.
     * 
     * @param nome Referência constante para um objeto da classe Texto.
     */
    void setNome(const Texto& nome);

    /**
     * @brief Define o limite do quadro.
     * 
     * @param limite Referência constante para um objeto da classe Limite.
     */
    void setLimite(const Limite& limite);



/**
     * @brief Define a descricao do quadro.
     * 
     * @param descricao Referência constante para um objeto da classe Descricao.
     */
    void setDescricao(const Texto& descricao);
};






/**
 * @class Cartao
 * @brief Classe que representa um cartão em um quadro Kanban.
 * 
 * A classe Cartao gerencia as informações de um cartão, incluindo código, nome, descrição e coluna.
 * Ela utiliza objetos das classes Codigo, Texto e Coluna para garantir que os dados atendam a certos critérios de validação.
 */
class Cartao {
private:
    Codigo codigo; ///< Código único associado ao cartão. Deve ser um identificador válido.
    Texto nome;    ///< Nome associado ao cartão. Deve ter entre 1 e 50 caracteres.
    Texto descricao; ///< Descrição associada ao cartão. Deve ter entre 1 e 50 caracteres.
    Coluna coluna; ///< Coluna em que o cartão está. Representa o status atual do cartão.

public:
    /**
     * @brief Construtor padrão.
     * 
     * Inicializa o cartão com valores padrão.
     */
    Cartao();  

    /**
     * @brief Construtor que inicializa os membros.
     * 
     * Inicializa o cartão com um código, nome, descrição e coluna fornecidos.
     * @param codigo Objeto da classe Codigo.
     * @param nome Objeto da classe Texto.
     * @param descricao Objeto da classe Texto.
     * @param coluna Objeto da classe Coluna.
     */
    Cartao(const Codigo& codigo, const Texto& nome, const Texto& descricao, const Coluna& coluna);  

    /**
     * @brief Retorna o código associado ao cartão.
     * 
     * @return Codigo O código do cartão.
     */
    std::string getCodigo() const;

    /**
     * @brief Retorna o nome associado ao cartão.
     * 
     * @return Texto O nome do cartão.
     */
    std::string getNome() const;

    /**
     * @brief Retorna a descrição associada ao cartão.
     * 
     * @return Texto A descrição do cartão.
     */
    std::string getDescricao() const;

    /**
     * @brief Retorna a coluna associada ao cartão.
     * 
     * @return Coluna A coluna do cartão.
     */
    std::string getColuna() const;

    /**
     * @brief Define o código do cartão.
     * 
     * @param codigo Objeto da classe Codigo.
     */
    void setCodigo(const Codigo& codigo);

    /**
     * @brief Define o nome do cartão.
     * 
     * @param nome Objeto da classe Texto.
     */
    void setNome(const Texto& nome);

    /**
     * @brief Define a descrição do cartão.
     * 
     * @param descricao Objeto da classe Texto.
     */
    void setDescricao(const Texto& descricao);

    /**
     * @brief Define a coluna do cartão.
     * 
     * @param coluna Objeto da classe Coluna.
     */
    void setColuna(const Coluna& coluna);
};




#endif











