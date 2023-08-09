#include "../global.hpp"
#include "editcampaign.hpp"
#include "maps.hpp"
#include <filesystem>
// #include <iostream>

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
    maps.LoadMaps(editCampaign.mapsFileAbsStr);
    std::string fileNameStr = fs::current_path().parent_path().string() + std::filesystem::path::preferred_separator + "tests_qt" + std::filesystem::path::preferred_separator + "pics" +
                              std::filesystem::path::preferred_separator + "maps" + std::filesystem::path::preferred_separator + "black_1920_1080_dm.jpg";

    if (std::filesystem::is_regular_file(fileNameStr))
    {
        maps.maps.front().CopyFile(fileNameStr);
        // there is a bug in older gcc versions which did not allow to copy if the file still exists
        maps.maps.front().CopyFile(fileNameStr);
    }
    else
    {
        return 1;
    }
}