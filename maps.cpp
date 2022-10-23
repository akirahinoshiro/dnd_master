#include "maps.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

#ifdef __unix__
char separatorMaps = '/';
#elif defined(_WIN32) || defined(WIN32)
#define OS_Windows
// char separatorMaps = '\';
#endif

Maps::Maps()
{
}

Maps::~Maps()
{
}

void Maps::LoadFile()
{
    if (std::filesystem::exists(filename))
    {
        folder = filename;
        for (auto i = folder.size() - 1; i > 0; i--)
        {
            if (folder.at(i) == separatorMaps)
                break;
            else
                folder.pop_back();
        }
        std::ifstream fileInput(filename);
        std::stringstream buffer;
        buffer << fileInput.rdbuf();
        /// check if it is a valid campaign file
        if (buffer.str().find("<mapfile>") != std::string::npos)
        {
            if (buffer.str().find("</mapfile>") != std::string::npos)
            {
                std::string tmpStr = buffer.str();
                auto begin = tmpStr.find("<title>");
                auto end = tmpStr.find("</title>");
                title = tmpStr.substr(begin + 7, end - begin - 7);
                begin = tmpStr.find("<dm_map>");
                end = tmpStr.find("</dm_map>");
                dmMapFile = tmpStr.substr(begin + 8, end - begin - 8);
                for (auto i = 0u; i < dmMapFile.size(); i++)
                {
                    if (dmMapFile.at(0) == separatorMaps)
                    {
                        dmMapFile = dmMapFile.substr(1, dmMapFile.size() - 1);
                        break;
                    }
                    dmMapFile = dmMapFile.substr(1, dmMapFile.size() - 1);
                }
                dmMapFile = folder + dmMapFile;
                title = tmpStr.substr(begin + 7, end - begin - 7);
                begin = tmpStr.find("<pc_map>");
                end = tmpStr.find("</pc_map>");
                pcMapFile = tmpStr.substr(begin + 8, end - begin - 8);
                for (auto i = 0u; i < pcMapFile.size(); i++)
                {
                    if (pcMapFile.at(0) == separatorMaps)
                    {
                        pcMapFile = pcMapFile.substr(1, pcMapFile.size() - 1);
                        break;
                    }
                    pcMapFile = pcMapFile.substr(1, pcMapFile.size() - 1);
                }
                pcMapFile = folder + pcMapFile;
            }
        }
    }
}

void Maps::LoadFile(std::string file)
{
    filename = file;
    LoadFile();
}