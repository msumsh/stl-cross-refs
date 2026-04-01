#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <cctype>

namespace functions {
    void getWords(const std::string& string, const int& line, std::unordered_map<std::string, std::set<int>>& map) {
        size_t strLength = string.length();
        if (strLength == 0) {
            return;
        }
        std::string word;
        for (size_t i = 0; i < strLength; i++) {
            if (isalpha(string[i]) || (string[i] == '-' && isalpha(string[i + 1])) || (string[i] == '\'' && isalpha(string[i + 1]))) {
                word += tolower(string[i]);
            }
            else {
                if (!word.empty()) {
                    map[word].insert(line);
                }
                word.clear();
            }
        }
    }
}

namespace command {
    void help() {
        std::cout << "======COMMAND LIST=====\n";
        std::cout << "====Get a command list: ====\n";
        std::cout << "    -HELP\n";
        std::cout << "====Get a cross-reference map: ====\n";
        std::cout << "    -MAP\n";
        std::cout << "====Get a word cross-reference map: ====\n";
        std::cout << "    -REFS <word>\n";
    }
    void getCrossRefMap(std::unordered_map<std::string, std::set<int>>& map) {
        if (map.empty()) {
            throw std::runtime_error("ERROR: empty map");
        }
        std::vector<std::string> sortedKeys;
        for (const auto& pair : map) {
            sortedKeys.push_back(pair.first);
        }
        std::sort(sortedKeys.begin(), sortedKeys.end());
        for (const auto& key : sortedKeys) {
            std::cout << key << ": ";
            std::copy(map[key].cbegin(), map[key].cend(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
    }
    void getWordCrossRef(std::unordered_map<std::string, std::set<int>>& map) {
        std::string word;
        std::cin >> word;
        if (map.empty()) {
            throw std::runtime_error("ERROR: empty map");
        }
        if (map.find(word) != map.end()) {
            std::cout << word << ": ";
            std::copy(map[word].cbegin(), map[word].cend(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
        else {
            throw std::runtime_error("ERROR: not found");
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR: Incorrect usage\n";
        return 1;
    }
    std::string fileName = argv[1];
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "ERROR: File is not open\n";
        return 1;
    }

    if (!file)
    {
        std::cerr << "File not found!" << std::endl;
        return 1;
    }

    std::unordered_map<std::string, std::set<int>> crossRefMap;
    std::cout << "==========Reading file...==========\n";
    int num = 0;
    while (!file.eof()) {
        std::string line;
        if (std::getline(file, line)) {
            ++num;
            std::cout << num << " " << line << std::endl;
            functions::getWords(line, num, crossRefMap);
        }
        else {
            file.clear();
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::map<std::string, std::function<void(std::unordered_map<std::string, std::set<int>> &)>> commandMap =
    {
        {"MAP", command::getCrossRefMap},
        {"REFS", command::getWordCrossRef}
    };

    std::cout << "==========Commands==========\n";
    while (!std::cin.eof())
    {
        std::string cmd;

        std::cin >> cmd;

        try
        {
            if (cmd == "HELP") {
                command::help();
            }
            else if (commandMap.find(cmd) != commandMap.end()) {
                auto it = commandMap.find(cmd);
                if (it != commandMap.end())
                    it->second(crossRefMap);
            }
            else {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}