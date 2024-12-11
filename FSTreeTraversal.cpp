/* Max Regardie Nikola Muromcew
 * 
 * FSTreeTraversal.cpp
 *
 * This file contains the implementation for the traversetree function; 
 * specified below. 
 * Function opens a given directory and prints out the paths to each
 * file in the directory, including files within subdirectories 
 *
 */

#include "FSTree.h"
#include "DirNode.h"
#include <iostream>
#include <string>

void traverseHelper(DirNode *root, std::string message){
    if (root->isEmpty()){
        std::cout << "its empty!" << std::endl;
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
                new_message += root->getFile(i);
                new_message += "\n";
            }
            std::cout << new_message;
            new_message = "";
        }
        if (root->hasSubDir()) {
            int x = root->numSubDirs();
            message += root->getName();
            message += "/";
            for (int i = 0; i < x; i ++){
                traverseHelper(root->getSubDir(i), message);
            }
        }
    }
}


void traverse_tree(std::string directory){
    
    FSTree Tree(directory);
    
    DirNode *toproot = Tree.getRoot();
    //see if directory has files 
    //for each subdirectory, 
    std::string message = "";
    traverseHelper(toproot, message);

}

int main(int argc, char *argv[]){
    if (argc != 2){
        std::cout << "wrong!\n";
        return 0;
    }

    traverse_tree(argv[1]);
}

