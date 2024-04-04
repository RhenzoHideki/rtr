#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <stdexcept>
#include "alinhador.h"

using namespace std;

string divisorFrames(string &frame){
    string byte = frame.substr(0,8);
    frame.erase(0,8);
    return byte;
}

void interpretador(string frame, bool PAQ){
    vector<string> componentes;
    for(int i=0; i<32; i++){
        componentes.push_back(divisorFrames(frame));
    }

    if(PAQ){
        cout << "Palavra de Alinhamento do (PAQ): " << componentes[0] <<endl;
    }else{
        cout << "Byte auxiliar 1: " << componentes[0] << endl;
    }
    cout << "Byte de sinalização: " << componentes[16] << endl;

    for(int i = 1; i < 16; i++){
        if(i < 9){
            cout << "Time Slot - " << i+1 << " " << componentes[i] << " " << "|" << " ";
        }else{
            cout << "Time Slot - " << i+1 << " "  << componentes[i] << " " << "|" << " ";
        }
    }
    cout << endl;
    for(int i = 17; i < 32; i++){
        cout << "Time Slot - " << i << ": " << componentes[i] << " " << "|" << " ";
    }
    cout << endl;

}

string leitorFrames(int frameIndex, const string arquivoNome){
    ifstream arq(arquivoNome);
    if(!arq.is_open()){
        throw runtime_error("Arquivo invalido");
    }

    vector<string> linhas;
    string linha;
    
    while(getline(arq,linha)){
        linhas.push_back(linha);
    }
    
    if (frameIndex >= linhas.size())
    {
        throw runtime_error("Frame index fora do range");
    }

    return linhas[frameIndex];
}

int main(){
    bool alinhamento = false;
    int frameindex = 1;

    for(int i=0; i<20 ; i++){
        string frame = leitorFrames(i,"pcm30TX.txt");
        concatenador(frame);

        if(!alinhamento){
            alinhamento = alinha(frame);
        }else{
            cout << endl;
            
            cout << "Frame " << frameindex << " content: " << endl;

            if(frameindex % 2 != 0){
                string frame = capturaFrame();
                interpretador(frame,true);
            }else{
                string frame = capturaFrame(); 
                interpretador(frame,true);
            }
        frameindex++;
        }       
    usleep(125000);
    }
    

}