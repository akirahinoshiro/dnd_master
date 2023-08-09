#pragma once
#include <string>

class Map
{
  public:
    Map(std::string mapFile, std::string mapFolder, std::string mapFileAbs);
    ~Map();
    std::string mapFileStr;
    std::string mapFolderStr;
    std::string mapFileAbsStr;

  private:
};