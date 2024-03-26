#include "alinhador.h"

string bitAuxiliar = "1";
string FAW = "0011011";
string fullFAW = bitAuxiliar + FAW;
string longFrame;
int alinhamentoIndex = 1;

void concatenador(string frame){
    alinhamentoIndex ++;
    longFrame = longFrame + frame;
}

string capturaFrame(){
    string frame = longFrame.substr(0,256);
    longFrame.erase(0,256);
    return frame;
}

bool alinha(string frame){
    if(alinhamentoIndex == 5){
        alinhamentoIndex = 0;
        if(procuraFAW() != false){
            return true;
        }
    }
    return false;
}

bool procuraFAW(){
    size_t index = longFrame.find(fullFAW);
    
    if(index == string::npos){
        return false;
    }

    if(longFrame[index + 257] == '1'){
        longFrame.erase(0,index);
        return true;
    }
    longFrame.erase(0,index + 1);

    return procuraFAW();

}