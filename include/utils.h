#pragma once

#include <map>
#include <regex>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

#define TEMPLATE_DIR "/etc/projup/templates/"

using namespace std;

string Replace(string str, string from, string to);
bool IsDirectoryExists(string dir);
bool IsTemplateExists(string temp);
string ReadFile(string file);
void WriteFile(string file, string content);
void CollectVariables(map<string, string>& variables, int argc, char* argv[]);