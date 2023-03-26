#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

// #include <fstream>
// #include <iostream>

// #include <boost/property_tree/json_parser.hpp>
// #include <boost/property_tree/ptree.hpp>

// void print(boost::property_tree::ptree const &pt)
// {
//     using boost::property_tree::ptree;
//     ptree::const_iterator end = pt.end();
//     for (ptree::const_iterator it = pt.begin(); it != end; ++it)
//     {
//         std::cout << it->first << ": " << it->second.get_value<std::string>() << std::endl;
//         std::cout << it->second.get_value<std::string>().size() << std::endl;
//         print(it->second);
//     }
// }

// int main()
// {
//     using boost::property_tree::ptree;

//     ptree opt;
//     opt.put("height", 32);
//     opt.put("several.levels.depth", "val");
//     ptree mammals;
//     mammals.put("hare", "red");
//     mammals.put("wolf", "grey");
//     mammals.put("spider", "blue");
//     ptree fish;
//     fish.put("dolphin", "white");
//     ptree animals;
//     animals.add_child("mammals", mammals);
//     animals.add_child("fish", fish);
//     opt.add_child("animals", animals);
//     write_json("out.json", opt);

//     ptree inpt;
//     read_json("out.json", inpt);
//     print(inpt);
// }
