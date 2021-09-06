#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include "./headers/arquivos.h"
using namespace std;

int main(int argc, char **argv)
{
    string input = argv[1];
    string output = argv[2];
    leArquivoEntrada(input, output);
    return 1;
}