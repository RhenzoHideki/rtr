#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "pamq.h"

string pamq = "0000";

std::vector<std::string> encontrarPAMQ(vector<vector<std::string>> quadro) {
    std::vector<std::string> multiQuadro;

    for (const auto& q : quadro) {           // Cria um iterador para os quadros
        if (q[16].substr(0,3) == pamq) {       // Verifica se o time slot 16 possui o PAMQ
            if (multiQuadro.empty()) {       // Se ainda não houver um multiquadro sendo formado, o inicia
                multiQuadro.push_back(q[16]);
            } else {
                break;
            }
        } else if (!multiQuadro.empty()) {
            multiQuadro.push_back(q[16]);
        }
    }

    return multiQuadro;
}



void mostrarQuadros(vector<std::string> quadro) {
    while (true) {
        try {
            std::cout << "\nEscolha o quadro (0-" << quadro.size()-1 << ") ou -1 para mostrar todos os quadros ou pressione -2 para sair: ";
            int escolha;
            std::cin >> escolha;

            if (escolha == -2) {
                break;
            } else if (escolha == -1) {
                for (size_t i = 0; i < quadro.size(); ++i) {
                    std::cout << "\nQuadro " << i << ":\n" << quadro[i] << std::endl;
                }
            } else if (escolha >= 0 && escolha < quadro.size()) {
                std::cout << "\n" << quadro[escolha] << std::endl;
            } else {
                std::cout << "\nQuadro inexistente!" << std::endl;
            }
        } catch(...) {
            std::cout << "\nEntrada inválida!" << std::endl;
        }
    }
}
