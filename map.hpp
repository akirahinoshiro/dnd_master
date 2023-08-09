#pragma once
#include <boost/property_tree/ptree.hpp>
#include <string>

class Map
{
  public:
    Map(std::string mapFile, std::string mapFolder, std::string mapFileAbs);
    ~Map();
    void SaveFile();
    void LoadFile();
    void SetTitle(std::string title);
    std::string GetTitle();
    std::string mapFileStr;
    std::string mapFolderStr;
    std::string mapFileAbsStr;

  private:
    boost::property_tree::ptree mapPtree;
    std::string titleStr;
};