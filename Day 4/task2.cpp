#include <iostream>
#include <fstream>
#include <map>

void lineCheck(std::string line, int32_t &rolls, int32_t &allRolls,int32_t y_coord, std::map<std::pair<int32_t,int32_t>,int> &grid);

void updateGrid(int32_t &rolls, int32_t &allRolls, std::map<std::pair<int32_t,int32_t>,int> &grid, int32_t xMax, int32_t yMax);

int main() {

    std::string line;
    std::ifstream myfile("example.txt");

    int32_t y_coord {0};
    int32_t rollsAvailable {0};
    int32_t allRolls {0};
    int32_t lineLength {0};
    int32_t rollsRemoved {0};

    std::map<std::pair<int32_t,int32_t>,int> grid;


    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            lineCheck(line, rollsAvailable, allRolls, y_coord, grid);
            y_coord++;
            lineLength = line.length();
        }

        myfile.close();
    }

    for(int32_t i = 0; i < lineLength; i++) {
        if(grid[std::pair<int32_t,int32_t>(i,y_coord-1)] > 3) {
            rollsAvailable--;
        }
    }

    rollsRemoved += rollsAvailable;

    while(rollsAvailable != 0 && allRolls != 0) {
        updateGrid(rollsAvailable, allRolls, grid, lineLength, y_coord);
        rollsRemoved += rollsAvailable;
    }

    std::cout << rollsRemoved << std::endl;

    return 0;
}

void lineCheck(std::string line, int32_t &rolls, int32_t &allRolls, int32_t y_coord, std::map<std::pair<int32_t,int32_t>,int> &grid) {

    for(int32_t i = 0; i < line.length(); i++) {
        if(y_coord == 0) {

            if(line[i] == '.') {
                grid.insert({std::pair<int32_t,int32_t>(i,y_coord),-1});
            } else if (line[i] == '@') {
                rolls++;
                allRolls++;
                grid.insert({std::pair<int32_t,int32_t>(i,y_coord),0});
                if(i != 0 && grid[std::pair<int32_t,int32_t>(i-1,y_coord)] >= 0) {
                    grid[std::pair<int32_t,int32_t>(i-1,y_coord)]++;
                    grid[std::pair<int32_t,int32_t>(i,y_coord)]++;
                }
            } 
        }
        else {
            if(line[i] == '.') {
                grid.insert({std::pair<int32_t,int32_t>(i,y_coord),-1});
                if (i != 0 && grid[std::pair<int32_t,int32_t>(i-1,y_coord-1)] > 3) {
                    rolls--;
                }
                if ((i == line.length()-1) && grid[std::pair<int32_t,int32_t>(i,y_coord-1)] > 3) {
                    rolls--;
                }
            } else if (line[i] == '@') {
                rolls++;
                allRolls++;
                grid.insert({std::pair<int32_t,int32_t>(i,y_coord),0});
                if(i != 0 && grid[std::pair<int32_t,int32_t>(i-1,y_coord)] >= 0) {
                    grid[std::pair<int32_t,int32_t>(i-1,y_coord)]++;
                    grid[std::pair<int32_t,int32_t>(i,y_coord)]++;
                }
                if (i != 0 && grid[std::pair<int32_t,int32_t>(i-1,y_coord-1)] >= 0) {
                    grid[std::pair<int32_t,int32_t>(i-1,y_coord-1)]++;
                    grid[std::pair<int32_t,int32_t>(i,y_coord)]++;
                    if(grid[std::pair<int32_t,int32_t>(i-1,y_coord-1)] > 3) {
                        rolls--;
                    }
                }
                if ((i != line.length()-1) && grid[std::pair<int32_t,int32_t>(i+1,y_coord-1)] >= 0) {
                    grid[std::pair<int32_t,int32_t>(i+1,y_coord-1)]++;
                    grid[std::pair<int32_t,int32_t>(i,y_coord)]++;
                }
                if (grid[std::pair<int32_t,int32_t>(i,y_coord-1)] >= 0) {
                    grid[std::pair<int32_t,int32_t>(i,y_coord-1)]++;
                    grid[std::pair<int32_t,int32_t>(i,y_coord)]++;
                    if((i == line.length()-1) && grid[std::pair<int32_t,int32_t>(i,y_coord-1)] > 3) {
                        rolls--;
                    }
                }
            } 
        }
    }
}

void updateGrid(int32_t &rolls, int32_t &allRolls, std::map<std::pair<int32_t,int32_t>,int> &grid, int32_t xMax, int32_t yMax) {
    rolls = 0;
    for(int i = 0; i < yMax; i++) {
        for(int j = 0; j < xMax; j++) {
            if(grid[std::pair<int32_t,int32_t>(j,i)] <= 3 && grid[std::pair<int32_t,int32_t>(j,i)] >= 0) {
                allRolls--;
                grid[std::pair<int32_t,int32_t>(j,i)] = -1;
            }
        }
    }

    for(int i = 0; i < yMax; i++) {
        for(int j = 0; j < xMax; j++) {
            if(grid[std::pair<int32_t,int32_t>(j,i)] > 3) {
                grid[std::pair<int32_t,int32_t>(j,i)] = 0;
                if(i > 0) { 
                    if(j > 0 && grid[std::pair<int32_t,int32_t>(j-1,i-1)] >= 0) {
                        grid[std::pair<int32_t,int32_t>(j,i)]++;
                    }
                    if(j < xMax-1 && grid[std::pair<int32_t,int32_t>(j+1,i-1)] >= 0) {
                        grid[std::pair<int32_t,int32_t>(j,i)]++;
                    }
                    if(grid[std::pair<int32_t,int32_t>(j,i-1)] >= 0) {
                        grid[std::pair<int32_t,int32_t>(j,i)]++;
                    }
                }
                if(i < yMax - 1) { 
                    if(j > 0 && grid[std::pair<int32_t,int32_t>(j-1,i+1)] >= 0) {
                        grid[std::pair<int32_t,int32_t>(j,i)]++;
                    }
                    if(j < xMax-1 && grid[std::pair<int32_t,int32_t>(j+1,i+1)] >= 0) {
                        grid[std::pair<int32_t,int32_t>(j,i)]++;
                    }
                    if(grid[std::pair<int32_t,int32_t>(j,i+1)] >= 0) {
                        grid[std::pair<int32_t,int32_t>(j,i)]++;
                    }
                }
                if(j > 0 && grid[std::pair<int32_t,int32_t>(j-1,i)] >= 0) {
                    grid[std::pair<int32_t,int32_t>(j,i)]++;
                }
                if(j < xMax-1 && grid[std::pair<int32_t,int32_t>(j+1,i)] >= 0) {
                    grid[std::pair<int32_t,int32_t>(j,i)]++;
                }

                if(grid[std::pair<int32_t,int32_t>(j,i)] <= 3) {
                    rolls++;
                }
            }
        }
    }
}