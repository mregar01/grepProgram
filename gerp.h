/* Max Regardie Nikola Muromcew
 * 
 * gerp.h
 *
 * This file contains the interface for Gerp Class. Main tasks include
 * interacting with user via command loop and connecting the indexTree
 * class and fileHash class to be able to perform a quick word search
 * on a given tree
 *
 */

#ifndef GERP_H
#define GERP_H

#include "indexTree.h"
#include "fileHash.h"
#include <fstream>

class gerp{
public:

    //name of directory to search and index
    std::string DirName;

    void runGame(std::string input, std::string output);
    
private:

    fileHash theHash;

    std::ofstream outputFile;

    std::string outputName;

    std::string toLowercase(std::string s);

    void takeQuery(std::ofstream &output);

    std::string stripNonAlphaNum1(std::string input);

    void open_or_die_out(std::ofstream &stream, std::string file_name);

};
#endif