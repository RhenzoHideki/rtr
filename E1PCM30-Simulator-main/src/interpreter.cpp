#include "interpreter.h"

int frameslot = 0; 

string binaryToHex(const string &binary) {
    stringstream ss;
    ss << std::hex << std::setfill('0');
    
    // convert every 8 bits to a hex number
    for (size_t i = 0; i < binary.length(); i += 8) {
        string byte = binary.substr(i, 8); 
        int value = std::stoi(byte, nullptr, 2); 
        ss << setw(2) << value;
    }
    
    return ss.str();
}

string bytesplitter(string &frame){
    // get 8 characters substring of the main string
    string byte = frame.substr(0, 8); 
    frame.erase(0, 8);
    return byte; 
}

void frameinterpreter(string frame, bool FawFrame){
    // split the PCM30 frame into its components 
    vector<string> frameComponents;
    for (int i = 0; i < 32; i++){
        frameComponents.push_back(bytesplitter(frame));
    }

    if(FawFrame){
        cout << "Frame Alignment Word: " << frameComponents[0] << endl;
    }else{  
        cout << "Aux byte 1: " << frameComponents[0] << endl;
    }
    cout << "Sinalization Slot: " << frameComponents[16] << endl;
    
    for (int i = 1; i < 16; i++){

        if (i < 9)
        {
        cout << "FS-" << "0" << i+1 << ": " << binaryToHex(frameComponents[i]) << " " << "|" << " ";
        }else 
        {
        cout << "FS-" << i+1 << ": " << binaryToHex(frameComponents[i]) << " " << "|" << " ";
        }
    }
    cout << endl;
    for (int i = 17; i < 32; i++){
        cout << "FS-" << i << ": " << binaryToHex(frameComponents[i]) << " " << "|" << " ";
    }
    cout << endl;
}
