#include "map.hpp"
#include <iostream>

Map::Map(std::string mapFile, std::string mapFolder, std::string mapFileAbs)
{
    mapFileStr = mapFile;
    mapFolderStr = mapFolder;
    mapFileAbsStr = mapFileAbs;
    std::cout << mapFileStr << std::endl;
    std::cout << mapFolderStr << std::endl;
    std::cout << mapFileAbsStr << std::endl;
}

Map::~Map()
{
}