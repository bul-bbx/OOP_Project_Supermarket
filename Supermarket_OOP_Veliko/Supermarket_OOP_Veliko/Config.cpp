#include "Config.h"
void replaceLineInFile(const string& filename, int lineNumber, string& newLine) {
    ifstream inFile(filename);
    vector<std::string> lines;
    string line;

    // Step 1: Read all lines into memory
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    // Step 2: Modify the desired line (check bounds)
    if (lineNumber >= 0 && lineNumber < lines.size()) {
        lines[lineNumber] = newLine;
    }
    else {
        std::cerr << "Line number out of range!" << std::endl;
        return;
    }

    // Step 3: Write everything back to the file
    ofstream outFile(filename);
    for (const auto& l : lines) {
        outFile << l << "\n";
    }
}

void deleteLineFromFile(const string& filename, int lineToDelete) {
    ifstream inFile(filename);
    vector<string> lines;
    string line;

    // Step 1: Read all lines
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    // Step 2: Check bounds and remove line
    if (lineToDelete >= 0 && lineToDelete < lines.size()) {
        lines.erase(lines.begin() + lineToDelete);
    }
    else {
        cerr << "Error: line number out of range.\n";
        return;
    }

    // Step 3: Write all remaining lines back to the file
    ofstream outFile(filename);
    for (const auto& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();
}