#pragma once
#include <string>

class Maps
{
  public:
    Maps();
    ~Maps();
    void LoadFile();
    void LoadFile(std::string file);
    std::string folder;
    std::string filename;
    std::string title;
    std::string dmMapFile;
    std::string pcMapFile;
};