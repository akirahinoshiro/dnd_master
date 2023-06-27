#include "qt/mainwindow.hpp"
#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <filesystem>
#include <iostream>

int main(int argc, char *argv[])
{
    auto path = std::filesystem::current_path();
    std::cout << path << std::endl;

    QApplication a(argc, argv);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    std::string enemies00 = "../tests_qt/pics/enemies/red_64_64.jpg";
    if (!std::filesystem::is_regular_file(enemies00))
        return 1;
    std::string maps00 = "../tests_qt/pics/maps/black_1920_1080.jpg";
    if (!std::filesystem::is_regular_file(maps00))
        return 2;
    std::string player00 = "../tests_qt/pics/players/blue_64_64.jpg";
    if (!std::filesystem::is_regular_file(player00))
        return 3;
    std::string player01 = "../tests_qt/pics/players/green_64_64.jpg";
    if (!std::filesystem::is_regular_file(player01))
        return 4;

    QGraphicsPixmapItem item(QPixmap(QString::fromStdString(maps00)));
    scene.addItem(&item);
    view.show();
    return a.exec();
}