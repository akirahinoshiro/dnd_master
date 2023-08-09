#include "../global.hpp"
#include "editcampaign.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
int main(int argc, char **argv)
{
    EditCampaign editCampaign;
    std::string filename;
    filename.push_back(std::filesystem::path::preferred_separator);
    filename.append("ctest_campaign");
    filename.push_back(std::filesystem::path::preferred_separator);
    filename.append("ctest_campaign.json");
    try
    {
        editCampaign.CreateNew(filename);
    }
    catch (std::filesystem::filesystem_error const &ex)
    {
        std::cout << "what():  " << ex.what() << '\n'
                  << "path1(): " << ex.path1() << '\n'
                  << "path2(): " << ex.path2() << '\n'
                  << "code().value():    " << ex.code().value() << '\n'
                  << "code().message():  " << ex.code().message() << '\n'
                  << "code().category(): " << ex.code().category().name() << '\n';
        return 0;
    }
    return 1;
}