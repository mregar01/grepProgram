/* Max Regardie Nikola Muromcew
 * 
 * indexTree.h
 *
 * This file contains the interface of the IndexTree class which works to open 
 * files, record their paths and their names. There is a private member variable
 * which holds all of the information about the files opened.
 */

#ifndef INDEXTREE_H
#define INDEXTREE_H

#include "DirNode.h"
#include "FSTree.h"
#include <string>
#include <iostream>
#include <vector>

class indexTree{

public:

    void traverse_tree(std::string directory);
    void traverseHelper(DirNode *root, std::string message);

    struct namePath {
        std::string path;
        std::string filename;
    };

    //function to access dirContent 
    std::vector <namePath> getContent();

    void testPrint();


private:
    
    //array to store all path names and the files
    //they lead to
    std::vector <namePath> dirContent;

    void pushContent(std::string filename, std::string path);

};

#endif
