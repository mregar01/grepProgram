/* Max Regardie Nikola Muromcew
 * 
 * gerp.cpp
 *
 * This file contains the implementation for Gerp Class. Main tasks include
 * interacting with user via command loop and connecting the indexTree
 * class and fileHash class to be able to perform a quick word search
 * on a given tree
 *
 */

#include "gerp.h"
#include <string>
#include <iostream>


//name: runGame
//purpose: read files, hash contents, prepare query loop
//arguments: file names for input and output 
//returns: none, void
//effects: calls upon helper functions, runs command loops
void gerp::runGame(std::string input, std::string output){
    theHash.setDirContent(input);
    theHash.openFiles(true); //open for sensitive
    theHash.openFiles(false); //open for insensitive
    outputName = output;
    open_or_die_out(outputFile, outputName);

    std::cout << "Query? ";
    takeQuery(outputFile);
    outputFile.close();
}

//name: takeQuery
//purpose: ask user for a query and call upon appropriate helper functions
//arguments: address of file to print items to
//returns: none
//effects: calls upon other function, eventually prints out found word data,
//prints to output file
void gerp::takeQuery(std::ofstream &output){
    std::string command = "";
    while (std::cin >> command){
        if (command == "@i"){
            command = "";
            std::string commandword = "";
            std::cin >> commandword;
            commandword = stripNonAlphaNum1(commandword);
            if (commandword == ""){
                output << commandword << " Not Found.\n";
            } else {
                theHash.doGerp(commandword, output, false);//take in word and     
            }                              //strip characters then run gerp  
        } else if (command == "@f"){
            output.close();
            std::cin >> outputName; 
            open_or_die_out(outputFile, outputName); //open new output dest.
        } else if (command == "@q" or command == "@quit"){
            std::cout << "Goodbye! Thank you and have a nice day.\n";
            return;
        } else {
            std::string commandword = stripNonAlphaNum1(command);
            if (commandword == ""){
                output << commandword << 
                " Not Found. Try with @insensitive or @i.\n";
            } else {
                theHash.doGerp(commandword, output, true);
            }
        } std::cout << "Query? ";
    }
    std::cout << "Goodbye! Thank you and have a nice day.\n";
    return;
}

//name: stripNonAlphaNum1
//purpose: edit a string to remove leading and trailing non-letter or number
//characters
//arguments: string to edit
//returns: edited string
//effects: if initial string starts or ends with special characters, reduces
//length of string, however, not always applicable to all strings. 
std::string gerp::stripNonAlphaNum1(std::string input){
    int length = input.length();
    int counter = 0;

    for (int i = 0; i < length; i++){
        int x = input[i];
        if (isalnum(x)){
            i = length;
        }
        else {
            counter++;
        }
    }
    input.erase(0, counter);
    length = input.length();
    counter = 0;

    for (int i = length - 1; i > -1; i--){
        int x = input[i];
        if (isalnum(x)){
            i = -1;
        }
        else {
            counter++;
        }
    }
    input.erase(length - counter, counter);
    return input;
}

//name: toLowercase
//purpose: turn a string into all lowercase letters
//arguments: string to turn
//returns: all-lowercase string
//effects: loops through string, makes all chars lowercase
std::string gerp::toLowercase(std::string s){
    std::string to_return;
    int size = s.length();
    for (int i = 0; i < size; i++){
        to_return += tolower(s[i]);
    }
    return to_return;
}

//name: open_or_die_out
//purpose: Try to open the given file, thrown runtime error on failure. If
//the function returns, caller can assume stream is open
//arguments: address of an outfile stream and the name of the file to be opened
//returns: nothing
//effects: none
void gerp::open_or_die_out(std::ofstream &stream, std::string file_name){
    stream.open(file_name);
    if (not stream.is_open()){
        std::string error_message = "Unable to open file " + file_name;
        throw std::runtime_error(error_message);
    }
}