#include <iostream>
#include <fstream>
#include <map>
#include <vector>

void readLine(std::string line, std::map<std::string, std::pair<std::vector<std::string>, int64_t>>  &preNeighbours);

int64_t countWays(std::map<std::string, std::pair<std::vector<std::string>, int64_t>>  &preNeighbours, std::string node);

int main() {

    std::string line {};
    std::ifstream myfile ("example.txt");

    std::map<std::string, std::pair<std::vector<std::string>, int64_t>>  preNeighbours {};

    if(myfile.is_open()) {
        while(getline(myfile,line)) {

            readLine(line, preNeighbours);

        }
        myfile.close();
    }

    auto it = preNeighbours.find("you");
    if(it != preNeighbours.end()) { 
    preNeighbours["you"].second = 1;
    }


    int64_t counter = countWays(preNeighbours, "out");

    std::cout << counter << std::endl;
    return 0;
}

void readLine(std::string line, std::map<std::string, std::pair<std::vector<std::string>, int64_t>>  &preNeighbours) {

    std::string neighbour {""};
    bool readNeighbour {true};
    std::string node {""};

    for(int i = 0; i < line.length(); i++) {

        if(!readNeighbour && line[i] != ' ') {
            node = node + line[i];
        }

        if(line[i] == ':') {
            readNeighbour = false;
        }

        if(readNeighbour) {
            neighbour = neighbour + line[i];
        }

        if(line[i] == ' ') {
            if(node != "") {
                auto it = preNeighbours.find(node);
                if(it != preNeighbours.end()) { 
                    preNeighbours[node].first.push_back(neighbour);    
                } else {
                    preNeighbours.insert({node, std::pair<std::vector<std::string>, int64_t>({neighbour},-1)});
                }

            }
            node = "";

        } 
    }

    auto it = preNeighbours.find(node);
    if(it != preNeighbours.end()) { 
        preNeighbours[node].first.push_back(neighbour);    
    } else {
        preNeighbours.insert({node, std::pair<std::vector<std::string>, int64_t>({neighbour},-1)});
    }

}

int64_t countWays(std::map<std::string, std::pair<std::vector<std::string>, int64_t>>  &preNeighbours, std::string node) {
    if(preNeighbours[node].second > -1) {
        return preNeighbours[node].second;
    }

    int64_t counter {0};

    for(int i = 0; i < preNeighbours[node].first.size(); i++) {
        counter += countWays(preNeighbours, preNeighbours[node].first[i]);
        
    }


    if(counter == 0) {
        preNeighbours[node].second = 0;
        return 0;
    } else {
        preNeighbours[node].second = counter;
        return counter;
    }

    
}
