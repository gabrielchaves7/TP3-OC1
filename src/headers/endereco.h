#include <iostream>
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