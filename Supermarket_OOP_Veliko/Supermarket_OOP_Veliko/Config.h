#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
void replaceLineInFile(const string& filename, int lineNumber, string& newLine);
void deleteLineFromFile(const string& filename, int lineToDelete);
