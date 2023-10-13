#include <iostream>
#include <string>

using std::string;

class No {

    No* esquerda_;
    string valor_;
    No* direita_;

    No (string valor) {
        esquerda_ = nullptr;
        valor_ = valor;
        direita_ = nullptr;
    }

    No (No* esquerda, string valor, No* direita) {
        esquerda_ = esquerda;
        valor_ = valor;
        direita_ = direita;
    }

};