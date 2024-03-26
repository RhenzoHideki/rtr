#include "aligner.h"

string AuxBit = "1";
string FAW = "0011011";
string FAWcomplete = AuxBit + FAW; 
string jumboframe;
int alignIndex = 1;

// concatenator function to store the frame recived into final of jumboframe 
void concatenator(string frame)
{
    alignIndex++;
    jumboframe = jumboframe + frame;
}

// aligner function to align the jumboframe and extract the frames
// the aligner function find for the FAW in the jumboframe and count the number of bits before the FAW

bool finderFAW() {
    // Find the first occurrence of FAWcomplete in jumboframe
    size_t index = jumboframe.find(FAWcomplete);

    if (index == string::npos) {
        // FAWcomplete not found, return false
        return false;
    }

    //cout << "Number of bits before the FAWcomplete: " << index << endl;

    // print the 256 bits of the frame: 
    //cout << "Frame: " << jumboframe.substr(index, 256) << endl;

    // Check if the FAW complement bit is "1" on the 257th bit position after FAWcomplete
    if (jumboframe[index + 257] == '1') {
      jumboframe.erase(0, index);
        // FAW complement bit is "1", return true
        return true;
    }

    // FAW complement bit is not "1", erase the portion of jumboframe before FAWcomplete and continue searching
    jumboframe.erase(0, index + 1);

    // Recursively continue searching for FAWcomplete
    return finderFAW(); 
}


// aligner main function 

bool aligner(string frame){

    // print the jumboframe length
    //cout << "jumboframe length: " << jumboframe.length() << endl;

    if (alignIndex == 5){
        alignIndex = 0;
        if (finderFAW() != false){
            return true;
        }
    }

    return false; 
}

string frameGetter(){
    string frame = jumboframe.substr(0, 256);
    jumboframe.erase(0, 256);
    return frame;
}


