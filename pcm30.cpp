#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<std::string> encontraPaq(std::string dado, std::string paq) {
    std::vector<std::string> timeSlot;

    int A = 256;
    int fim = 512;

    if (dado.substr(A, 1) == "1" && dado.substr(fim, 8) == paq) {
        std::cout << dado.substr(0, fim);

        for (int j = 0; j < fim; j += 8) {
            timeSlot.push_back(dado.substr(j, 8));  // Adiciona na lista 'timeSlot', de 8 em 8 bits
        }
    }

    return timeSlot;
}

void mostraQuadros(std::vector<std::string> quadro) {
    while (true) {
        try {
            int escolha;
            std::cout << "\nEscolha o quadro (0-" << quadro.size()-1 << ") ou -1 para mostrar todos os quadros ou pressione -2 para sair: ";
            std::cin >> escolha;

            if (escolha == -2) {
                break;
            } else if (escolha == -1) {
                for (int i = 0; i < quadro.size(); ++i) {
                    std::cout << "\nQuadro " << i << ": \n" << quadro[i];
                }
            } else if (escolha >= 0 && escolha < quadro.size()) {
                std::cout << "\n" << quadro[escolha];
            } else {
                std::cout << "\nQuadro inexistente!";
            }
        } catch(...) {
            std::cout << "\nEntrada inválida!";
        }
    }
}

std::vector<std::string> encontraPamq(std::string pamq, std::vector<std::string> quadro) {
    std::vector<std::string> multiQuadro;

    for (const auto& q : quadro) {
        if (q.substr(16, 4) == pamq) {
            if (multiQuadro.empty()) {
                multiQuadro.push_back(q);
            } else {
                break;
            }
        } else if (!multiQuadro.empty()) {
            multiQuadro.push_back(q);
        }
    }

    return multiQuadro;
}

int main() {
    std::ifstream arq("RX(vetor)MQ_v2.txt");
    std::string dado((std::istreambuf_iterator<char>(arq)), std::istreambuf_iterator<char>());
    arq.close();

    dado.erase(std::remove(dado.begin(), dado.end(), ' '), dado.end());

    size_t inic = 0;
    std::vector<std::string> quadro;
    std::string paq = "10011011";
    std::vector<size_t> paqVerd;
    std::string pamq = "0000";

    std::cout << "\nBits alinhados:";

    while (true) {
        inic = dado.find(paq, inic);

        if (inic == std::string::npos) {
            break;
        } else {
            auto timeSlot = encontraPaq(dado.substr(inic), paq);

            if (!timeSlot.empty()) {
                paqVerd.push_back(inic);
                quadro.insert(quadro.end(), timeSlot.begin(), timeSlot.end());
            }

            inic += 1;
        }
    }

    std::cout << "\n\nOs PAQs verdadeiros estão nas posições: ";
    for (size_t i = 0; i < paqVerd.size(); ++i) {
        std::cout << paqVerd[i];
        if (i != paqVerd.size() - 1) {
            std::cout << ", ";
        }
    }

    if (!quadro.empty()) {
        auto multiQuadro = encontraPamq(pamq, quadro);
        mostraQuadros(multiQuadro);
    } else {
        std::cout << "Não há nenhum quadro dentro do arquivo!";
    }

    return 0;
}
