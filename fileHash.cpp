
/* Max Regardie Nikola Muromcew
 * 
 * fileHash.cpp
 * 
 * Implementation for class that contains all functions and variables used to 
 * hash the lines of all provided files
 * 
 */

#include "fileHash.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <array>

//empty constructore for c++ :)
fileHash::fileHash(){
    SensitiveHash = new std::vector<fileHash::pathLine>[100000];
    InsensitiveHash = new std::vector<fileHash::pathLine>[100000];
}

fileHash::~fileHash(){
    delete [] SensitiveHash;
    delete [] InsensitiveHash;
}

//name: doGerp
//purpose: find given word in hashtable, print out all line and paths for word
//arguments: word to find, output file to print to, bool to search sensitive 
//or not
//returns: none
//effects: prints to output file all paths and lines with 
//given word
void fileHash::doGerp(std::string currword, std::ostream &output, 
    bool sensitive){
    bool wordfound = false;
    if (sensitive){
        //locate bucket index, go through bucket and print all correct matches
        int index = std::hash<std::string>{}(currword) % 100000;
        int bucketsize = SensitiveHash[index].size();
        for (int i = 0; i < bucketsize; i++){
            if (SensitiveHash[index].at(i).word == currword){
                printInfo(SensitiveHash[index].at(i), output);
                wordfound = true;
            }
        } if (not wordfound){
            output << currword << " Not Found. Try with @insensitive or @i.\n";
            }
        }
    if (not sensitive) {
        std::string findword = toLowercase(currword);
        int index;
        //locate bucket index, go through bucket and print all correct matches
        index = std::hash<std::string>{}(findword) % 100000;
        int bucketsize = InsensitiveHash[index].size();
        for (int i = 0; i < bucketsize; i++){
            if(InsensitiveHash[index].at(i).word == findword){
                printInfo(InsensitiveHash[index].at(i), output);
                wordfound = true;
            }
        } if (not wordfound){
        output << currword << " Not Found.\n";
    }}
}

//name: printInfo
//purpose: print out path, line number, and line where desired word in found
//arguments: pathLine containing line number and path data etc, and output
//to print to
//returns: none
//arguments: prints line to output file
void fileHash::printInfo(fileHash::pathLine foundword, std::ostream &output){
    output << foundword.path << ":" << foundword.lineNumber << ": " 
    << foundword.line << std::endl;
}

//name: openFiles
//purpose: open all files in a given array of file from a directory
//arguments: none
//returns: none
//effects: opens all files, calls upon readLines() function
void fileHash::openFiles(bool sensitive){
    int limit = IndexArray.getContent().size();
    for (int i = 0; i < limit; i++){
        std::ifstream input;
        open_or_die_in(input, directoryContent[i].path);
        if (sensitive){
            //read lines of each file in directory 
            readLines(input, directoryContent[i].path, true);
        }
        else {
            //read lines of each file in directory
            readLines(input, directoryContent[i].path, false);
        }
        //close the file
        input.close();
    }
}

//name: readLines();
//purpose: from an open file, read each line
//arguments: input file, an opened file to read
//returns: none, void
//effects: calls upon hashLine functions for Insensitive hash 
void fileHash::readLines(std::ifstream &input, std::string path, 
    bool sensitive){
    std::string currline = "";
    int currlinenum = 1;
    
    pathLine LineData = {"",path, currline, currlinenum};
    if (sensitive){
        //read a line from file, pass to hashline
        while (getline(input, currline)){
            std::stringstream ss;
            ss << currline;
            LineData.line = currline;
            LineData.lineNumber = currlinenum;
            hashLine(ss, LineData, true);
            currlinenum++;
        }
    } else {
        //read a line from file, pass to hashline
        while (getline(input, currline)){
           LineData.line = currline;
           LineData.lineNumber = currlinenum;
           std::stringstream ss;
           ss << currline;
           hashLine(ss, LineData, false);
           currlinenum++; 
        }
}}

//name: hashLine
//purpose: read each word of a given line and populate hash table 
//arguments: stringstream line to be read, bool of if sensitive hash
//or not
//returns: none
//effects: adds pathLines to HashSensitive or HashInsensitive array
void fileHash::hashLine(std::stringstream &input, 
fileHash::pathLine LineData, bool sensitive){
    std::string currword;
    if (sensitive){
    while(input >> currword){
        LineData.word = currword;
        hashWord(true, LineData);
        } 
    }
    else {
        while(input >> currword){
        LineData.word = currword;
        hashWord(false, LineData);
        }
    }
}

//name: hashWord
//purpose: sort a word into hashtable and store its corresponding data
//arguments: bool value if to be hashed sensitive or not, word data 
//returns: none
//effects: hashes word (via pathLine) and puts into appropriate array
void fileHash::hashWord(bool ifSensitive, fileHash::pathLine data){
    std::string hashword = stripNonAlphaNum(data.word);
    data.word = hashword;
    if (ifSensitive){
        int index = std::hash<std::string>{}(hashword) % 100000;
        if (SensitiveHash[index].size() != 0){ 
            if (not findMatch(index, data, true)){ //if not a repeat line, add 
                
                SensitiveHash[index].push_back(data);
            }
        } else {
            std::vector<fileHash::pathLine> bucket;
            bucket.push_back(data);
            SensitiveHash[index] = bucket;
        }  
    } else {
        data.word = toLowercase(data.word);
        int index = 0;
        index = std::hash<std::string>{}(data.word) % 100000;
        if (InsensitiveHash[index].size() != 0){
            if (not findMatch(index, data, false)){//if not a repeat line, add 
                InsensitiveHash[index].push_back(data);
            }
        }
        else {
            std::vector<fileHash::pathLine> bucket;
            bucket.push_back(data);
            InsensitiveHash[index] = bucket;
        }
    }
}

//name: findMatch
//purpose: within a bucket, see if current path and line number already exist,
//this is to avoid duplicate lines
//arguments: index of bucket and pathline to compare, bool of if sensitive 
//returns: bool, true is match is found
//effects: none
bool fileHash::findMatch(int index, fileHash::pathLine currpath, 
bool sensitive){
    if(sensitive){ //if sensitive Hash
            if ((currpath.word == SensitiveHash[index].back().word) and 
            (currpath.path == SensitiveHash[index].back().path) and
            (currpath.line == SensitiveHash[index].back().line) and
            (currpath.lineNumber == SensitiveHash[index].back().lineNumber)){
                //if the same word in the same file in the same line at the
                //same line number in file, return true
                return true;
            } 
    } else { //if insensitiveHash
            if ((currpath.word == InsensitiveHash[index].back().word) and 
            (currpath.path == InsensitiveHash[index].back().path) and
            (currpath.line == InsensitiveHash[index].back().line) and
            (currpath.lineNumber == InsensitiveHash[index].back().lineNumber)){
                //if the same word in the same file in the same line at the
                //same line number in file, return true
                return true;
            }
    }
    return false;
}

//name: stripNonAlphaNum
//purpose: edit a string to remove leading and trailing non-letter or number
//characters
//arguments: string to edit
//returns: edited string
//effects: if initial string starts or ends with special characters, reduces
//length of string, however, not always applicable to all strings. 
std::string fileHash::stripNonAlphaNum(std::string input){
    int length = input.length();
    int counter = 0;

    for (int i = 0; i < length; i++){
        int x = input[i];
        if (isalnum(x)){
            i = length;
        }
        else {
            counter++;
            //keeps track of number of nonAlpha chars
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
            //keeps track of number of nonAlpha chars
        }
    }
    input.erase(length - counter, counter);
    return input;
}

//name: open_or_die_in
//purpose: Try to open the given file, thrown runtime error on failure. If
//the function returns, caller can assume stream is open
//arguments: address of an infile stream and the name of the file to be opened
//returns: nothing
//effects: none
void fileHash::open_or_die_in(std::ifstream &stream, std::string file_name){
    stream.open(file_name);
    if (not stream.is_open()){
        std::string error_message = "Unable to open file " + file_name;
        throw std::runtime_error(error_message);
    }
}

//name: setDirContent
//purpose: from indexArray, fill array with file names and their paths
//arguments: directory name to read
//returns: none
//effects: traverses tree and fills directoryContent with directory files
void fileHash::setDirContent(std::string dirName){
    IndexArray.traverse_tree(dirName);
    directoryContent = IndexArray.getContent();
}

//name: toLowercase
//purpose: turn a string into all lowercase letters
//arguments: string to turn
//returns: all-lowercase string
//effects: loops through string, makes all chars lowercase
std::string fileHash::toLowercase(std::string s){
    std::string to_return;
    int size = s.length();
    for (int i = 0; i < size; i++){
        to_return += tolower(s[i]);
    }
    return to_return;
}