#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <map>



void readLine(std::string line, int64_t &counter, std::map<std::pair<int64_t,int64_t>, int64_t> &nums);

void readNumbers(std::string line, std::map<std::pair<int64_t,int64_t>, int64_t> &nums);

void readSign(std::string line, int64_t &counter, std::map<std::pair<int64_t,int64_t>, int64_t> &nums);

int main() {

    std::string line {};
    std::ifstream myfile ("example.txt");

    int64_t counter {};
    std::map<std::pair<int64_t,int64_t>, int64_t> nums {};



    if(myfile.is_open()) {
        while(getline(myfile,line)) {

           readLine(line,counter,nums);

        }
    }

    std::cout << counter << std::endl;

    return 0;
}

void readLine(std::string line, int64_t &counter, std::map<std::pair<int64_t,int64_t>, int64_t> &nums) {
    for(int i = 0 ; i < line.length(); i++) {
        if(line[i] >= 48 && line[i] <= 57) {
            readNumbers(line,nums);
            return;
        } else if(line[i] == '*' || line[i] == '+') {
            readSign(line,counter,nums);
            return;
        }

    }
}


void readNumbers(std::string line, std::map<std::pair<int64_t,int64_t>, int64_t> &nums) {
    
    bool isNum {false};
    int64_t index {0};

    
    for(int i = 0; i < line.length(); i++) {
        if(line[i] >= 48 && line[i] <= 57) {
            if(nums.find(std::pair<int64_t,int64_t>(index,i)) == nums.end()) {
                nums[std::pair<int64_t,int64_t>(index,i)] = (line[i] - 48);
            } else {
                nums[std::pair<int64_t,int64_t>(index,i)] *= 10;
                nums[std::pair<int64_t,int64_t>(index,i)] += (line[i] - 48);
            }
            isNum = true;
        } else if(isNum){

            isNum = false;
            index++;
        }

    }
}

void readSign(std::string line, int64_t &counter, std::map<std::pair<int64_t,int64_t>, int64_t> &nums) {

    int64_t index {-1};

    bool isMulti {false};

    int64_t result {0};
    
    for(int i = 0; i < line.length(); i++) {
        if(line[i] == '*') {

            counter = counter + result;
            result = 1;
            isMulti = true;
            index++;
        } else if(line[i] == '+'){ 

            counter = counter + result;
            result = 0;
            isMulti = false;
            index++;
        } 

        if(isMulti) {

            if(nums[std::pair<int64_t,int64_t>(index,i)] != 0) {
                result *= nums[std::pair<int64_t,int64_t>(index,i)];
            }

        } else{

            result += nums[std::pair<int64_t,int64_t>(index,i)];

        }


    }

    counter += result;
}
