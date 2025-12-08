#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>
#include <cstdint>
#include <string>
#include <algorithm>

struct Node {
        int64_t x;
        int64_t y;
        int64_t z;
        int64_t group;
    };

void writeLine(std::string line, std::map<int64_t, std::vector<int64_t>> &groups, std::vector<Node> &nodes);

void listClosestConnections(std::vector<Node> &nodes, std::vector<std::pair<double,std::pair<int64_t,int64_t>>> &connections, int32_t number);

int64_t modifyGroups(std::vector<std::pair<double,std::pair<int64_t,int64_t>>> connections,std::map<int64_t, std::vector<int64_t>> &groups, std::vector<Node> &nodes);

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

    listClosestConnections(nodes,connections,(nodes.size() * (nodes.size() - 1) )/2);

    std::cout << modifyGroups(connections,groups,nodes);  

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

    for(int32_t i = 0; i < nodes.size(); i++) {
        for(int32_t j = i + 1; j < nodes.size(); j++) {

            double value = sqrt( (double)pow(nodes[i].x - nodes[j].x,2) + (double)pow(nodes[i].y - nodes[j].y,2) + (double)pow(nodes[i].z - nodes[j].z,2));

            connections.push_back(std::make_pair(value,std::pair<int64_t, int64_t>(i,j)));

        }
    }

    std::sort(connections.begin(), connections.end());
}

int64_t modifyGroups(std::vector<std::pair<double,std::pair<int64_t,int64_t>>> connections,std::map<int64_t, std::vector<int64_t>> &groups, std::vector<Node> &nodes) {
    int64_t lastFirst {};
    int64_t lastSecond {};
    for(auto it = connections.begin(); it != connections.end(); it++) {
        if(nodes[it->second.second].group != nodes[it->second.first].group) {
            lastFirst = it->second.first;
            lastSecond = it->second.second;
            int64_t index = nodes[it->second.second].group;
            for(auto iter = groups[index].begin(); iter != groups[index].end(); iter++) {
                groups.at(nodes[it->second.first].group).push_back(*iter);
            }

            for(auto iter = groups[index].begin(); iter != groups[index].end(); iter++) {
                    nodes[*iter].group = nodes[it->second.first].group;
            }
            groups.erase(index);
        }
    }

    return nodes[lastFirst].x * nodes[lastSecond].x;
}

