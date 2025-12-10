#include <iostream>
#include <fstream>
#include <queue>
#include <map>

void readLine(std::string line,
            std::queue<std::pair<std::string, int32_t>> &configurations,
            std::map<std::string, int32_t> &checkedConfigurations,
            std::vector<std::vector<int32_t>> &buttons,
            std::string &destination);

int32_t calculateMinButtons(std::queue<std::pair<std::string, int32_t>> &configurations,
                            std::map<std::string, int32_t> &checkedConfigurations,
                            std::vector<std::vector<int32_t>> &buttons,
                            std::string &destination);

std::string findNewCode(std::string code, std::vector<int32_t> &button);

int main() {

    std::string line {};
    std::ifstream myfile ("example.txt");

    int32_t counter {};

    if(myfile.is_open()) {

        while(getline(myfile,line)) {
            std::queue<std::pair<std::string, int32_t>> configurations {};
            std::map<std::string, int32_t> savedConfigurations {};
            std::vector<std::vector<int32_t>> buttons {};
            std::string destination {};
            
            readLine(line, configurations, savedConfigurations, buttons, destination);


            counter += calculateMinButtons(configurations,savedConfigurations, buttons, destination);

        }

        myfile.close();
    }


    std:: cout << counter << std::endl;

    return 0;
}

void readLine(std::string line,
            std::queue<std::pair<std::string, int32_t>> &configurations,
            std::map<std::string, int32_t> &savedConfigurations,
            std::vector<std::vector<int32_t>> &buttons,
            std::string &destination) {
    
    std::string word {""};
    std::string start {""};

    bool readWord {false};
    bool readNum {false};
    std::vector<int32_t> button {};
    int32_t num {};

    for(int i = 0; i < line.length(); i++) {

        if(line[i] == ']') {
            destination = word;
            for(int i = 0; i < word.length(); i++) {
                start = start + '.';
            }
            configurations.push(std::pair<std::string,int32_t>(start,0));
            savedConfigurations.insert({start,0});
            readWord = false; 
        }

        if(line[i] == ')') {
            button.push_back(num);
            num = 0;
            buttons.push_back(button);
            readNum = false;
            button.clear();
        }


        

        if(readWord) {
            word = word + line[i];
        }

        if(readNum) {
            if(line[i] == ',') {
                button.push_back(num);
                num = 0;
            } else {
                num *= 10;
                num += (line[i] - 48);
            }
        }


        if(line[i] == '[') {
            readWord = true; 
        }

        if(line[i] == '(') {
            readNum = true;
        }
    }
}

int32_t calculateMinButtons(std::queue<std::pair<std::string, int32_t>> &configurations,
                            std::map<std::string, int32_t> &savedConfigurations,
                            std::vector<std::vector<int32_t>> &buttons,
                            std::string &destination) {
    
    while(!configurations.empty()) {
        std::string code {configurations.front().first};
        int32_t click {configurations.front().second};

        std::string newCode {""};

        for(int i = 0; i < buttons.size(); i++) {
            newCode = findNewCode(code, buttons[i]);
            if(newCode == destination) {
                return click + 1;
            }
            auto it = savedConfigurations.find(newCode); 
            if(it == savedConfigurations.end()) {
                
                savedConfigurations.insert({newCode,click+1});
                configurations.push(std::pair<std::string, int32_t>(newCode, click+1));
            } 
        }
        configurations.pop();



    }                            
    

    return 0;                         
}


std::string findNewCode(std::string code, std::vector<int32_t> &button) {

    std::string newCode = code;
    for(int i = 0; i < button.size(); i++) {
        if(newCode[button[i]] == '.') {
            newCode[button[i]] = '#';
        } else {
            newCode[button[i]] = '.';
        }
    }
    return newCode;
}
