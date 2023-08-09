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
}