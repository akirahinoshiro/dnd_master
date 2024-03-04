#include "mainwindow.hpp"
#include "global.hpp"
#include "ui_campaign.h"
#include "ui_dm_map.h"
#include "ui_edit_campaign.h"
#include "ui_mainwindow.h"
#include "ui_pc_map.h"
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QPixmap>
#include <QStandardItemModel>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), uiEditCampaign(new Ui::EditCampaign), uiCampaign(new Ui::Campaign), uiDm(new Ui::DmMap), uiPc(new Ui::PcMap),
      maps(editCampaign.GetFileName(), editCampaign.GetFolder(), editCampaign.GetFileAbs())
// MainWindow::MainWindow(QWidget *parent)
{
    ui->setupUi(this);
    uiEditCampaign->setupUi(&editCampaignWidget);
    ui->editCampaignLayout->addWidget(&editCampaignWidget);

    connect(uiEditCampaign->newEditCampaignBtn, SIGNAL(clicked()), SLOT(CreateNewCampaign()));
    connect(uiEditCampaign->saveEditCampaignBtn, SIGNAL(clicked()), SLOT(SaveCampaign()));
    connect(uiEditCampaign->loadEditCampaignBtn, SIGNAL(clicked()), SLOT(LoadCampaign()));
    connect(uiEditCampaign->titleEdit, SIGNAL(textChanged(QString)), SLOT(SetBaseInformation(QString)));
    connect(uiEditCampaign->addMapBtn, SIGNAL(clicked()), this, SLOT(NewMap()));

    /// just for testing
    campaignOpen = true;
    fileName = "/home/tosch/campaigns/test.json";
    editCampaign.LoadFiles(fileName.toStdString());
    uiEditCampaign->titleEdit->setText(QString::fromStdString(editCampaign.GetTitle()));
    campaignChanged = false;
    this->setWindowTitle("MainWindow");
}

MainWindow::~MainWindow()
{
    if (campaignChanged)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Save Changes", "Do you want to save changes before quitting?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            SaveCampaign();
        }
        else if (reply == QMessageBox::No)
        {
        }
    }
    delete uiPc;
    delete uiDm;
    delete uiCampaign;
    delete uiEditCampaign;
    delete ui;
}

void MainWindow::CreateNewCampaign()
{
    // auto fileName = QFileDialog::getSaveFileName(this, tr("Open Image"), QString::fromStdString(fs::current_path()), tr("campaign files (*.json)"));
    fileName = QFileDialog::getSaveFileName(this, tr("New Campaign"), "/home/tosch/", tr("campaign files (*.json)"));
    if (!fileName.contains(".json"))
    {
        fileName.append(".json");
    }
    editCampaign.CreateNew(fileName.toStdString());
    campaignOpen = true;
}

void MainWindow::SaveCampaign()
{
    if (campaignOpen)
    {
        editCampaign.SaveFiles();
        campaignChanged = false;
        this->setWindowTitle("MainWindow");
    }
}

void MainWindow::LoadCampaign()
{
    auto tmpFileName = QFileDialog::getOpenFileName(this, tr("Open Campaign"), "/home/tosch/", tr("campaign files (*.json)"));
    if (tmpFileName.size() > 5)
    {
        if (tmpFileName.contains(".json"))
        {
            fileName = tmpFileName;
            campaignOpen = true;
            editCampaign.LoadFiles(fileName.toStdString());
            uiEditCampaign->titleEdit->setText(QString::fromStdString(editCampaign.GetTitle()));
            campaignChanged = false;
            this->setWindowTitle("MainWindow");
            maps.InitializeMaps(editCampaign.GetFileName(), editCampaign.GetFolder(), editCampaign.GetFileAbs());
            maps.LoadMaps(editCampaign.GetFileAbs());
        }
    }
}

void MainWindow::SetBaseInformation(QString title)
{
    if (campaignOpen)
    {
        editCampaign.SetBaseInformation(title.toStdString());
        campaignChanged = true;
        this->setWindowTitle("MainWindow*");
    }
}

void MainWindow::NewMap()
{
    if (campaignOpen)
    {
        auto tmpFileName = QFileDialog::getOpenFileName(this, tr("New Map"), "/home/tosch/", tr("image files (*.png *.jpg *.jpeg *.bmp)"));
        if (tmpFileName.size() > 5)
        {
            if (tmpFileName.contains(".png") || tmpFileName.contains(".jpg") || tmpFileName.contains(".jpeg") || tmpFileName.contains(".bmp"))
            {
                maps.NewMap(tmpFileName.toStdString());
                std::string fileNameStr = std::filesystem::path(maps.maps.back().GetFileName()).string() + std::filesystem::path::preferred_separator + "test.bmp";
                std::cout << fileNameStr << std::endl;

                if (std::filesystem::is_regular_file(fileNameStr))
                {
                    maps.maps.front().CopyFile(fileNameStr);
                }
                int row = uiEditCampaign->mapsWidget->rowCount();
                uiEditCampaign->mapsWidget->insertRow(row);
                uiEditCampaign->mapsWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(maps.maps.back().GetTitle())));
                uiEditCampaign->mapsWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(maps.maps.back().GetFileName())));
                // maps.SaveMaps();
                // maps.LoadMaps(editCampaign.GetFileAbs());
                campaignChanged = true;
                this->setWindowTitle("MainWindow*");
            }
        }
        // campaignChanged = true;
        // this->setWindowTitle("MainWindow*");
    }
}
