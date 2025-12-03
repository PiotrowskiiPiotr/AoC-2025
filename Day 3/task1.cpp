#include <iostream>
#include <fstream>


int32_t getLineMaxJoltage(std::string line);

int main() {

    std::string line;
    std::ifstream myfile ("example.txt");
    int32_t joltageSum {0};

    if(myfile.is_open()) {
        while (std::getline(myfile, line)) {
                joltageSum += getLineMaxJoltage(line);
            
        }

        myfile.close();
    }

    std::cout << joltageSum << std::endl;

    return 0;
}


int32_t getLineMaxJoltage(std::string line) {
    int firstNum {0};
    int secondNum {0};
    int firstTemp {0};
    int secondTemp {0};

    for(auto c : line) {
        if(c > firstNum) {
            firstTemp = firstNum;
            if(c > secondNum) {
                secondTemp = c;
            } else {
                secondTemp = secondNum;
            }
            
            firstNum = c;
            secondNum = 0;
        } else if(c > secondNum) {
            secondNum = c;
        }
    } 

    if(secondNum == 0) {
        return (firstTemp-48)*10 + (secondTemp -48);
    } else {
        return (firstNum-48)*10 + (secondNum -48);
    }
} 