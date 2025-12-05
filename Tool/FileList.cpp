#include "FileList.h"
#include <filesystem>
#include <iostream>
#include <regex>

FileList::FileList() {
    this->mapFiles = std::vector<std::string>();
    this->demandFile = std::string();
}

bool FileList::initialFileList(const std::string &filePath) {
    if (!std::filesystem::exists(filePath)) {
        std::cout << filePath << "不存在！" << std::endl;
        return false;
    }
    for (const auto &entry: std::filesystem::directory_iterator(filePath)) {
        if (entry.path().extension() == ".csv")
            this->mapFiles.push_back(entry.path().string());
        else if (entry.path().extension() == ".txt")
            this->demandFile = entry.path().string();
    }
    sortByTimeRegex(this->mapFiles);
    return true;
}

void sortByTimeRegex(std::vector<std::string> &list) {
    std::regex pattern(R"([_\\](\d+)\.csv$)");

    std::sort(list.begin(), list.end(), [&pattern](const std::string &a, const std::string &b) {
        if (std::smatch matchA, matchB; std::regex_search(a, matchA, pattern) && std::regex_search(b, matchB, pattern)) {
            // 提取时间数字并比较
            const int timeA = std::stoi(matchA[1].str());
            const int timeB = std::stoi(matchB[1].str());
            return timeA < timeB;
        }

        // 如果不符合格式，按原始字符串排序
        return a < b;
    });
}

std::vector<std::string> FileList::getMapFiles() {
    return this->mapFiles;
}

std::string FileList::getDemandFile() {
    return this->demandFile;
}