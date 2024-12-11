
#include <string>
#include <iostream>
std::string stripNonAlphaNum(std::string input){
    int length = input.length();
    int counter = 0;

    for (int i = 0; i < length; i++){
        int x = input[i];
        if (((x > 47) and (x < 58)) or ((x > 64) and (x < 91)) or 
        ((x > 96) and (x < 123))){
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
        if (((x > 47) and (x < 58)) or ((x > 64) and (x < 91)) or 
        ((x > 96) and (x < 123))){
            i = -1;
        }
        else {
            counter++;
        }
    }
    input.erase(length - counter, counter);
    return input;   
}


int main(){
    std::cout << "Enter a word\n";
    std::string word;
    std::cin >> word;

    std::cout << stripNonAlphaNum(word) << std::endl;
    
}
