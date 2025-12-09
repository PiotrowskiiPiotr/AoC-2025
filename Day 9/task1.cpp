#include <iostream>
#include <fstream>
#include <vector>



void readPoint(std::string line, std::vector<std::pair<int64_t,int64_t>> &points, int64_t &result);

int main() {

    int64_t result {};

    std::string line {};
    std::ifstream myfile ("example.txt");

    std::vector<std::pair<int64_t,int64_t>> points {};

    if(myfile.is_open()) {
        while(getline(myfile,line)) {

            readPoint(line,points,result);

        }
        myfile.close();
    }

    std::cout << result << std::endl;

    return 0;
}


void readPoint(std::string line, std::vector<std::pair<int64_t,int64_t>> &points, int64_t &result) {
    int64_t x {};
    int64_t y {};

    bool firstNum {true};

    for(int i = 0; i < line.length(); i++) {
        if(firstNum) {
            if(line[i] == ',') {
                firstNum = false;
            }
            else {
                x *= 10;
                x += (line[i] - 48);
            }
        } else {
            if(line[i] >= 48 && line[i] <= 57) {
                y *= 10;
                y += (line[i] - 48);
            }
        }
    }

    for(auto it = points.begin(); it != points.end(); it++) {
        int64_t xLength {};
        int64_t yLength {};
        if((it->first) < x) {
            xLength = x - (it->first) + 1;
        } else {
            xLength = (it->first) - x + 1;
        }
        if((it->second) < y) {
            yLength = y - (it->second) + 1;
        } else {
            yLength = (it->second) - y + 1;
        }
        if(xLength*yLength > result) {
            result = xLength * yLength;
        }
        
    }

    points.push_back(std::pair<int64_t,int64_t>(x,y));
}
