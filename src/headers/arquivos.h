#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include "memoria.h"
using namespace std;

void geraArquivoSaida(string output, Memoria memoria)
{
    ofstream outfile;
    outfile.open(output);
    vector<Saida> saidas = memoria.saidas;
    Historico historico = memoria.historico;
    outfile << "READS: " << historico.reads << "\n";
    outfile << "WRITES: " << historico.writes << "\n";
    outfile << "HITS: " << historico.hits << "\n";
    outfile << "MISSES: " << historico.misses << "\n";
    outfile << "HIT RATE: " << setprecision(3) << historico.calculateHitRate() << "\n";
    outfile << "MISS RATE: " << setprecision(3) << historico.calculateMissRate() << endl
            << endl;
    int saidasSize = saidas.size();
    for (int i = 0; i < saidasSize; i++)
    {
        outfile << saidas[i].endereco << " " << saidas[i].tipoOperacao << ((saidas[i].dado.empty()) ? "" : " " + saidas[i].dado) << " " << saidas[i].resultado << endl;
    }

    outfile.close();
}


void leArquivoEntrada(string input, string output)
{
    int endereco, tipoOperacao;
    string line;
    ifstream infile(input);
    Memoria memoria = Memoria();
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
    geraArquivoSaida(output, memoria);
    infile.close();
}

