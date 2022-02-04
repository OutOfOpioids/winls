#include <iostream>
#include <filesystem>
#include <direct.h>
#include <string>
#include <Windows.h>

using namespace std;
namespace fs = std::filesystem;

string file;

bool endsWith(string const& fullString, string const& ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    }
    else {
        return false;
    }
}

int main(int argc, char* argv[]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string path = fs::current_path().string();
    if (argc == 1) {
        for (const auto& entry : fs::directory_iterator(path)) {
            file = entry.path().string();
            file.erase(file.begin(), file.begin() + path.size() + 1);
            if (fs::is_directory(entry)) {
                SetConsoleTextAttribute(hConsole, 9);
                cout << file + "/" << endl;
            }
            else if (endsWith(file, ".exe")) {
                SetConsoleTextAttribute(hConsole, 12);
                cout << file << endl;
            }
            else {
                SetConsoleTextAttribute(hConsole, 15);
                cout << file << endl;
            }

        }
    }
    else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        cout << "Usage: ls [FILE]" << endl;
        cout << "List files in a directory" << endl;
        cout << "Source code: https://github.com/NotKronos/winls" << endl;
    }
    else if (strcmp(argv[1], "--recursive") == 0 || strcmp(argv[1], "-R") == 0) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        string path = fs::current_path().string();
        for (const auto& entry : fs::recursive_directory_iterator(path)) {
            file = entry.path().string();
            file.erase(file.begin(), file.begin() + path.size() + 1);
            if (fs::is_directory(entry)) {
                SetConsoleTextAttribute(hConsole, 9);
                cout << file + "/" << endl;
            }
            else if (endsWith(file, ".exe")) {
                SetConsoleTextAttribute(hConsole, 12);
                cout << file << endl;
            }
            else {
                SetConsoleTextAttribute(hConsole, 15);
                cout << file << endl;
            }

        }
    }
    SetConsoleTextAttribute(hConsole, 15);
}

