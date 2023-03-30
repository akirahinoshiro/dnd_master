#pragma once
#include <boost/property_tree/ptree.hpp>
#include <string>

class EditCampaign
{
  public:
    EditCampaign();
    ~EditCampaign();
    void CreateNew(std::string baseFilename);
    void SetBaseInformation(std::string title = "", std::string mapsFile = "", std::string enemiesFile = "", std::string charsFile = "");
    void SaveFiles();
    bool filesModified;

  private:
    boost::property_tree::ptree basePtree;
    boost::property_tree::ptree mapsPtree;
    boost::property_tree::ptree enemiesPtree;
    boost::property_tree::ptree charsPtree;
    std::string parentFolderStr;
    std::string baseFileNameStr;
    std::string mapsFolderStr;
    std::string mapsFileStr;
    std::string mapsFileAbsStr;
    std::string enemiesFolderStr;
    std::string enemiesFileStr;
    std::string enemiesFileAbsStr;
    std::string charsFolderStr;
    std::string charsFileStr;
    std::string charsFileAbsStr;
    std::string titleStr;
};