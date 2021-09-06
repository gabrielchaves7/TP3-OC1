#include <iostream>
using namespace std;

class Saida
{
public:
    int endereco;
    int tipoOperacao;
    string dado;
    string resultado;
    Saida(int endereco, int tipoOperacao, string dado, string resultado)
    {
        this->endereco = endereco;
        this->tipoOperacao = tipoOperacao;
        this->dado = dado;
        this->resultado = resultado;
    }
};