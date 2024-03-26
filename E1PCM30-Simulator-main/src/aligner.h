#ifndef ALIGNER_H
#define ALIGNER_H

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

void concatenator(string frame); 

bool finderFAW();

bool aligner(string frame);

string frameGetter();

#endif