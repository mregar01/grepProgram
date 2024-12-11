/* Max Regardie Nikola Muromcew
 * 
 * indexTree.cpp
 *
 * This file contains the implementation of the IndexTree class
 * which works to open files, record their paths and their names
 */

#include "indexTree.h"
#include <string>
#include <iostream>

//name: Traverse_tree
//purpose: prints out all file paths in provided directory
//arguments: string name of directory to be opened
//returns: none, void
//effects: prints all path names of all files 
void indexTree::traverse_tree(std::string directory){
    
    FSTree Tree(directory);
    
    DirNode *toproot = Tree.getRoot();
    std::string message = "";
    traverseHelper(toproot, message);
}

//name: TraverseHelper
//purpose: recursively follows an FST tree to find file path names
//arguments: root of an index tree, message to be printed
//returns: none, void
//effects: none
void indexTree::traverseHelper(DirNode *root, std::string message){
    if (root->isEmpty()){
        message += root->getName();
        message += "\n";
        std::cout <<  message;
    }
    else {
        if (root->hasFiles()){ 
            std::string new_message;
            int x = root->numFiles();
            for (int i = 0; i < x; i ++){
                new_message += message;
                new_message += root->getName();
                new_message += "/"; 
                new_message += root->getFile(i); //update pathname
                pushContent(root->getFile(i), new_message);//add namePaths
                new_message = "";
            }
        }
        if (root->hasSubDir()) {
            int x = root->numSubDirs();
            message += root->getName();
            message += "/";
            for (int i = 0; i < x; i ++){
                traverseHelper(root->getSubDir(i), message);//recurse
            }
        }
    }
}

//name: getContent
//purpose: return vector of namePaths to be used in other classes
//arguments: none
//returns: vector of namePath structs
//effects: none
std::vector <indexTree::namePath> indexTree::getContent(){
    return dirContent;
}

//name: pushContent
//purpose: add a new namePath to end of array
//arguments: string of filename and string of path 
//returns: none, void
//effects: increases size of dirContent via push_back function,
//adds new namePath to back of dirContent array
void indexTree::pushContent(std::string filename, std::string path){
    namePath newone;
    newone.path = path;
    newone.filename = filename;

    dirContent.push_back(newone);
}

//testing function used to test tree indexing
void indexTree::testPrint(){
    int limit = dirContent.size();
    for (int i = 0; i < limit; i ++){
        std::cout << "path: " << dirContent[i].path << " ";
        std::cout << "filename: " << dirContent[i].filename << std::endl;
    }
}


