#include "frameimporter.h"
#include <fstream>
#include <stdexcept>

// function to import a frame from a file, witch is a string on a line. 
// The frameindex is the line number to import from the file
std::string importFrame(int frameindex, const std::string& filename) {
    // open the file
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    // read the file into a vector of strings
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    // if the frameindex is out of range, throw an exception
    if (frameindex >= lines.size()) {
        throw runtime_error("Frame index out of range");
    }

    // return the frame
    return lines[frameindex];
}
