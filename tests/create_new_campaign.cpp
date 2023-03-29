#include "../global.hpp"
#include "editcampaign.hpp"
#include <filesystem>

namespace fs = std::filesystem;
int main(int argc, char **argv)
{
    EditCampaign editCampaign;
    std::string filename = fs::current_path();
    filename.push_back(separator);
    filename.append("ctest_campaign");
    filename.push_back(separator);
    filename.append("ctest_campaign.json");
    editCampaign.CreateNew(filename);
    editCampaign.SetBaseInformation("", "", "", "");
}