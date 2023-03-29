#include "editcampaign.hpp"
#include "../global.hpp"
#include <filesystem>
#include <fstream>

EditCampaign::EditCampaign()
{
}

EditCampaign::~EditCampaign()
{
}

void EditCampaign::CreateNew(std::string baseFilename)
{
    std::filesystem::create_directory(std::filesystem::path(baseFilename).parent_path());
    std::ofstream file(baseFilename);
    file.close();
    std::string parentPath = std::filesystem::path(baseFilename).parent_path();
    parentPath.push_back(separator);
    std::filesystem::create_directory(parentPath + "maps");
    std::filesystem::create_directory(parentPath + "enemies");
    std::filesystem::create_directory(parentPath + "chars");
    std::string filenameEmpty = parentPath;
    filenameEmpty.push_back(separator);
    filenameEmpty.append("maps");
    filenameEmpty.push_back(separator);
    filenameEmpty.append("maps.json");
    file.open(filenameEmpty);
    file.close();
    filenameEmpty = parentPath;
    filenameEmpty.push_back(separator);
    filenameEmpty.append("enemies");
    filenameEmpty.push_back(separator);
    filenameEmpty.append("enemies.json");
    file.open(filenameEmpty);
    file.close();
    filenameEmpty = parentPath;
    filenameEmpty.push_back(separator);
    filenameEmpty.append("chars");
    filenameEmpty.push_back(separator);
    filenameEmpty.append("chars.json");
    file.open(filenameEmpty);
    file.close();
}