#include "editcampaign.hpp"
#include "../global.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

EditCampaign::EditCampaign()
{
    filesModified = false;
}

EditCampaign::~EditCampaign()
{
}

void EditCampaign::CreateNew(std::string baseFilename)
{
    std::filesystem::create_directory(std::filesystem::path(baseFilename).parent_path());
    parentFolderStr = std::filesystem::path(baseFilename).parent_path();
    parentFolderStr.push_back(std::filesystem::path::preferred_separator);
    baseFileNameStr = baseFilename;

    mapsFolderStr = "maps";
    mapsFolderStr.push_back(std::filesystem::path::preferred_separator);
    mapsFileStr = "maps.json";
    mapsFileAbsStr = parentFolderStr + mapsFolderStr + mapsFileStr;
    std::filesystem::create_directory(std::filesystem::path(mapsFileAbsStr).parent_path());

    enemiesFolderStr = "enemies";
    enemiesFolderStr.push_back(std::filesystem::path::preferred_separator);
    enemiesFileStr = "enemies.json";
    enemiesFileAbsStr = parentFolderStr + enemiesFolderStr + enemiesFileStr;
    std::filesystem::create_directory(std::filesystem::path(enemiesFileAbsStr).parent_path());

    charsFolderStr = "chars";
    charsFolderStr.push_back(std::filesystem::path::preferred_separator);
    charsFileStr = "chars.json";
    charsFileAbsStr = parentFolderStr + charsFolderStr + charsFileStr;
    std::filesystem::create_directory(std::filesystem::path(charsFileAbsStr).parent_path());

    SetBaseInformation("new", mapsFolderStr + mapsFileStr, enemiesFolderStr + enemiesFileStr, charsFolderStr + charsFileStr);
    SaveFiles();
}

void EditCampaign::SetBaseInformation(std::string title, std::string mapsFile, std::string enemiesFile, std::string charsFile)
{
    if (!title.empty())
    {
        titleStr = title;
        basePtree.put("title", titleStr);
    }
    if (!mapsFile.empty())
    {
        mapsFileStr = mapsFile;
        basePtree.put("mapsFile", mapsFileStr);
    }
    if (!enemiesFile.empty())
    {
        enemiesFileStr = enemiesFile;
        basePtree.put("enemiesFile", enemiesFileStr);
    }
    if (!charsFile.empty())
    {
        charsFileStr = charsFile;
        basePtree.put("charsFile", charsFileStr);
    }

    filesModified = true;
}

void EditCampaign::SaveFiles()
{
    if (std::filesystem::is_regular_file(baseFileNameStr))
    {
        write_json(baseFileNameStr, basePtree);
    }
    if (std::filesystem::is_regular_file(mapsFileAbsStr))
    {
        write_json(mapsFileAbsStr, mapsPtree);
    }
    if (std::filesystem::is_regular_file(enemiesFileAbsStr))
    {
        write_json(enemiesFileAbsStr, enemiesPtree);
    }
    if (std::filesystem::is_regular_file(charsFileAbsStr))
    {
        write_json(charsFileAbsStr, charsPtree);
    }
    filesModified = false;
}

void EditCampaign::LoadFiles()
{
    if (std::filesystem::is_regular_file(baseFileNameStr))
    {
        read_json(baseFileNameStr, basePtree);
    }
    if (std::filesystem::is_regular_file(mapsFileAbsStr))
    {
        read_json(mapsFileAbsStr, mapsPtree);
    }
    if (std::filesystem::is_regular_file(enemiesFileAbsStr))
    {
        read_json(enemiesFileAbsStr, enemiesPtree);
    }
    if (std::filesystem::is_regular_file(charsFileAbsStr))
    {
        read_json(charsFileAbsStr, charsPtree);
    }
    filesModified = false;
}
