#include "maps.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

Maps::Maps(std::string file, std::string folder, std::string fileAbs) : mapsFileStr{std::move(file)}, mapsFolderStr{std::move(folder)}, mapsFileAbsStr{std::move(fileAbs)}
{
}

void Maps::NewMap(const std::string &mapName)
{
    const Map tmpMap{mapName + ".json", mapName + std::filesystem::path::preferred_separator,
                     std::filesystem::path(mapsFileAbsStr).parent_path().string() + std::filesystem::path::preferred_separator + mapName + std::filesystem::path::preferred_separator + mapName +
                         ".json"};
    maps.push_back(tmpMap);
    boost::property_tree::ptree tmpPtree;
    tmpPtree.put_value(mapName + std::filesystem::path::preferred_separator + mapName + ".json");
    mapsPtree.push_back(std::make_pair("mapFile", tmpPtree));
    mapsChanged = true;
}

void Maps::SaveMaps()
{
    for (auto idx : maps)
    {
        idx.SaveFile();
    }
    write_json(mapsFileAbsStr, mapsPtree);
    mapsChanged = false;
}

void Maps::LoadMaps(const std::string &mapsFileAbs)
{
    maps.clear();
    read_json(mapsFileAbsStr, mapsPtree);
    using boost::property_tree::ptree;
    for (ptree::const_iterator it = mapsPtree.begin(); it != mapsPtree.end(); ++it)
    {
        if (it->first == "mapFile")
        {
            std::string mapFile;
            std::string mapFolder;
            std::string mapFileAbs;
            mapFileAbs = std::filesystem::path(mapsFileAbs).parent_path().string() + std::filesystem::path::preferred_separator + it->second.get_value<std::string>();
            mapFolder = std::filesystem::path(mapFileAbs).parent_path().string().substr(std::filesystem::path(mapsFileAbs).parent_path().string().size() + 1, mapFileAbs.size()) +
                        std::filesystem::path::preferred_separator;
            mapFile = mapFileAbs.substr(mapFileAbs.size() - it->second.get_value<std::string>().size() + mapFolder.size(), mapFileAbs.size());
            const Map tmpMap{mapFile, mapFolder, mapFileAbs};
            maps.push_back(tmpMap);
        }
    }
}