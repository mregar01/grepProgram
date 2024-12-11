/* Max Regardie Nikola Muromcew
 * 
 * main.cpp
 *
 * Project main for gerp. Takes in command line arguments and then calls upon
 * gerp class to run the gerp simulation.
 *
 */

#include "gerp.h"
#include "indexTree.h"
#include "fileHash.h"
#include <string>


int main(int argc, char *argv[]){
    if (argc != 3){
        std::cerr << "Usage: ./gerp inputDirectory outputFile\n";
        exit(EXIT_FAILURE);
    }
    gerp the_gerp;
    the_gerp.runGame(argv[1], argv[2]);

}