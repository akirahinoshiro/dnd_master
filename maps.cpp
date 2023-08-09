#include "maps.hpp"
#include <filesystem>
#include <fstream>

Maps::Maps(std::string mapsFile, std::string mapsFolder, std::string mapsFileAbs)
{
    mapsFileStr = mapsFile;
    mapsFolderStr = mapsFolder;
    mapsFileAbsStr = mapsFileAbs;
}

Maps::~Maps()
{
}

void Maps::NewMap(std::string mapName)
{
    maps.push_back(Map(mapName, mapName + std::filesystem::path::preferred_separator, mapsFileAbsStr + mapName + std::filesystem::path::preferred_separator + mapName + ".json"));
    std::filesystem::create_directory(std::filesystem::path(maps.back().mapFileAbsStr).parent_path());
    if (!std::filesystem::is_regular_file(maps.back().mapFileAbsStr))
    {
        std::ofstream outfile(maps.back().mapFileAbsStr);
    }
}