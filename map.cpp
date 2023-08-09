#include "map.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

Map::Map(std::string mapFile, std::string mapFolder, std::string mapFileAbs)
{
    mapFileStr = mapFile;
    mapFolderStr = mapFolder;
    mapFileAbsStr = mapFileAbs;
}

Map::~Map()
{
}

void Map::SaveFile()
{
    std::filesystem::create_directory(std::filesystem::path(mapFileAbsStr).parent_path());
    if (!std::filesystem::is_regular_file(mapFileAbsStr))
    {
        std::ofstream outfile(mapFileAbsStr);
    }
    write_json(mapFileAbsStr, mapPtree);
}

void Map::LoadFile()
{
    read_json(mapFileAbsStr, mapPtree);
    using boost::property_tree::ptree;
    for (ptree::const_iterator it = mapPtree.begin(); it != mapPtree.end(); ++it)
    {
        if (it->first == "title")
            titleStr = it->second.get_value<std::string>();
        std::cout << titleStr << std::endl;
    }
}

void Map::SetTitle(std::string title)
{
    titleStr = title;
    mapPtree.put("title", titleStr);
}

std::string Map::GetTitle()
{
    std::cout << titleStr << std::endl;
    return titleStr;
}
