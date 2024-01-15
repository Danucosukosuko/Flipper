#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <getopt.h>
#include <algorithm>

void printHelp() {
    std::cout << "DuckyWordListGenerator - v1.0\n"
              << "No arguments provided. Use -h to show available arguments\n";
}

void printHelp2() {
    std::cout << "-l					-> Numbers or letters to the wordlist\n"
              << "-w					-> Lenght of the line. Example: -w 5, aaaaa\n";
}

void generateCombinations(const std::string& letters, int width, std::ofstream& outFile) {
    std::string currentCombination(width, letters[0]);
    int lineCount = 0;

    do {
        for (int j = width - 1; j >= 0; --j) {
            std::string::const_iterator it = std::find(letters.begin(), letters.end(), currentCombination[j]);
            if (it != letters.end()) {
                ++it;
                if (it != letters.end()) {
                    currentCombination[j] = *it;
                    break;
                } else {
                    currentCombination[j] = letters[0];
                }
            }
        }

        ++lineCount;

        outFile << "STRING " << currentCombination << std::endl;
        outFile << "ENTER" << std::endl;
        outFile << "DELAY 500" << std::endl;

        std::cout << "Line: " << lineCount << "\r";
        std::cout.flush();
    } while (currentCombination != std::string(width, letters[0]));

    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    const char *optString = "hl:w:";
    int opt;

    std::string letters;
    int columnWidth = 0;

    while ((opt = getopt(argc, argv, optString)) != -1) {
        switch (opt) {
        case 'h':
            printHelp2();
            return 0;
        case 'l':
            letters = optarg;
            break;
        case 'w':
            columnWidth = std::atoi(optarg);
            break;
        default:
            printHelp();
            return 1;
        }
    }

    if (letters.empty() || columnWidth == 0) {
        printHelp();
        return 1;
    }

    std::sort(letters.begin(), letters.end());

    std::ofstream outFile("TOP.txt");

    if (!outFile.is_open()) {
        std::cerr << "Error - Failed to open TOP.txt" << std::endl;
        return 1;
    }

    outFile << "REM Wordlist created by DuckyList" << std::endl;

    generateCombinations(letters, columnWidth, outFile);

    outFile.close();

    return 0;
}


