#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <bitset>
using namespace std;

class Endereco
{
public:
    int decimal;
    string binario;
    string tag;
    string indice;
    string offset;
    Endereco() {}
    Endereco(int decimal)
    {
        this->binario = bitset<32>(decimal).to_string();
        this->indice = binario.substr(22, 6);
        this->offset = binario.substr(28, 4);
        this->tag = binario.substr(0, 22);
        this->decimal = decimal;
    }
};

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
    vector<Endereco> enderecos;
    Operacoes operacoes;
    vector<Saida> saidas;
    Memoria()
    {
        this->operacoes = Operacoes();
    }
    void addEntrada(Entrada entrada)
    {
        string resultado = this->realizaOperacao(entrada.tipoOperacao, entrada.endereco);
        this->geraSaida(entrada, resultado);
    }

private:
    string realizaOperacao(int tipoOperacao, Endereco endereco)
    {
        string resultado = "";
        if (tipoOperacao == 1)
        {
            enderecos.push_back(endereco);
            resultado = "W";
            operacoes.writes += 1;
        }

        else
        {
            operacoes.reads += 1;
            resultado = readDado(endereco);
        }

        return resultado;
    }
    string readDado(Endereco novoEndereco)
    {
        int enderecosSize = enderecos.size();
        for (int i = 0; i < enderecosSize; i++)
        {
            Endereco it = enderecos.at(i);
            if (it.tag == novoEndereco.tag && it.indice == novoEndereco.indice)
            {
                operacoes.hits += 1;
                return "H";
            }
        }

        operacoes.misses += 1;
        enderecos.push_back(novoEndereco);
        return "M";
    }
    void geraSaida(Entrada entrada, string resultado)
    {
        saidas.push_back(Saida(entrada.endereco.decimal, entrada.tipoOperacao, entrada.dado, resultado));
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
    outfile << "HIT RATE: " << setprecision(3) << operacoes.calculateHitRate() << "\n";
    outfile << "MISS RATE: " << setprecision(3) << operacoes.calculateMissRate() << endl << endl;
    int saidasSize = saidas.size();
    for (int i = 0; i < saidasSize; i++)
    {
        outfile << saidas[i].endereco << " " << saidas[i].tipoOperacao << ((saidas[i].dado.empty()) ? "" : " " + saidas[i].dado) << " " << saidas[i].resultado << endl;
    }

    outfile.close();
    infile.close();

    return 1;
}