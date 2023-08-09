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
    if (!std::filesystem::is_regular_file(baseFileNameStr))
    {
        std::ofstream outfile(baseFileNameStr);
    }

    mapsFolderStr = "maps";
    mapsFolderStr.push_back(std::filesystem::path::preferred_separator);
    mapsFileStr = "maps.json";
    mapsFileAbsStr = parentFolderStr + mapsFolderStr + mapsFileStr;
    std::filesystem::create_directory(std::filesystem::path(mapsFileAbsStr).parent_path());
    if (!std::filesystem::is_regular_file(mapsFileAbsStr))
    {
        std::ofstream outfile(mapsFileAbsStr);
    }

    enemiesFolderStr = "enemies";
    enemiesFolderStr.push_back(std::filesystem::path::preferred_separator);
    enemiesFileStr = "enemies.json";
    enemiesFileAbsStr = parentFolderStr + enemiesFolderStr + enemiesFileStr;
    std::filesystem::create_directory(std::filesystem::path(enemiesFileAbsStr).parent_path());
    if (!std::filesystem::is_regular_file(enemiesFileAbsStr))
    {
        std::ofstream outfile(enemiesFileAbsStr);
    }

    charsFolderStr = "chars";
    charsFolderStr.push_back(std::filesystem::path::preferred_separator);
    charsFileStr = "chars.json";
    charsFileAbsStr = parentFolderStr + charsFolderStr + charsFileStr;
    std::filesystem::create_directory(std::filesystem::path(charsFileAbsStr).parent_path());
    if (!std::filesystem::is_regular_file(charsFileAbsStr))
    {
        std::ofstream outfile(charsFileAbsStr);
    }

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
        // write_json(mapsFileAbsStr, mapsPtree);
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

void EditCampaign::LoadFiles(std::string baseFilename)
{
    if (std::filesystem::is_regular_file(baseFilename))
    {
        parentFolderStr = std::filesystem::path(baseFilename).parent_path();
        parentFolderStr.push_back(std::filesystem::path::preferred_separator);
        baseFileNameStr = baseFilename;
        read_json(baseFileNameStr, basePtree);
        LoadBaseFile();
    }
    if (std::filesystem::is_regular_file(mapsFileAbsStr))
    {
        // read_json(mapsFileAbsStr, mapsPtree);
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

std::string EditCampaign::GetTitle()
{
    return titleStr;
}

void EditCampaign::LoadBaseFile()
{
    int properties = 0;
    using boost::property_tree::ptree;
    ptree::const_iterator end = basePtree.end();
    for (ptree::const_iterator it = basePtree.begin(); it != end; ++it)
    {
        if (it->first == "title")
        {
            titleStr = it->second.get_value<std::string>();
            properties++;
        }
        if (it->first == "mapsFile")
        {
            if (std::filesystem::is_regular_file(parentFolderStr + it->second.get_value<std::string>()))
            {
                // mapsFileAbsStr = std::filesystem::path(parentFolderStr + it->second.get_value<std::string>()).parent_path();
                // mapsFileAbsStr.push_back(std::filesystem::path::preferred_separator);
                // mapsFileStr = parentFolderStr + it->second.get_value<std::string>();
                // mapsFileAbsStr = mapsFileStr;
                mapsFileAbsStr = parentFolderStr + it->second.get_value<std::string>();
                mapsFolderStr = std::filesystem::path(mapsFileAbsStr).parent_path();
                mapsFolderStr.push_back(std::filesystem::path::preferred_separator);
                mapsFolderStr = mapsFolderStr.substr(parentFolderStr.size(), mapsFolderStr.size());
                mapsFileStr = mapsFileAbsStr.substr(parentFolderStr.size() + mapsFolderStr.size(), mapsFileAbsStr.size());
                properties++;
            }
        }
        if (it->first == "enemiesFile")
        {
            if (std::filesystem::is_regular_file(parentFolderStr + it->second.get_value<std::string>()))
            {
                // enemiesFileAbsStr = std::filesystem::path(parentFolderStr + it->second.get_value<std::string>()).parent_path();
                // enemiesFileAbsStr.push_back(std::filesystem::path::preferred_separator);
                // enemiesFileStr = parentFolderStr + it->second.get_value<std::string>();
                // enemiesFolderStr = std::filesystem::path(enemiesFileStr).parent_path();
                // enemiesFolderStr.push_back(std::filesystem::path::preferred_separator);
                // enemiesFolderStr = enemiesFolderStr.substr(parentFolderStr.size(), enemiesFolderStr.size());
                properties++;
            }
        }
        if (it->first == "charsFile")
        {
            if (std::filesystem::is_regular_file(parentFolderStr + it->second.get_value<std::string>()))
            {
                // charsFileAbsStr = std::filesystem::path(parentFolderStr + it->second.get_value<std::string>()).parent_path();
                // charsFileAbsStr.push_back(std::filesystem::path::preferred_separator);
                // charsFileStr = parentFolderStr + it->second.get_value<std::string>();
                // charsFolderStr = std::filesystem::path(charsFileStr).parent_path();
                // charsFolderStr.push_back(std::filesystem::path::preferred_separator);
                // charsFolderStr = charsFolderStr.substr(parentFolderStr.size(), charsFolderStr.size());
                properties++;
            }
        }
    }
    if (properties != 4)
    {
        throw std::runtime_error("base file did not cover all minimum parameters");
    }
}
