#include <iostream>
#include <vector>
#include "entrada.h"
#include "historico.h"
#include "saida.h"
using namespace std;

const int OPERACAO_DE_ESCRITA = 1;
const int OPERACAO_DE_LEITURA = 0;
const string SIGLA_LEITURA = "W";
const string SIGLA_HIT = "H";
const string SIGLA_MISS = "M";

class Memoria
{
public:
    vector<Endereco> enderecos;
    Historico historico;
    vector<Saida> saidas;
    Memoria()
    {
        this->historico = Historico();
    }
    void addEntrada(Entrada entrada)
    {
        string resultado = this->realizaOperacao(entrada.tipoOperacao, entrada.endereco);
        this->geraSaida(entrada, resultado);
    }

private:
    string realizaOperacao(int tipoOperacao, Endereco endereco)
    {
        if (tipoOperacao == OPERACAO_DE_ESCRITA)
        {
            enderecos.push_back(endereco);            
            historico.writes += 1;
            return SIGLA_LEITURA;
        }
        else
        {
            historico.reads += 1;
            return readDado(endereco);
        }
    }
    string readDado(Endereco novoEndereco)
    {
        int enderecosSize = enderecos.size();
        for (int i = 0; i < enderecosSize; i++)
        {
            Endereco it = enderecos.at(i);
            if (it.tag == novoEndereco.tag && it.indice == novoEndereco.indice)
            {
                historico.hits += 1;
                return SIGLA_HIT;
            }
        }

        historico.misses += 1;
        enderecos.push_back(novoEndereco);
        return SIGLA_MISS;
    }
    void geraSaida(Entrada entrada, string resultado)
    {
        saidas.push_back(Saida(entrada.endereco.decimal, entrada.tipoOperacao, entrada.dado, resultado));
    }
};