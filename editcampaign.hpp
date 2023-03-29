#pragma once
#include <boost/property_tree/ptree.hpp>
#include <string>

class EditCampaign
{
  public:
    EditCampaign();
    ~EditCampaign();
    void CreateNew(std::string baseFilename);
    void SetBaseInformation(std::string title, std::string mapsFile, std::string enemiesFile, std::string charsFile);

  private:
    boost::property_tree::ptree basePtree;
    bool basePtreeChanged;
    std::string baseFileNameStr;
    std::string titleStr;
    std::string mapsFileStr;
    std::string enemiesFileStr;
    std::string charsFileStr;
};