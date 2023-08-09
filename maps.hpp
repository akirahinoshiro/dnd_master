#pragma once
#include "map.hpp"
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <vector>

class Maps
{
  public:
    Maps(std::string mapsFile, std::string mapsFolder, std::string mapsFileAbs);
    ~Maps();
    void NewMap(std::string mapName);
    void SaveMaps();
    void LoadMaps(std::string mapsFileAbs);
    bool mapsChanged;
    std::vector<Map> maps;

  private:
    boost::property_tree::ptree mapsPtree;
    std::string mapsFileStr;
    std::string mapsFolderStr;
    std::string mapsFileAbsStr;
};