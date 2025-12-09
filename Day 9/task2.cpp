#include <iostream>
#include <fstream>
#include <vector>



void readPoint(std::string line, std::vector<std::pair<int64_t,int64_t>> &points);

void findLargestArea(std::vector<std::pair<int64_t,int64_t>> points,int64_t &result);

bool canBeRectangle(std::vector<std::pair<int64_t,int64_t>> points, int one, int two);

int main() {

    int64_t result {};

    std::string line {};
    std::ifstream myfile ("example.txt");

    std::vector<std::pair<int64_t,int64_t>> points {};

    if(myfile.is_open()) {
        while(getline(myfile,line)) {

            readPoint(line,points);

        }
        myfile.close();
    }

    findLargestArea(points, result);

    std::cout << result << std::endl;

    return 0;
}


void readPoint(std::string line, std::vector<std::pair<int64_t,int64_t>> &points) {
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

    points.push_back(std::pair<int64_t,int64_t>(x,y));
}

void findLargestArea(std::vector<std::pair<int64_t,int64_t>> points,int64_t &result) {

    for(int i = 0; i < points.size(); i++) {
        for(int j = i; j < points.size(); j++) {

            int64_t xLength {};
            int64_t yLength {};
            if((points[i].first) < points[j].first) {
                xLength = points[j].first - points[i].first + 1;
            } else {
                xLength = points[i].first - points[j].first + 1;
            }
            if((points[i].second) < points[j].second) {
                yLength = points[j].second - points[i].second + 1;
            } else {
                yLength = points[i].second - points[j].second + 1;
            }
            if(xLength*yLength > result && canBeRectangle(points,i,j)) {
                result = xLength * yLength;
            }
        }
    }
   
}

bool canBeRectangle(std::vector<std::pair<int64_t,int64_t>> points, int one, int two) {
    for(int i = 0; i < points.size(); i++) {
        if(i == 0) {
            if((points[i].first == points[points.size()-1].first) && 
                (points[i].first < std::max(points[one].first, points[two].first) &&
                (points[i].first > std::min(points[one].first, points[two].first)))) {

                if(std::max(points[i].second, points[points.size()-1].second) > std::min(points[one].second,points[two].second) &&
                std::min(points[i].second, points[points.size()-1].second) <  std::max(points[one].second,points[two].second)) {
                    return false;
                }         
            }

            if((points[i].second == points[points.size()-1].second) && 
                (points[i].second < std::max(points[one].second, points[two].second) &&
                (points[i].second > std::min(points[one].second, points[two].second)))) {

                if(std::max(points[i].first, points[points.size()-1].first) > std::min(points[one].first,points[two].first) &&
                std::min(points[i].first, points[points.size()-1].first) <  std::max(points[one].second,points[two].first)) {
                    return false;
                }         
            }
        } else {
            if((points[i].first == points[i-1].first) && 
                (points[i].first < std::max(points[one].first, points[two].first) &&
                (points[i].first > std::min(points[one].first, points[two].first)))) {

                if(std::max(points[i].second, points[i-1].second) > std::min(points[one].second,points[two].second) &&
                std::min(points[i].second, points[i-1].second) <  std::max(points[one].second,points[two].second)) {
                    return false;
                }         
            }

            if((points[i].second == points[i-1].second) && 
                (points[i].second < std::max(points[one].second, points[two].second) &&
                (points[i].second > std::min(points[one].second, points[two].second)))) {

                if(std::max(points[i].first, points[i-1].first) > std::min(points[one].first,points[two].first) &&
                std::min(points[i].first, points[i-1].first) <  std::max(points[one].second,points[two].first)) {
                    return false;
                }         
            }
        }
    }
    return true;
}

