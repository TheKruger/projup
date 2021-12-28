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

// Run the projup file in the path/ directory if it exists in the 'path' directory.
void RunProjup(string path, map<string, string>& variables) {
    string projup = path;

    // Get the current dircetory to restore it later.
    string current_dir = fs::current_path().string();

    // if the projup not endswith / then add it.
    if (projup.back() != '/') {
        projup += "/";
    }

    projup += "projup";

    if (fs::exists(projup)) {

        // Replace the variables in the projup file.
        string content = ReadFile(projup);
        for (const auto& var : variables) {
            regex r("@\\b" + var.first + "\\b");
            content = regex_replace(content, r, var.second);
        }
        WriteFile(projup, content);

        // Make the file executable.
        system(string("chmod +x " + projup).c_str());

        // Change the directory to the path/ directory.
        fs::current_path(path);

        // Execute the projup file.
        system("./projup");

        // Remove the projup file.
        fs::remove("./projup");

        // Change the directory back to the current directory.
        fs::current_path(current_dir);
    }
}