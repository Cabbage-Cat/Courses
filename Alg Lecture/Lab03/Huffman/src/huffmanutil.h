
#ifndef _huffmanutil_h
#define _huffmanutil_h

#include <iostream>
#include <string>
using namespace std;

/*
 * Checks whether the given file exists; if it does, prompts the user whether
 * they want to overwrite the file.  Returns true if the user does want to
 * overwrite, and false if not.
 */
bool confirmOverwrite(string filename);

/*
 * Returns the size of the given file in bytes.
 */
int fileSize(string filename);

/*
 * Repeatedly asks the user to type a file name using the given prompt message
 * until the user types the name of a file that exists, then returns that file's name.
 */
string promptForExistingFileName(string prompt);


#endif
