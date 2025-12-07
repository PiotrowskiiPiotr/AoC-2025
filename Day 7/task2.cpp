#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>


void analyzeLine(std::string line, std::vector<int64_t> &beam);

int main() {

    std::string line;

    std::ifstream myfile ("example.txt");

    int64_t counter {0};

    std::vector<int64_t> beam {};

    if(myfile.is_open()) {

        std::getline(myfile, line);

        for(int i = 0; i < line.length(); i++) {
            if(line[i] == 'S') {
                beam.push_back(1);
            } else {
                beam.push_back(0);
            }
        }
 
        while (std::getline(myfile, line)) {
            analyzeLine(line,beam);
        }

        myfile.close();
    }

    for(auto it = beam.begin(); it != beam.end(); it++) {
        counter += *it;
    }

    std::cout << counter << std::endl;

    return 0;
}


void analyzeLine(std::string line, std::vector<int64_t> &beam) {

    for(int i = 0; i < line.length(); i++) {
        if(line[i] == '^' && beam.at(i) > 0) {
            if(i > 0) {
                beam.at(i-1) = beam.at(i-1) + beam.at(i);
            }
            if(i <line.length() - 1) {
                beam.at(i+1) = beam.at(i+1) + beam.at(i);
            }
            
            beam.at(i) = 0;
            
        }
    }
}
