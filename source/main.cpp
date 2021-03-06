#include <utils.h>

#define VERSION "v1.0.0"

int main(int argc, char* argv[])
{
    bool verbose = false;

    for (int i = 0; i < argc; i++)
    {
        string arg = argv[i];
        if (arg == "--version" || arg == "-V")
        {
            cout << "projup version: " << VERSION << endl;
            return 0;
        }
        else if (arg == "--help" || arg == "-h")
        {
            cout << "Usage: " << argv[0] << " <path> <template> [VARIABLES]" << endl;
            cout << "Options:" << endl;
            cout << "  --version, -V  Print version and exit." << endl;
            cout << "  --help, -h     Display this help message and exit." << endl;
            cout << "  --verbose, -v  Increase the verbosity level." << endl;
            return 0;
        }
        else if (arg == "--verbose" || arg == "-v")
        {
            verbose = true;
        }
    }

    if (argc < 3)
    {
        cout << "Usage: " << argv[0] << " <path> <template> [VARIABLES]" << endl;
        return 1;
    }

    // In this context the 'temp' is not the short of temporary,
    // It's the short of template.
    string path = argv[1];
    string temp = argv[2];

    // Check if template file exists
    if (!IsTemplateExists(temp))
    {
        cout << "Template does not exist: " << temp << endl;
        return 1;
    }

    // Built-in variables
    map<string, string> variables = {
        {"NAME", path},
        {"TEMPLATE", temp}
    };

    // Collect variables
    CollectVariables(variables, argc, argv);

    // Create directory if it does not exist
    if (!IsDirectoryExists(path))
        fs::create_directory(path);

    // Copy the files from the tempalte/<template> directory to the new directory.
    if (verbose)
        std::cout << "Copying files..." << std::endl;
    const auto CopyOptions = fs::copy_options::recursive | fs::copy_options::update_existing | fs::copy_options::overwrite_existing;
    fs::copy(TEMPLATE_DIR + temp, path, CopyOptions);

    // Looping through the files in the new directory including subdirectories
    // and replace the variables with the values from the 'variables' map.
    if (verbose)
        std::cout << "Replacing variables..." << std::endl;
    for (const auto& entry : fs::recursive_directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            // If the file is the projup file, skip it.
            if (entry.path().filename() == "projup")
                continue;

            string content = ReadFile(entry.path().string());

            for (const auto& var : variables)
            {
                content = Replace(content, var.first, var.second);
            }
            WriteFile(entry.path().string(), content);
        }
    }

    // Run projup file if it exists in the directory.
    if (verbose)
        std::cout << "Running projup file..." << std::endl;
    RunProjup(path, variables);

    if (verbose)
        std::cout << "Project created successfully." << std::endl;

    return 0;
}