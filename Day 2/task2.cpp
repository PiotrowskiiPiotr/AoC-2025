#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>

void sumInRange(int64_t rangeStart, int64_t rangeEnd, int64_t &sum);

bool checkNumber(int64_t number);

bool checkBlocks(int64_t number, int digits, int blockSize);


int main() {

    std::cout << "Hello, World!" << std::endl;

    std::string line;

    std::ifstream myfile ("example.txt");
    if(myfile.is_open()) {
        getline(myfile,line);

        myfile.close();
    }

    bool leftFlag {true};

    int64_t leftNumber {0};
    int64_t rightNumber {0};

    int64_t sum {0};

    for(auto const  c : line) {
        
        if(c == '-') {
            leftFlag = false;
            std::cout << leftNumber << std::endl;          
        } else if(c == ',') {
            leftFlag = true;
            std::cout << rightNumber << std::endl;

            sumInRange(leftNumber,rightNumber, sum);
            std::cout << sum << std::endl;
            leftNumber = 0;
            rightNumber = 0;
        } else if(leftFlag) {
            leftNumber *= 10;
            leftNumber += (c-48);
        } else {
            rightNumber *= 10;
            rightNumber += (c-48);
        }
    }

    std::cout << rightNumber << std::endl;
    sumInRange(leftNumber,rightNumber, sum);
    rightNumber = 0;

    std::cout << sum << std::endl;

    return 0;
}


void sumInRange(int64_t rangeStart, int64_t rangeEnd, int64_t &sum) {
    for(int64_t num = rangeStart; num <= rangeEnd; num++) {
        if(checkNumber(num)) {
            sum += num;
        }
    }
}

bool checkNumber(int64_t num) {
    int64_t temp = num;
    int digits {0};
    while(temp != 0) {
        temp /= 10;
        digits ++;
    }

    for(int i = 1; i <= digits/2; i++) {
        if((digits % i == 0) && checkBlocks(num,digits,i)) {
            return true;
        }
    }

    return false;
}

bool checkBlocks(int64_t number, int digits, int blockSize) {
    bool firstBlock {true};
    int64_t block {0};
    int divider = (int)pow(10,blockSize);
    while(number != 0) {
        if(firstBlock) {
            block = number % divider;
            firstBlock = false;       
        } else {
            if(number % divider != block) {
                return false;
            }
            
        }

        number /= divider;
    }
    return true;
}