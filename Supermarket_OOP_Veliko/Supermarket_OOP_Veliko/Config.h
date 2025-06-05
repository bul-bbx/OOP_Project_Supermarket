#pragma once
#include <iostream>
#include <fstream>
using namespace std;
void replaceLineInFile(const char* filename, int targetLine, const char* newLine);
void deleteLineFromFile(const char* filename, int targetLine);
