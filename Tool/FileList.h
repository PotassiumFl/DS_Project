#ifndef DS_PJ_FILELIST_H
#define DS_PJ_FILELIST_H

#include <vector>
#include <string>

class FileList {
public:
    FileList();

    bool initialFileList(const std::string &filePath);

    std::vector<std::string> getMapFiles();

    std::string getDemandFile();

private:
    std::vector<std::string> mapFiles;
    std::string demandFile;
};

void sortByTimeRegex(std::vector<std::string> &list);



#endif //DS_PJ_FILELIST_H