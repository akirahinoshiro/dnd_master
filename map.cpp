#include "map.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <filesystem>
#include <fstream>
// #include <iostream>

Map::Map(std::string file, std::string folder, std::string fileAbs) : mapFileStr{std::move(file)}, mapFolderStr{std::move(folder)}, mapFileAbsStr{std::move(fileAbs)}
{
}

void Map::SaveFile()
{
    std::filesystem::create_directory(std::filesystem::path(mapFileAbsStr).parent_path());
    if (!std::filesystem::is_regular_file(mapFileAbsStr))
    {
        const std::ofstream outfile(mapFileAbsStr);
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
        {
            titleStr = it->second.get_value<std::string>();
        }
    }
}

void Map::SetTitle(const std::string &title)
{
    titleStr = title;
    mapPtree.put("title", titleStr);
}

std::string Map::GetTitle()
{
    return titleStr;
}

void Map::CopyFile(const std::string &absFilePath) const
{
    if (std::filesystem::is_regular_file(absFilePath))
    {
        std::filesystem::copy(absFilePath,
                              std::filesystem::path(mapFileAbsStr).parent_path().string() + std::filesystem::path::preferred_separator +
                                  absFilePath.substr(std::filesystem::path(absFilePath).parent_path().string().size() + 1, absFilePath.size()),
                              std::filesystem::copy_options::overwrite_existing);
        if (!std::filesystem::is_regular_file(std::filesystem::path(mapFileAbsStr).parent_path().string() + std::filesystem::path::preferred_separator +
                                              absFilePath.substr(std::filesystem::path(absFilePath).parent_path().string().size() + 1, absFilePath.size())))
        {
            throw(std::invalid_argument("resulting filename is not a valid file"));
        }
    }
}

std::string Map::GetFileName()
{
    return mapFileStr;
}
