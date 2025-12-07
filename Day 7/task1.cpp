#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>


void analyzeLine(std::string line, std::vector<bool> &beam, int32_t &counter);

int main() {

    std::string line;

    std::ifstream myfile ("example.txt");

    int32_t counter {0};

    std::vector<bool> beam {};

    if(myfile.is_open()) {

        std::getline(myfile, line);

        for(int i = 0; i < line.length(); i++) {
            if(line[i] == 'S') {
                beam.push_back(true);
            } else {
                beam.push_back(false);
            }
        }
 
        while (std::getline(myfile, line)) {
            analyzeLine(line,beam,counter);
        }

        myfile.close();
    }

    std::cout << counter << std::endl;

    return 0;
}


void analyzeLine(std::string line, std::vector<bool> &beam, int32_t &counter) {

    for(int i = 0; i < line.length(); i++) {
        if(line[i] == '^' && beam.at(i)) {
            if(i > 0) {
                beam.at(i-1) = true;
            }
            if(i <line.length() - 1) {
                beam.at(i+1) = true;
            }
            beam.at(i) = false;
            counter++;
        }
    }
}
