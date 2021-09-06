#include "endereco.h"

class Entrada
{
public:
    Endereco endereco;
    int tipoOperacao;
    string dado;
    Entrada(int endereco, int tipoOperacao, string dado)
    {
        this->endereco = Endereco(endereco);
        this->tipoOperacao = tipoOperacao;
        this->dado = dado;
    }
};