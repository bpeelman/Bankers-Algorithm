// Brody Peelman
// 11/20/2024
// bankers-algorithm.cpp
// 
// Takes .txt input of tables

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// # of rows in tables
const int processes = 5;
// # of columns in tables
const int resources = 3;
// Char that splits ints in .txt tables
const char toRemoveFromString = '|';


// str == string of line in table
// row == row in table
// vec == table
void fillRow(std::string str, int row, std::vector<std::vector<int>>& vec) {

    // Removes edges:  [0|1|0] --> 0|1|0
    str = str.substr(1, str.length() - 2);

    std::stringstream ss(str);
    std::string temp;

    vec[row].clear();

    // Splits string at char specified and inserts the int into the index of the table
    while (getline(ss, temp, toRemoveFromString)) {
        vec[row].push_back(std::stoi(temp));
    }
}



int main(int argc, char*argv[]) {

    //Exits if not two arguments on cl
    if (argc != 2) {
        std::cerr << "Too few/many arguments." << std::endl;
        exit(1);
    }

    std::ifstream data(argv[1]);
    if (!data.is_open()) {
        std::cerr << "File not opened." << std::endl;
        exit(1);
    }


    // Reads in tables from .txt, outputs them
    std::string text;
    std::vector<std::string> lines;
    while(getline(data, text)) { lines.push_back(text); std::cout << text << std::endl; }
    data.close();
    // Spaces
    for (int endl = 0; endl < 2; ++endl) { std::cout << std::endl; }


    std::vector<std::vector<int>> allocation(processes, std::vector<int>(resources));
    for (int i = 0; i < processes; ++i) fillRow(lines[i+1], i, allocation);

    std::vector<std::vector<int>> max(processes, std::vector<int>(resources));
    for (int i = 0; i < processes; ++i) fillRow(lines[i+7], i, max);

    std::vector<std::vector<int>> available(1, std::vector<int>(resources));
    fillRow(lines[13], 0, available);


    // Need = Max - Allocation
    std::vector<std::vector<int>> need(processes, std::vector<int>(resources));
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) need[i][j] = max[i][j] - allocation[i][j];
    }
    

    // Specifies which process receives needed resources and finishes
    std::vector<bool> finished = {false, false, false, false, false};
    // Receives process num in order of their completion
    std::vector<int> safeSequence = {0, 0, 0, 0, 0};
    int index = 0;

    int loop = 0;
    while (loop < processes) {
        // p == current process num
        for (int p = 0; p < processes; ++p) {
            if (finished[p] == false) {
                bool works = true;
                for (int r = 0; r < resources; ++r) {
                    if (need[p][r] > available[0][r]) {
                        works = false;
                        break;
                    }
                }
                // if the process can be satisfied
                if (works) {
                    finished[p] = true;
                    for (int a = 0; a < resources; ++a) {
                        available[0][a] += allocation[p][a];
                    }
                    safeSequence[index++] = p;
                }
            }
        }
        ++loop;
    }

    // Checks whether each process was completed, if one wasn't the system is not safe
    bool safe = true;
    for (bool b : finished) {
        if (!b) {
            safe = false;
            break;
        }
    }

    if (safe) {
        std::cout << "There exists a safe sequence of: " << std::endl;
        for (int s = 0; s < index; ++s) {
            std::cout << "P" << safeSequence[s];
            if (s < index-1) std::cout << " , ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No safe sequence exists." << std::endl;
    }


}
