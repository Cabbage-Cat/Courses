
#include "huffmanutil.h"
#include "bitstream.h"
#include "filelib.h"
#include "simpio.h"

bool confirmOverwrite(string filename) {
    if (!fileExists(filename)) {
        return true;
    } else {
        return getYesOrNo(filename + " already exists.  Overwrite? (y/n) ");
    }
}

int fileSize(string filename) {
    ifstream input;
    input.open(filename.c_str(), ifstream::binary);
    input.seekg(0, ifstream::end);
    return (int) input.tellg();
}

string promptForExistingFileName(string prompt) {
    while (true) {
        string filename = getLine(prompt);
        if (fileExists(filename)) {
            return filename;
        } else {
            cout << "That file does not exist; please try again." << endl;
        }
    }
    return "";
}

