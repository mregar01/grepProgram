
/* Max Regardie Nikola Muromcew
 * 
 * fileHash.h
 * 
 * Interface for class that contains all functions and variables used to 
 * hash the words of all provided files. Places words into two seperate hash
 * tables, one for case sensitive search and one for case insensitive search
 * 
 *
 */

#ifndef FILEHASH_H
#define FILEHASH_H

#include "indexTree.h"
#include <string>
#include <iostream>
#include <functional>
#include <array>
#include <vector>


class fileHash {

public:
    
    //constructor
    fileHash();

    ~fileHash();

    void doGerp(std::string currword, std::ostream &output, bool sensitive);

    
    
    //read file contents, Hash words
    //sensitively
    void getSensitive();

    //read file contents, Hash words
    //insensitively
    void getInSensitive();

    struct pathLine{
        std::string word;
        std::string path;
        std::string line;
        int lineNumber;
    };

    void printInfo(pathLine foundword, std::ostream &output);

    std::string stripNonAlphaNum(std::string input);

    void setDirContent(std::string dirName);

    void openFiles(bool sensitive);

private:
    
    indexTree IndexArray;

    std::vector<fileHash::pathLine> *SensitiveHash;
    std::vector<fileHash::pathLine> *InsensitiveHash; 

    std::vector <indexTree::namePath> directoryContent;

    void readLines(std::ifstream &input, std::string path, bool sensitive);

    void hashLine(std::stringstream &input, fileHash::pathLine LineData,
    bool sensitive);

    void hashWord(bool ifSensitive, pathLine data);

    bool findMatch(int index, fileHash::pathLine currpath, bool sensitive);
    
    void open_or_die_in(std::ifstream &stream, std::string file_name); 

    std::string toLowercase(std::string s);

};

#endif