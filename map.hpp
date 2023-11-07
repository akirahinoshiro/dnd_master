#pragma once
#include <boost/property_tree/ptree.hpp>
#include <string>

class Map
{
  public:
    Map(std::string file, std::string folder, std::string fileAbs);
    virtual ~Map() = default;
    void SaveFile();
    void LoadFile();
    void SetTitle(const std::string &title);
    void CopyFile(const std::string &absFilePath) const;
    std::string GetTitle();
    std::string GetFileName();

  private:
    boost::property_tree::ptree mapPtree;
    std::string titleStr;
    std::string mapFileStr;
    std::string mapFolderStr;
    std::string mapFileAbsStr;
};