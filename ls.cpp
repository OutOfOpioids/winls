#include <iostream>
#include <filesystem>
#include <direct.h>
#include <string>
#include <Windows.h>

using namespace std;
namespace fs = std::filesystem;

string wd;
string file;

bool endsWith(string const& fullString, string const& ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    }
    else {
        return false;
    }
}

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string path = fs::current_path().string();
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
