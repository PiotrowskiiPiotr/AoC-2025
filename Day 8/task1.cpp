#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>

struct Node {
        int64_t x;
        int64_t y;
        int64_t z;
        int64_t group;
    };

void writeLine(std::string line, std::map<int64_t, std::vector<int64_t>> &groups, std::vector<Node> &nodes);

void listClosestConnections(std::vector<Node> &nodes, std::vector<std::pair<double,std::pair<int64_t,int64_t>>> &connections, int32_t number);

void findBiggestNumber(double value, std::vector<std::pair<double,std::pair<int64_t,int64_t>>> &connections, int64_t first, int64_t second);

int main() {


    std::string line {};

    std::ifstream myfile ("example.txt");

    std::map<int64_t, std::vector<int64_t>> groups {};
    std::vector<Node> nodes {};

    if(myfile.is_open()) {
        while(getline(myfile,line)) {

            writeLine(line,groups,nodes);

        }

        myfile.close();
    }

    std::vector<std::pair<double,std::pair<int64_t,int64_t>>> connections {};


    listClosestConnections(nodes,connections,10);

    // --- Printowanie --- //
/*
    for(auto it = nodes.begin(); it != nodes.end(); it++) {
        std::cout << it->x << " " << it->y << " " << it->z << " " << it->group << std::endl;
    }

    for(auto g : groups) {
        std::cout << g.first << "      " ;
        for(auto it = g.second.begin(); it != g.second.end(); it++) {
            std::cout << *it;
        }
        std::cout << std:: endl;
    }
*/
    for(auto it = connections.begin(); it != connections.end(); it++) {
        std::cout << it->first << " " << it->second.first << " " << it->second.second << std::endl;
    }

    return 0;
}

void writeLine(std::string line, std::map<int64_t, std::vector<int64_t>> &groups, std::vector<Node> &nodes) {
    
    int64_t x {};
    int64_t y {};
    int64_t z {};

    int num {0};

    for(int i = 0; i < line.length(); i++) {
        if(num == 0) {
            if(line[i] == ',') {
                num++;
            } else {
                x *= 10;
                x += (line[i] - 48);
            }
        } else if (num == 1) {
            if(line[i] == ',') {
                num++;
            } else {
                y *= 10;
                y += (line[i] - 48);
            }
        } else if (num == 2 && line[i] >= 48 && line[i] <= 57) {
            z *= 10;
            z += (line[i] - 48);
        } 
    }

    int64_t nodeSize {(int64_t)nodes.size()};

    struct Node node = {x ,y,z,nodeSize};

    nodes.push_back(node);

    groups.insert({nodeSize, std::vector<int64_t>({nodeSize})});
}

void listClosestConnections(std::vector<Node> &nodes, std::vector<std::pair<double,std::pair<int64_t,int64_t>>> &connections, int32_t number) {

    for(int32_t i = 0; i < number; i++) {
        connections.push_back(std::make_pair(0,std::pair<int64_t,int64_t>(0,0)));
    }

    for(int32_t i = 0; i < nodes.size(); i++) {
        for(int32_t j = i + 1; j < nodes.size(); j++) {
            int32_t index = -1;

            double value = sqrt( (double)pow(nodes[i].x - nodes[j].x,2) + (double)pow(nodes[i].y - nodes[j].y,2) + (double)pow(nodes[i].z - nodes[j].z,2));
            findBiggestNumber(value,connections,i,j);

        }
    }
}

void findBiggestNumber(double value, std::vector<std::pair<double,std::pair<int64_t,int64_t>>> &connections, int64_t first, int64_t second) {
    for(int32_t i = connections.size() - 1; i >= 0; i --) {
        if(value < connections[i].first) {
            return;
        } else {
            if(i == (connections.size() - 1)) {
                connections.at(i) = std::make_pair(value,std::pair<int64_t,int64_t>(first,second));
            } else {
                connections.at(i + 1) = connections.at(i);
                connections.at(i) = std::make_pair(value,std::pair<int64_t,int64_t>(first,second));
            }
        }
    }
}
