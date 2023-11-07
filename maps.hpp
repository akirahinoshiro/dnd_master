#pragma once
#include "map.hpp"
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <vector>

class Maps
{
  public:
    Maps(std::string file, std::string folder, std::string fileAbs);
    virtual ~Maps() = default;
    void NewMap(const std::string &mapName);
    void SaveMaps();
    void LoadMaps(const std::string &mapsFileAbs);
    std::vector<Map> maps;

  private:
    boost::property_tree::ptree mapsPtree;
    std::string mapsFileStr;
    std::string mapsFolderStr;
    std::string mapsFileAbsStr;
    bool mapsChanged = false;
};