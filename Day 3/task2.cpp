#include <iostream>
#include <fstream>
#include <array>


int64_t getLineMaxJoltage(std::string line);

void updateJoltage(char value, int32_t joltage[], int index);

int main() {

    std::string line;
    std::ifstream myfile ("example.txt");
    int64_t joltageSum {0};

    if(myfile.is_open()) {
        while (std::getline(myfile, line)) {
            joltageSum += getLineMaxJoltage(line);
            
        }

        myfile.close();
    }

    std::cout << joltageSum << std::endl;

    return 0;
}


int64_t getLineMaxJoltage(std::string line) {
    int64_t sum {0};
    int32_t joltage[12] {};
    int counter {0};
    for(auto it = line.rbegin();  it != line.rend(); ++it) {
        if(counter < 12) {
            joltage[11-counter] = *it;
            counter++;
        } else {
            if(*it >= joltage[0]) {
                updateJoltage(*it, joltage, 0);
            }

        }
        
    } 

    for(int i = 0; i <= 11; i++) {
        sum *= 10;
        sum += (joltage[i] -48);
    }

    return sum;
} 

void updateJoltage(char value, int32_t joltage[], int index) {
    if(index == 11 || (joltage[index+1] > joltage[index])) {
        joltage[index] = value;
    } else {
        updateJoltage(joltage[index], joltage, index+1);
        joltage[index] = value;
    }
}

