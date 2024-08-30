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

    Maps maps(editCampaign.GetFileName(), editCampaign.GetFolder(), editCampaign.GetFileAbs());
    maps.LoadMaps(editCampaign.GetFileAbs());
}