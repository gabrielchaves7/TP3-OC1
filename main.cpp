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

int main(int argc, char **argv)
{
    string input = argv[1];
    string output = argv[2];
    int endereco, tipoOperacao;

    Memoria memoria = Memoria();
    ifstream infile(input);
    ofstream outfile;
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

    outfile.open (output);
    vector<Saida> saidas = memoria.saidas;
    Operacoes operacoes = memoria.operacoes;
    outfile << "READS: " << operacoes.reads << "\n";
    outfile << "WRITES: " << operacoes.writes << "\n";
    outfile << "HITS: " << operacoes.hits << "\n";
    outfile << "MISSES: " << operacoes.misses << "\n";
    outfile << "HIT RATE: " << operacoes.calculateHitRate() << "\n";
    outfile << "MISS RATE: " << operacoes.calculateMissRate() << "\n\n";
    for (int i = 0; i < saidas.size(); i++)
    {
        outfile << saidas[i].endereco << " " << saidas[i].tipoOperacao << " " << saidas[i].dado << " " << saidas[i].resultado << endl;
    }

    outfile.close();
    infile.close();   

    return 1;
}