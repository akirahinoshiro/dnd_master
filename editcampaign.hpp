#pragma once
#include <boost/property_tree/ptree.hpp>
#include <string>

class EditCampaign
{
  public:
    EditCampaign() = default;
    virtual ~EditCampaign() = default;
    void CreateNew(const std::string &baseFilename);
    void SetBaseInformation(const std::string &title = "", const std::string &mapsFile = "", const std::string &enemiesFile = "", const std::string &charsFile = "");
    void SaveFiles();
    void LoadFiles(const std::string &baseFilename);
    std::string GetTitle();
    std::string GetFileName();
    std::string GetFolder();
    std::string GetFileAbs();

  private:
    void LoadBaseFile();
    bool filesModified = false;
    std::string mapsFolderStr;
    std::string mapsFileStr;
    std::string mapsFileAbsStr;
    boost::property_tree::ptree basePtree;
    boost::property_tree::ptree mapsPtree;
    boost::property_tree::ptree enemiesPtree;
    boost::property_tree::ptree charsPtree;
    std::string parentFolderStr;
    std::string baseFileNameStr;
    std::string enemiesFolderStr;
    std::string enemiesFileStr;
    std::string enemiesFileAbsStr;
    std::string charsFolderStr;
    std::string charsFileStr;
    std::string charsFileAbsStr;
    std::string titleStr;
};