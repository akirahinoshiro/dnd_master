#include "editcampaign.hpp"
#include "../global.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

EditCampaign::EditCampaign()
{
    basePtreeChanged = false;
}

EditCampaign::~EditCampaign()
{
}

void EditCampaign::CreateNew(std::string baseFilename)
{
    std::filesystem::create_directory(std::filesystem::path(baseFilename).parent_path());
    baseFileNameStr = baseFilename;
    std::ofstream file(baseFileNameStr);
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

    write_json(baseFilename, basePtree);
    basePtreeChanged = false;
}

void EditCampaign::SetBaseInformation(std::string title, std::string mapsFile, std::string enemiesFile, std::string charsFile)
{
    titleStr = title;
    mapsFileStr = mapsFile;
    enemiesFileStr = enemiesFile;
    charsFileStr = charsFile;

    basePtree.put("title", titleStr);
    basePtree.put("mapsFile", mapsFileStr);
    basePtree.put("enemiesFile", enemiesFileStr);
    basePtree.put("charsFile", charsFileStr);

    write_json(baseFileNameStr, basePtree);
    basePtreeChanged = false;

    // std::stringstream ss;
    // boost::property_tree::json_parser::write_json(ss, basePtree);
    // std::cout << ss.str() << std::endl;
}