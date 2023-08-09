#include "maps.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <filesystem>
#include <fstream>

Maps::Maps(std::string mapsFile, std::string mapsFolder, std::string mapsFileAbs)
{
    mapsFileStr = mapsFile;
    mapsFolderStr = mapsFolder;
    mapsFileAbsStr = mapsFileAbs;
    mapsChanged = false;
}

Maps::~Maps()
{
}

void Maps::NewMap(std::string mapName)
{
    maps.push_back(
        Map(mapName, mapName + std::filesystem::path::preferred_separator,
            std::filesystem::path(mapsFileAbsStr).parent_path().string() + std::filesystem::path::preferred_separator + mapName + std::filesystem::path::preferred_separator + mapName + ".json"));
    boost::property_tree::ptree tmpPtree;
    tmpPtree.put_value(mapName + std::filesystem::path::preferred_separator + mapName + std::filesystem::path::preferred_separator + ".json");
    mapsPtree.push_back(std::make_pair("mapFile", tmpPtree));
    mapsChanged = true;
}

void Maps::SaveMaps()
{
    for (auto idx : maps)
    {
        std::filesystem::create_directory(std::filesystem::path(idx.mapFileAbsStr).parent_path());
        if (!std::filesystem::is_regular_file(idx.mapFileAbsStr))
        {
            std::ofstream outfile(idx.mapFileAbsStr);
        }
    }
    write_json(mapsFileAbsStr, mapsPtree);
}