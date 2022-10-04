#include <iostream>
#include <filesystem>
#include <direct.h>
#include <string>
#include <Windows.h>

std::string file;

bool endsWith(std::string const& fullString, std::string const& ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    }
    else {
        return false;
    }
}

void listFiles(const auto& entry, const std::string& path, HANDLE hConsole) {
    file = entry.path().string();
    file.erase(file.begin(), file.begin() + path.size() + 1); // NOLINT(cppcoreguidelines-narrowing-conversions)
    if (std::filesystem::is_directory(entry)) {
        SetConsoleTextAttribute(hConsole, 9);
        std::cout << file + "/" << std::endl;
    }
    else if (endsWith(file, ".exe")) {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << file << std::endl;
    }
    else {
        SetConsoleTextAttribute(hConsole, 15);
        std::cout << file << std::endl;
    }}

int main(int argc, char* argv[]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string path = std::filesystem::current_path().string();

    if (argc == 1) {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            listFiles(entry, path, hConsole);
        }
        SetConsoleTextAttribute(hConsole, 15);
    }
    else {
        bool rec = false;
        bool help = false;
        for(int i = 1; i <= argc; i++)
        {
            if ((strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) && !help)  {
                help = true;
                std::cout << "Usage: ls [FILE]" << std::endl;
                std::cout << "List files in a directory" << std::endl;
                std::cout << "Source code: https://github.com/NotKronos/winls" << std::endl;
            }
            if ((strcmp(argv[i], "--recursive") == 0 || strcmp(argv[i], "-R") == 0) && !rec) {
                rec = true;
                for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
                        listFiles(entry, path, hConsole);
                }
                SetConsoleTextAttribute(hConsole, 15);
            }

        }
    }
}

