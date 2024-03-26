#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string bytesplitter(string &frame); 

void frameinterpreter(string frame, bool FawFrame);

#endif // INTERPRETER_H
