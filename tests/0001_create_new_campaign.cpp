#include "../global.hpp"
#include "editcampaign.hpp"
#include <filesystem>

namespace fs = std::filesystem;
int main(int argc, char **argv)
{
    std::string filename = fs::current_path();
    {
        EditCampaign editCampaign;
        filename.push_back(std::filesystem::path::preferred_separator);
        filename.append("ctest_campaign");
        filename.push_back(std::filesystem::path::preferred_separator);
        filename.append("ctest_campaign.json");
        editCampaign.CreateNew(filename);
        editCampaign.SetBaseInformation("title");
        editCampaign.SaveFiles();
        // set local random name but do not save this
        editCampaign.SetBaseInformation("random");
        if (editCampaign.GetTitle() != "random")
            return 1;
    }
    EditCampaign editCampaign;
    editCampaign.LoadFiles(filename);
    if (editCampaign.GetTitle() != "title")
        return 2;
}