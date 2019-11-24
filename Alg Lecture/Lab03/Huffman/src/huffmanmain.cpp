
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "filelib.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "HuffmanNode.h"
#include "encoding.h"
#include "huffmanutil.h"
using namespace std;

const string DEFAULT_COMPRESSED_FILE_EXTENSION = ".huf";
const string DEFAULT_DECOMPRESSED_FILE_EXTENSION = ".txt";

string menu();

void test_compress();
void test_decompress();

int main() {
    
    while (true) {
        string choice = menu();
        if (choice == "Q") {
            break;
        } else if (choice == "C") {
            test_compress();
        } else if (choice == "D") {
            test_decompress();
        }
    }

    cout << "Exiting." << endl;
    return 0;
}


/*
 * Prints a menu of choices for the user and reads/returns the user's response.
 */
string menu() {
    cout << endl;
    cout << "C) compress file" << endl;
    cout << "D) decompress file" << endl;
    cout << "Q) quit" << endl;
    cout << endl;
    string choice = toUpperCase(trim(getLine("Your choice? ")));
    return choice;
}

/*
 * Tests the compress function.
 * Prompts for input/output file names and opens streams on those files.
 * Then calls your compress function and displays information about how many
 * bytes were written, if any.
 */
void test_compress() {
    string inputFileName = promptForExistingFileName("Input file name: ");
    ifstream input;
    ofbitstream output;
    string defaultOutputFileName = getRoot(inputFileName) + DEFAULT_COMPRESSED_FILE_EXTENSION;
    string outputFileName = trim(getLine("Output file name (Enter for "
                                    + defaultOutputFileName + "): "));
    if (outputFileName == "") {
        outputFileName = defaultOutputFileName;
    }
    if (inputFileName == outputFileName) {
        cout << "You cannot specify the same file as both the input file" << endl;
        cout << "and the output file.  Aborting." << endl;
        return;
    }
    if (!confirmOverwrite(outputFileName)) {
        return;
    }

    int inputFileSize = fileSize(inputFileName);
    cout << "Reading " << inputFileSize << " uncompressed bytes." << endl;
    input.open(inputFileName.c_str(), ifstream::binary);
    output.open(outputFileName.c_str());
    cout << "Compressing ..." << endl;
    compress(input, output);
    input.close();
    output.flush();
    output.close();

    if (fileExists(outputFileName)) {
        cout << "Wrote " << fileSize(outputFileName) << " compressed bytes." << endl;
    } else {
        cout << "Compressed output file was not found; perhaps there was an error." << endl;
    }
}

/*
 * Tests the decompress function.
 * Prompts for input/output file names and opens streams on those files.
 * Then calls your decompress function and displays information about how many
 * bytes were written, if any.
 */
void test_decompress() {
    string inputFileName = promptForExistingFileName("Input file name: ");
    ifbitstream input;
    ofstream output;
    string defaultOutputFileName = getRoot(inputFileName) + "-out" + DEFAULT_DECOMPRESSED_FILE_EXTENSION;
    string outputFileName = trim(getLine("Output file name (Enter for "
                                    + defaultOutputFileName + "): "));
    if (outputFileName == "") {
        outputFileName = defaultOutputFileName;
    }
    if (inputFileName == outputFileName) {
        cout << "You cannot specify the same file as both the input file" << endl;
        cout << "and the output file.  Aborting." << endl;
        return;
    }
    if (!confirmOverwrite(outputFileName)) {
        return;
    }

    int inputFileSize = fileSize(inputFileName);
    cout << "Reading " << inputFileSize << " compressed bytes." << endl;
    input.open(inputFileName.c_str());
    output.open(outputFileName.c_str(), ofstream::binary);
    cout << "Decompressing ..." << endl;
    decompress(input, output);
    input.close();
    output.flush();
    output.close();

    if (fileExists(outputFileName)) {
        cout << "Wrote " << fileSize(outputFileName) << " decompressed bytes." << endl;
    } else {
        cout << "Decompressed output file was not found; perhaps there was an error." << endl;
    }
}

