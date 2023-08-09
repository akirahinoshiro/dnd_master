#pragma once
#include "map.hpp"
#include <string>
#include <vector>

class Maps
{
  public:
    Maps(std::string mapsFile, std::string mapsFolder, std::string mapsFileAbs);
    ~Maps();
    void NewMap(std::string mapName);

  private:
    std::vector<Map> maps;
    std::string mapsFileStr;
    std::string mapsFolderStr;
    std::string mapsFileAbsStr;
};