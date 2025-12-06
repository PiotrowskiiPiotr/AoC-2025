#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>



void readLine(std::string line, int64_t &counter, std::vector<int64_t> &sum, std::vector<int64_t> &product);

void readNumbers(std::string line, std::vector<int64_t> &sum, std::vector<int64_t> &product);

void readSign(std::string line, int64_t &counter, std::vector<int64_t> &sum, std::vector<int64_t> &product);

int main() {

    std::string line {};
    std::ifstream myfile ("example.txt");

    int64_t counter {};
    std::vector<int64_t> sum {};
    std::vector<int64_t> product{};


    if(myfile.is_open()) {
        while(getline(myfile,line)) {

           readLine(line,counter,sum,product);

        }
    }

    std::cout << counter << std::endl;

    return 0;
}

void readLine(std::string line, int64_t &counter, std::vector<int64_t> &sum, std::vector<int64_t> &product) {
    for(int i = 0 ; i < line.length(); i++) {
        if(line[i] >= 48 && line[i] <= 57) {
            readNumbers(line,sum,product);
            return;
        } else if(line[i] == '*' || line[i] == '+') {
            readSign(line,counter,sum,product);
            return;
        }

    }
}


void readNumbers(std::string line, std::vector<int64_t> &sum, std::vector<int64_t> &product) {
    
    int64_t num {0};
    int64_t index {0};

    
    for(int i = 0; i < line.length(); i++) {
        if(line[i] >= 48 && line[i] <= 57) {
            num *= 10;
            num += (line[i]-48);
        } else if(num != 0){
            if(index >= sum.size()) {
                sum.push_back(num);
            } else {
                sum[index] += num;
            }

            if(index >= product.size()) {
                product.push_back(num);
            } else {
                product[index] *= num;
            }
            num = 0;
            index++;
        }
    }
    if(num != 0){
        if(index >= sum.size()) {
            sum.push_back(num);
        } else {
            sum[index] += num;
        }
        if(index >= product.size()) {
            product.push_back(num);
        } else {
            product[index] *= num;
        }
        num = 0;
        index++;
    }
}

void readSign(std::string line, int64_t &counter, std::vector<int64_t> &sum, std::vector<int64_t> &product) {

    int64_t index {0};

    
    for(int i = 0; i < line.length(); i++) {
        if(line[i] == '*') {
            counter += product[index];
            index++;
        } else if(line[i] == '+'){ 
            counter += sum[index];
            index++;
        }
    }
}
