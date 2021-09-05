#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

const int TAMANHO_MEMORIA = 64;

class Entrada
{
public:
    int endereco;
    int tipoOperacao;
    string dado;
    Entrada(int endereco, int tipoOperacao, string dado)
    {
        this->endereco = endereco;
        this->tipoOperacao = tipoOperacao;
        this->dado = dado;
    }
};

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

class Operacoes
{
public:
    double reads = 0;
    double writes = 0;
    double hits = 0;
    double misses = 0;
    Operacoes() {}
    double calculateMissRate()
    {
        return misses / reads;
    }
    double calculateHitRate()
    {
        return hits / reads;
    }
};

class Memoria
{
public:
    string dados[64];
    Operacoes operacoes;
    vector<Saida> saidas;
    Memoria()
    {
        this->operacoes = Operacoes();
    }
    void addEntrada(Entrada entrada)
    {
        int posicao = entrada.endereco % TAMANHO_MEMORIA;
        string dadoAtual = dados[posicao];
        string resultado = this->realizaOperacao(entrada.tipoOperacao, posicao, dadoAtual, entrada.dado);
        cout << "O resultado da operacao e: " << resultado << "\n\n";
        this->geraSaida(entrada, resultado);
    }

private:
    string realizaOperacao(int tipoOperacao, int posicaoMemoria, string dadoAtual, string novoDado)
    {
        string resultado = "";
        if (tipoOperacao == 1)
        {
            resultado = "W";
            operacoes.writes += 1;
            writeDado(posicaoMemoria, novoDado);
        }

        else
        {
            operacoes.reads += 1;
            resultado = readDado(dadoAtual);
        }

        return resultado;
    }
    void writeDado(int posicaoMemoria, string novoDado)
    {
        dados[posicaoMemoria] = novoDado;
    }
    string readDado(string dadoAtual)
    {
        if (dadoAtual.empty())
        {
            operacoes.misses += 1;
            return "M";
        }
        else
        {
            operacoes.hits += 1;
            return "H";
        }
    }
    void geraSaida(Entrada entrada, string resultado)
    {
        saidas.push_back(Saida(entrada.endereco, entrada.tipoOperacao, entrada.dado, resultado));
    }
};

int main()
{
    int endereco, tipoOperacao;
    Memoria memoria = Memoria();
    ifstream infile("arquivo.txt");
    string line;
    while (getline(infile, line))
    {
        istringstream iss(line);
        if (!(iss >> endereco >> tipoOperacao))
        {
            break;
        }
        string dado = "";
        if (tipoOperacao == 1)
        {
            iss >> dado;
        }
        Entrada entrada = Entrada(endereco, tipoOperacao, dado);
        memoria.addEntrada(entrada);
    }

    vector<Saida> saidas = memoria.saidas;
    Operacoes operacoes = memoria.operacoes;
    cout << "READS: " << operacoes.reads << "\n";
    cout << "WRITES: " << operacoes.writes << "\n";
    cout << "HITS: " << operacoes.hits << "\n";
    cout << "MISSES: " << operacoes.misses << "\n";
    cout << "HIT RATE: " << operacoes.calculateHitRate() << "\n";
    cout << "MISS RATE: " << operacoes.calculateMissRate() << "\n";
    for (int i = 0; i < saidas.size(); i++)
    {
        cout << saidas[i].endereco << " " << saidas[i].tipoOperacao << " " << saidas[i].dado << " " << saidas[i].resultado << "\n";
    }
    system("pause");
}