#include "../global.hpp"
#include "editcampaign.hpp"
#include "maps.hpp"
#include <filesystem>

namespace fs = std::filesystem;
int main(int argc, char **argv)
{
    std::string filename = fs::current_path();
    filename.push_back(std::filesystem::path::preferred_separator);
    filename.append("ctest_campaign");
    filename.push_back(std::filesystem::path::preferred_separator);
    filename.append("ctest_campaign.json");
    EditCampaign editCampaign;
    editCampaign.LoadFiles(filename);

    Maps maps(editCampaign.mapsFileStr, editCampaign.mapsFolderStr, editCampaign.mapsFileAbsStr);
    maps.NewMap("test0");
    maps.NewMap("test1");
    maps.SaveMaps();
    maps.LoadMaps(editCampaign.mapsFileAbsStr);

    if (maps.maps.size() != 2)
        return 1;
    if (maps.maps.at(0).mapFileStr != "test0.json")
        return 2;
    if (maps.maps.at(1).mapFileStr != "test1.json")
        return 3;

    maps.maps.at(0).SetTitle("test0 title");
    if (maps.maps.at(0).GetTitle() != "test0 title")
        return 4;
    maps.maps.at(1).SetTitle("test1 title");
    if (maps.maps.at(1).GetTitle() != "test1 title")
        return 5;
    for (auto idx : maps.maps)
        idx.SaveFile();
    maps.maps.at(0).SetTitle("crap0");
    if (maps.maps.at(0).GetTitle() != "crap0")
        return 6;
    maps.maps.at(1).SetTitle("crap1");
    if (maps.maps.at(1).GetTitle() != "crap1")
        return 7;
    for (auto &idx : maps.maps)
        idx.LoadFile();
    if (maps.maps.at(0).GetTitle() != "test0 title")
        return 8;
    if (maps.maps.at(1).GetTitle() != "test1 title")
        return 9;
}