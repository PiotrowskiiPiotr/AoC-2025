#include <iostream>
#include <fstream>
#include <vector>

void addRange(std::string line, std::vector<std::pair<int64_t,int64_t>> &ranges);

bool isFresh(std::string line, std::vector<std::pair<int64_t,int64_t>> ranges);

int main() {

    std::string line {};
    std::ifstream myfile ("example.txt");

    bool flagRanges {true};
    std::vector<std::pair<int64_t,int64_t>> ranges {};

    int32_t fresh {0};


    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            if(line == "") {
                flagRanges = false;
                continue;
            }
            if(flagRanges) {
                addRange(line, ranges);
            } else if(isFresh(line,ranges)) {
                fresh++;
            }
        }
    }

    std::cout << fresh << std::endl;

    return 0;
}



void addRange(std::string line, std::vector<std::pair<int64_t,int64_t>> &ranges) {
    int64_t left {0};
    int64_t right {0};

    bool findBreak {false};

    for(int i = 0; i < line.length(); i++) {
        if(line[i] == '-') {
            findBreak = true;
            continue;
        } 
        if(!findBreak) {
            left *= 10;
            left += (line[i] - 48);
        } else {
            right *= 10;
            right += (line[i]-48);
        }
    }

    ranges.push_back(std::pair<int64_t,int64_t>(left,right));
}


bool isFresh(std::string line, std::vector<std::pair<int64_t,int64_t>> ranges) {

    int64_t id {0};

    for(int i = 0; i < line.length(); i++) {
        id *= 10;
        id += (line[i]-48);
    }

    for(auto it = ranges.begin(); it != ranges.end(); it++) {
        if(id >= (it->first) && id <= (it->second)) {
            
            return true;
        }
    }

    return false;
}

