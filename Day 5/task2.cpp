#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void addRange(std::string line, std::vector<std::pair<int64_t,int64_t>> &ranges);

void updateRange(std::pair<int64_t,int64_t> newRange, std::vector<std::pair<int64_t,int64_t>> &ranges, std::vector<std::pair<int64_t,int64_t>>::iterator it);

int main() {

    std::string line {};
    std::ifstream myfile ("example.txt");

    bool flagRanges {true};
    std::vector<std::pair<int64_t,int64_t>> ranges {};

    int64_t fresh {0};


    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            addRange(line, ranges);
        }
    }

    for(auto it = ranges.begin(); it != ranges.end(); it++) {
        fresh += ((it->second) - (it->first) + 1);
    }

    std::cout << fresh << std::endl;

    return 0;
}



void addRange(std::string line, std::vector<std::pair<int64_t,int64_t>> &ranges) {
    int64_t left {0};
    int64_t right {0};

    bool findBreak {false};
    bool updated {false};

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

    for(auto it = ranges.begin(); it != ranges.end(); it++) {
        if(left <= (it->second) && right >= (it->first)) {
            it->first = std::min(left,it->first);
            it->second = std::max(right,it->second);
            updateRange(std::pair<int64_t,int64_t>(it->first,it->second), ranges, it);
            updated = true;
        }
    }

    if(!updated) {
        ranges.push_back(std::pair<int64_t,int64_t>(left,right));
    } else {
        auto it = find(ranges.begin(), ranges.end(), std::pair<int64_t,int64_t>(0,0));
        while(it != ranges.end()) {
            ranges.erase(it);
            it = find(ranges.begin(), ranges.end(), std::pair<int64_t,int64_t>(0,0));
        }
    }
    
}

void updateRange(std::pair<int64_t,int64_t> newRange, std::vector<std::pair<int64_t,int64_t>> &ranges, std::vector<std::pair<int64_t,int64_t>>::iterator it) {
    for(auto iter = it + 1; iter != ranges.end(); iter++) {
        if(((newRange.first) <= (iter->second)) && ((newRange.second) >= (iter->first))) {
            it->first = 0;
            it->second = 0;
            iter->first = std::min(newRange.first,iter->first);
            iter->second = std::max(newRange.second,iter->second);
            updateRange(std::pair<int64_t,int64_t>(iter->first,iter->second), ranges, iter);

            return;
            
        }
    }
}


