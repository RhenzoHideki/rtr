#include <iostream>
#include <fstream>
#include <vector>


std::vector<std::string> encontraPaq(const std::string& dado, const std::string& paq) {
    std::vector<std::string> timeSlot;

    const int A = 256;
    const int fim = 512;
    
    if (dado.substr(A, 1) == "1" && dado.substr(fim, 8) == paq) {
        std::cout << dado.substr(0, fim);
        for (int j = 0; j < fim; j += 8) {
            timeSlot.push_back(dado.substr(j, 8));
        }
    }
    return timeSlot;
}


void mostraQuadros(const std::vector<std::string>& quadro) {
    while (true) {
        std::cout << "\nEscolha o quadro (0-" << quadro.size()/32 - 1<< ") ou -1 para mostrar todos os quadros ou pressione -2 para sair: ";
        int escolha;
        std::cin >> escolha;

        if (escolha == -2) {
            break;
        } else if (escolha == -1) {
            for (size_t i = 0; i < quadro.size(); i++) {
                std::cout << "\nQuadro " << i << ": \n" << quadro[i] << "\n";
            }
        } else if (escolha >= 0 && escolha < quadro.size()) {
            for(int i = 0; i < 32 ;i++){
            std::cout << "'" << quadro[escolha+(i*16)] << "' ,";
            }
            std::cout << std::endl;
        } else {
            std::cout << "\nQuadro inexistente!\n";
        }
    }
}


std::vector<std::string> encontraPamq(const std::string& pamq, const std::vector<std::string>& quadro) {
    std::vector<std::string> multiQuadro;
    bool isCollecting = false;

    for (const auto& q : quadro) {
        if (q.substr(0,4) == pamq) {
            if (!isCollecting) {
                multiQuadro.push_back(q);
                isCollecting = true;
            } else {
                break;
            }
        } else if (isCollecting) {
            multiQuadro.push_back(q);
        }
    }
    return multiQuadro;
}



int main() {
    std::ifstream arq("pcm30TX.txt");
    std::string dado, linha;
    while (std::getline(arq, linha)) {
        dado += linha;
    }

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
            std::vector<std::string> timeSlot = encontraPaq(dado.substr(inic), paq);

            if (!timeSlot.empty()) {
                paqVerd.push_back(inic);
                quadro.insert(quadro.end(), timeSlot.begin(), timeSlot.end());
            }

            inic += 1;
        }
    }

    std::cout << "\n\nOs PAQs verdadeiros estão nas posições:";
    for (size_t i = 0; i < paqVerd.size(); ++i) {
        std::cout << " " << paqVerd[i];
    }

    if (!quadro.empty()) {
        std::vector<std::string> quadroPamq = encontraPamq(pamq, quadro);
        mostraQuadros(quadroPamq);
    } else {
        std::cout << "\nNão há nenhum quadro dentro do arquivo!" << std::endl;
    }

    return 0;
}
