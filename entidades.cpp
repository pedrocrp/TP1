#include "entidades.h"
#include "dominios.h"

/**
 * Implementações para a classe Conta.
 */

// ---------------------------------------------------------------------------------------------------------------------
// Construtores

/**
 * @brief Construtor padrão para a classe Conta.
 * 
 * Inicializa a instância de Conta com valores padrão, utilizando os construtores padrão dos membros.
 */
Conta::Conta() {
    // Construtor padrão sem lógica específica, os membros serão inicializados com seus construtores padrão.
}

/**
 * @brief Construtor sobrecarregado que aceita valores iniciais para os membros da classe Conta.
 * 
 * Inicializa a instância de Conta com os valores fornecidos para email, nome e senha.
 * 
 * @param email Objeto do tipo Email que representa o email associado à conta.
 * @param nome Objeto do tipo Texto que representa o nome associado à conta.
 * @param senha Objeto do tipo Senha que representa a senha associada à conta.
 */
Conta::Conta(const Email& email, const Texto& nome, const Senha& senha) 
    : email(email), nome(nome), senha(senha) {
    // O corpo está vazio, a lista de inicialização já lidou com a atribuição de membros.
}

// ---------------------------------------------------------------------------------------------------------------------
// Getters

/**
 * @brief Recupera o email associado à conta.
 * 
 * @return Uma string contendo o valor do email, não o objeto Email inteiro.
 */
std::string Conta::getEmail() const {
    return email.getEmail();  // Retorna o valor de email, não o objeto inteiro.
}

/**
 * @brief Recupera o nome associado à conta.
 * 
 * @return Uma string contendo o valor do nome, não o objeto Texto inteiro.
 */
std::string Conta::getNome() const {
    return nome.getTexto();  // Retorna o valor de nome, não o objeto inteiro.
}

/**
 * @brief Recupera a senha associada à conta.
 * 
 * @return Uma string contendo o valor da senha, não o objeto Senha inteiro.
 */
std::string Conta::getSenha() const {
    return senha.getSenha();  // Retorna o valor de senha, não o objeto inteiro.
}

// ---------------------------------------------------------------------------------------------------------------------
// Setters

/**
 * @brief Define o email associado à conta.
 * 
 * @param email Um objeto do tipo Email. A validação ocorre no objeto 'Email'.
 */
void Conta::setEmail(const Email& email) {
    this->email = email;  // Atribuição direta. A validação ocorre no objeto 'Email'.
}

/**
 * @brief Define o nome associado à conta.
 * 
 * @param nome Um objeto do tipo Texto. A validação ocorre no objeto 'Texto'.
 */
void Conta::setNome(const Texto& nome) {
    this->nome = nome;  // Atribuição direta. A validação ocorre no objeto 'Texto'.
}

/**
 * @brief Define a senha associada à conta.
 * 
 * @param senha Um objeto do tipo Senha. A validação ocorre no objeto 'Senha'.
 */
void Conta::setSenha(const Senha& senha) {
    this->senha = senha;  // Atribuição direta. A validação ocorre no objeto 'Senha'.
}


// ------------------------------------------------------------------------------------------------------------------------


/**
 * @brief Implementações para a classe Cartao.
 * 
 * Essa seção do código contém as implementações dos métodos da classe Cartao.
 */

// ---------------------------------------------------------------------------------------------------------------------
// Construtores

/**
 * @brief Constrói um novo objeto da classe Cartao com valores padrão.
 */
Cartao::Cartao() {
    // Construtor padrão sem lógica específica, os membros serão inicializados com seus construtores padrão.
}

/**
 * @brief Constrói um novo objeto da classe Cartao com os valores fornecidos.
 * 
 * @param codigo O código a ser atribuído ao cartão.
 * @param nome O nome a ser atribuído ao cartão.
 * @param descricao A descrição a ser atribuída ao cartão.
 * @param coluna A coluna a ser atribuída ao cartão.
 */
Cartao::Cartao(const Codigo& codigo, const Texto& nome, const Texto& descricao, const Coluna& coluna)
    : codigo(codigo), nome(nome), descricao(descricao), coluna(coluna) {
    // O corpo está vazio, a lista de inicialização já lidou com a atribuição de membros.
}

// ---------------------------------------------------------------------------------------------------------------------
// Getters

/**
 * @brief Retorna o código associado ao cartão.
 * 
 * @return Uma string representando o código do cartão.
 */
std::string Cartao::getCodigo() const {
    return codigo.getCodigo();  // Retorna o valor de código, não o objeto inteiro.
}

/**
 * @brief Retorna o nome associado ao cartão.
 * 
 * @return Uma string representando o nome do cartão.
 */
std::string Cartao::getNome() const {
    return nome.getTexto();  // Retorna o valor de nome, não o objeto inteiro.
}

/**
 * @brief Retorna a descrição associada ao cartão.
 * 
 * @return Uma string representando a descrição do cartão.
 */
std::string Cartao::getDescricao() const {
    return descricao.getTexto();  // Retorna o valor de descrição, não o objeto inteiro.
}

/**
 * @brief Retorna o estado da coluna associada ao cartão.
 * 
 * @return Uma string representando o estado da coluna do cartão.
 */
std::string Cartao::getColuna() const {
    return coluna.getEstado();  // Retorna o estado da coluna, não o objeto Coluna inteiro.
}

// ---------------------------------------------------------------------------------------------------------------------
// Setters

/**
 * @brief Define o código do cartão.
 * 
 * @param codigo O novo código do cartão.
 */
void Cartao::setCodigo(const Codigo& codigo) {
    this->codigo = codigo;  // Atribuição direta. A validação ocorre no objeto 'Codigo'.
}

/**
 * @brief Define o nome do cartão.
 * 
 * @param nome O novo nome do cartão.
 */
void Cartao::setNome(const Texto& nome) {
    this->nome = nome;  // Atribuição direta. A validação ocorre no objeto 'Texto'.
}

/**
 * @brief Define a descrição do cartão.
 * 
 * @param descricao A nova descrição do cartão.
 */
void Cartao::setDescricao(const Texto& descricao) {
    this->descricao = descricao;  // Atribuição direta. A validação ocorre no objeto 'Texto'.
}

/**
 * @brief Define a coluna do cartão.
 * 
 * @param coluna A nova coluna do cartão.
 */
void Cartao::setColuna(const Coluna& coluna) {
    this->coluna = coluna;  // Atribuição direta. A validação ocorre no objeto 'Coluna'.
}


// ------------------------------------------------------------------------------------------------------------------------




/**
 * @brief Implementações para a classe Quadro.
 * 
 * Essa seção do código contém as implementações dos métodos da classe Quadro.
 */

// Construtores

/**
 * @brief Constrói um novo objeto da classe Quadro com valores padrão.
 */
Quadro::Quadro() {
    // Construtor padrão sem lógica específica, os membros serão inicializados com seus construtores padrão.
}

/**
 * @brief Constrói um novo objeto da classe Quadro com os valores fornecidos.
 * 
 * @param codigo O código a ser atribuído ao quadro.
 * @param nome O nome a ser atribuído ao quadro.
 * @param limite O limite a ser atribuído ao quadro.
 */
Quadro::Quadro(const Codigo& codigo, const Texto& nome, const Texto& descricao, const Limite& limite)
    : codigo(codigo), nome(nome), limite(limite), descricao(descricao){
    // O corpo está vazio, a lista de inicialização já lidou com a atribuição de membros.
}

// Getters

/**
 * @brief Retorna o código associado ao quadro.
 * 
 * @return Uma string representando o código do quadro.
 */
std::string Quadro::getCodigo() const {
    return codigo.getCodigo();  // Retorna o valor de código, não o objeto inteiro.
}

/**
 * @brief Retorna o nome associado ao quadro.
 * 
 * @return Uma string representando o nome do quadro.
 */
std::string Quadro::getNome() const {
    return nome.getTexto();  // Retorna o valor de nome, não o objeto inteiro.
}

/**
 * @brief Retorna o limite associado ao quadro.
 * 
 * @return Um inteiro representando o limite do quadro.
 */
int Quadro::getLimite() const {
    return limite.getLimite();  // Retorna o valor de limite, não o objeto inteiro.
}

std::string Quadro::getDescricao() const {
    return descricao.getTexto();  // Retorna o valor de nome, não o objeto inteiro.
}

// Setters

/**
 * @brief Define o código do quadro.
 * 
 * @param codigo O novo código do quadro.
 */
void Quadro::setCodigo(const Codigo& codigo) {
    this->codigo = codigo;  // Atribuição direta. A validação ocorre no objeto 'Codigo'.
}

/**
 * @brief Define o nome do quadro.
 * 
 * @param nome O novo nome do quadro.
 */
void Quadro::setNome(const Texto& nome) {
    this->nome = nome;  // Atribuição direta. A validação ocorre no objeto 'Texto'.
}

void Quadro::setDescricao(const Texto& descricao) {
    this->descricao = descricao;  // Atribuição direta. A validação ocorre no objeto 'Texto'.
}

/**
 * @brief Define o limite do quadro.
 * 
 * @param limite O novo limite do quadro.
 */
void Quadro::setLimite(const Limite& limite) {
    this->limite = limite;  // Atribuição direta. A validação ocorre no objeto 'Limite'.
}




