#include "Tool/FileList.h"
#include <windows.h>
#include <iostream>
#include <cstring>
#include <regex>
#include "Entity/Map.h"

int main(const int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    if (argc >= 2 && (strcmp(argv[1], "-H") == 0 || strcmp(argv[1], "--help") == 0)) {
        std::cout << "选项：" << std::endl;
        std::cout << "  -P, --path <file>\t解析<file>文件夹" << std::endl;
        std::cout << "  -H, --help\t\t选项菜单" << std::endl;
        return 0;
    }
    if (argc != 3 || (strcmp(argv[1], "-P") != 0 && strcmp(argv[1], "--path") != 0)) {
        std::cout << "命令行参数错误！" << std::endl;
        std::cout << "选项：" << std::endl;
        std::cout << "  -P, --path <file>\t解析<file>文件夹" << std::endl;
        std::cout << "  -H, --help\t\t选项菜单" << std::endl;
        return 0;
    }

    const std::string filePath = argv[2];
    FileList FileList;
    FileList.initialFileList(filePath);

    Map map;
    if (!map.initialMap(FileList.getMapFiles()[0], FileList.getDemandFile())) {
        std::cerr<< "地图初始化失败" << std::endl;
        return -1;
    }
    map.findRoute();

    const std::regex pattern(R"([_\\](\d+)\.csv$)");
    std::smatch match;
    std::string out;

    if (std::regex_search(FileList.getMapFiles()[0], match, pattern)) {
        out = match[1];
        std::cout << out.substr(0, 2) + ":" + out.substr(2) + "\t";
    }
    map.printRoute();

    for (int i = 1; i < FileList.getMapFiles().size(); i++) {
        if (!map.updateMap(FileList.getMapFiles()[i])) {
            std::cerr << FileList.getMapFiles()[i] << "加载失败" << std::endl;
        }
        map.findRoute();
        if (std::regex_search(FileList.getMapFiles()[i], match, pattern)) {
            out = match[1];
            std::cout << out.substr(0, 2) + ":" + out.substr(2) + "\t";
        }
        map.printRoute();
    }
}
