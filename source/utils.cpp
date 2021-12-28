#include <utils.h>

#include <map>
#include <regex>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

string Replace(string str, string from, string to) {
    regex r("\\$\\b" + from + "\\b");
    return regex_replace(str, r, to);
}

// Check if directory exists.
bool IsDirectoryExists(string dir) {
    return fs::exists(dir);
}

// Check if template exists.
bool IsTemplateExists(string temp) {

    // Check if 'temp' folder is in the templates directory.
    // If not, return false.
    if (!IsDirectoryExists(TEMPLATE_DIR + temp)) {
        return false;
    }
    return true;
}

string ReadFile(string file) {
    ifstream in(file);
    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    return content;
}

void WriteFile(string file, string content) {
    ofstream out(file);
    out << content;
}

void CollectVariables(map<string, string>& variables, int argc, char* argv[]) {
    for (int i = 3; i < argc; i++) {
        string var = argv[i];

        if (var.find("=") == string::npos) {
            continue;
        }

        size_t pos = var.find("=");
        if (pos != string::npos) {
            string key = var.substr(0, pos);
            string value = var.substr(pos + 1);
            variables[key] = value;
        }
    }
}