#pragma once
#include "maps.hpp"
#include <memory>
#include <string>
#include <vector>

class Campaign
{
  public:
    Campaign();
    ~Campaign();
    void LoadCampaign(std::string baseFile);
    std::string title;
    std::vector<std::shared_ptr<Maps>> maps;

  private:
    void LoadMaps();
    std::string baseFolder;
    std::string mapsFile;
    std::string enemiesFile;
    std::string charsFile;
};