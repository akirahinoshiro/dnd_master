#include "campaign.hpp"
#include <filesystem>
#include <fstream>
// #include <iostream>

#ifdef __unix__
char separator = '/';
#elif defined(_WIN32) || defined(WIN32)
#define OS_Windows
// char separator = '\';
#endif

Campaign::Campaign()
{
}

Campaign::~Campaign()
{
}

void Campaign::LoadCampaign(std::string baseFile)
{
    if (std::filesystem::exists(baseFile))
    {
        auto endFolder = 0;
        for (auto i = baseFile.size() - 1; i > 0; i--)
        {
            if (baseFile.at(i) == separator)
            {
                endFolder = i + 1;
                break;
            }
        }
        baseFolder = baseFile.substr(0, endFolder);
        std::ifstream fileInput(baseFile);
        std::stringstream buffer;
        buffer << fileInput.rdbuf();
        /// check if it is a valid campaign file
        if (buffer.str().find("<campaign>") != std::string::npos)
        {
            if (buffer.str().find("</campaign>") != std::string::npos)
            {
                auto begin = buffer.str().find("<title>");
                auto end = buffer.str().find("</title>");
                if ((begin != std::string::npos) && (end != std::string::npos))
                    title = buffer.str().substr(begin + 7, end - begin - 7);
                begin = buffer.str().find("<maps>");
                end = buffer.str().find("</maps>");
                if ((begin != std::string::npos) && (end != std::string::npos))
                {
                    mapsFile = baseFolder;
                    if (buffer.str().at(begin + 6) == '.')
                        begin++;
                    if (buffer.str().at(begin + 6) == separator)
                        begin++;
                    mapsFile.append(buffer.str().substr(begin + 6, end - begin - 6));
                    LoadMaps();

                    // std::shared_ptr<Maps> p = std::make_shared<Maps>();
                    // p->SetTitle("test3");
                    // maps.push_back(p);
                }
                begin = buffer.str().find("<enemies>");
                end = buffer.str().find("</enemies>");
                if ((begin != std::string::npos) && (end != std::string::npos))
                {
                    enemiesFile = baseFolder;
                    if (buffer.str().at(begin + 9) == '.')
                        begin++;
                    if (buffer.str().at(begin + 9) == separator)
                        begin++;
                    enemiesFile.append(buffer.str().substr(begin + 9, end - begin - 9));
                }
                begin = buffer.str().find("<chars>");
                end = buffer.str().find("</chars>");
                if ((begin != std::string::npos) && (end != std::string::npos))
                {
                    charsFile = baseFolder;
                    if (buffer.str().at(begin + 7) == '.')
                        begin++;
                    if (buffer.str().at(begin + 7) == separator)
                        begin++;
                    charsFile.append(buffer.str().substr(begin + 7, end - begin - 7));
                }
            }
        }
    }
}

void Campaign::LoadMaps()
{
    if (std::filesystem::exists(mapsFile))
    {
        std::ifstream fileInput(mapsFile);
        std::stringstream buffer;
        buffer << fileInput.rdbuf();
        /// check if it is a valid campaign file
        if (buffer.str().find("<maps>") != std::string::npos)
        {
            if (buffer.str().find("</maps>") != std::string::npos)
            {
                std::string tmpStr = buffer.str();
                for (;;)
                {
                    auto begin = tmpStr.find("<mapfile>");
                    auto end = tmpStr.find("</mapfile>");
                    if ((begin != std::string::npos) && (end != std::string::npos))
                    {
                        std::string tmpFolderStr = mapsFile;
                        for (auto i = tmpFolderStr.size() - 1; i > 0; i--)
                        {
                            if (tmpFolderStr.at(i) == separator)
                                break;
                            else
                                tmpFolderStr.pop_back();
                        }
                        std::string fileNameStr = tmpStr.substr(begin + 9, end - begin - 9);
                        for (auto i = 0u; i < fileNameStr.size(); i++)
                        {
                            if (fileNameStr.find(separator) != std::string::npos)
                            {
                                fileNameStr = fileNameStr.substr(1, fileNameStr.size() - 1);
                                if (fileNameStr.at(0) == separator)
                                {
                                    fileNameStr = fileNameStr.substr(1, fileNameStr.size() - 1);
                                    break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        std::shared_ptr<Maps> p = std::make_shared<Maps>();
                        // p->folder = tmpFolderStr;
                        p->filename = tmpFolderStr + fileNameStr;
                        p->LoadFile();
                        maps.push_back(p);

                        tmpStr = tmpStr.substr(end + 10, tmpStr.size() - end);
                    }
                    else
                    {
                        return;
                    }
                }
            }
        }
    }
}