/*
*===============================================================*
*            Trabalho 1 - Técnicas de programação               *
*===============================================================*
*===============================================================*
*                                                               *
*   Aluno 1: [Pedro César Ribeiro Passos] Matrícula:[180139312] *
*                                                               *
*===============================================================*
*/

#include <iostream>
#include <string>
#include <locale.h>
#include "testes.h"

using namespace std;

int main(){

    setlocale(LC_ALL,"");

    /* INÍCIO TESTES CLASSES DOMÍNIOS */

    cout << "                       TESTE DE UNIDADE DOMINIOS " << endl;

    TUCodigo teste_Codigo;
    if(teste_Codigo.run())
        cout << "O teste de Unidade da Classe 'Codigo' está funcionando corretamente!" << endl;
    else
        cout << "Código inválido!" << endl;


    TUColuna teste_Coluna;
    if(teste_Coluna.run())
        cout << "O teste de Unidade da Classe 'Coluna' está funcionando corretamente!" << endl;
    else
        cout << "Coluna inválida!" << endl;


    TUEmail teste_Email;
    if(teste_Email.run())
        cout << "O teste de Unidade da Classe 'Email' está funcionando corretamente!" << endl;
    else
        cout << "Email inválido!" << endl;


    TULimite teste_Limite;
    if(teste_Limite.run())
        cout << "O teste de Unidade da Classe 'Limite' está funcionando corretamente!" << endl;
    else
        cout << "Limite inválido!" << endl;

    
    TUSenha teste_Senha;
    if(teste_Senha.run())
        cout << "O teste de Unidade da Classe 'Senha' está funcionando corretamente!" << endl;
    else
        cout << "Senha inválida!" << endl;

    TUTexto teste_Texto;
    if(teste_Texto.run())
        cout << "O teste de Unidade da Classe 'Texto' está funcionando corretamente!" << endl;
    else
        cout << "Texto inválido!" << endl;



    /* FIM TESTES CLASSES DOMÍNIOS */

    cout << endl;

    // Quando você tiver classes de entidade, pode adicionar testes de unidade para elas aqui.

    /* INÍCIO TESTES CLASSES ENTIDADES */

    cout << "                       TESTE DE UNIDADE ENTIDADES " << endl;

    TUConta teste_Conta;
    if(teste_Conta.run())
        cout << "O teste de Unidade da Classe 'Conta' está funcionando corretamente!" << endl;
    else
        cout << "Conta inválida!" << endl;


    TUQuadro teste_Quadro;
    if(teste_Quadro.run())
        cout << "O teste de Unidade da Classe 'Quadro' está funcionando corretamente!" << endl;
    else
        cout << "Quadro inválido!" << endl;

    
    TUCartao teste_Cartao;
    if(teste_Cartao.run())
        cout << "O teste de Unidade da Classe 'Cartao' está funcionando corretamente!" << endl;
    else
        cout << "Cartao inválido!" << endl;


    /* FIM TESTES CLASSES ENTIDADES */

    // Para aguardar uma entrada do usuário antes do programa terminar
    cin.get();

    return 0;
}



