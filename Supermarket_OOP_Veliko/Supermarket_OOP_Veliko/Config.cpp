#pragma once
#include "Config.h"
void replaceLineInFile(const char* filename, int targetLine, const char* newLine) {
    ifstream inputFile(filename);
    ofstream tempFile("temp.txt");

    if (!inputFile || !tempFile) {
        cout << "Error opening file.\n";
        return;
    }

    char buffer[1024];
    int currentLine = 1;

    while (inputFile.getline(buffer, sizeof(buffer))) {
        if (currentLine == targetLine) {
            tempFile.write(newLine, strlen(newLine));
            tempFile.put('\n');
        }
        else {
            tempFile.write(buffer, strlen(buffer));
            tempFile.put('\n');
        }
        currentLine++;
    }

    // If the target line was beyond EOF, pad with empty lines
    while (currentLine <= targetLine) {
        if (currentLine == targetLine) {
            tempFile.write(newLine, strlen(newLine));
        }
        tempFile.put('\n');
        currentLine++;
    }

    inputFile.close();
    tempFile.close();

    remove(filename);
    rename("temp.txt", filename);
}

void deleteLineFromFile(const char* filename, int targetLine) {
    ifstream inputFile(filename);
    ofstream tempFile("temp.txt");

    if (!inputFile || !tempFile) {
        cout << "Error opening file.\n";
        return;
    }

    char buffer[1024];
    int currentLine = 1;

    while (inputFile.getline(buffer, sizeof(buffer))) {
        if (currentLine != targetLine) {
            tempFile.write(buffer, strlen(buffer));
            tempFile.put('\n');
        }
        currentLine++;
    }

    inputFile.close();
    tempFile.close();

    // Replace the original file
    remove(filename);
    rename("temp.txt", filename);
}