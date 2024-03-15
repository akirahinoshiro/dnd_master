#include "mainwindow.hpp"
#include "global.hpp"
#include "ui_campaign.h"
#include "ui_dm_map.h"
#include "ui_edit_campaign.h"
#include "ui_edit_map.h"
#include "ui_mainwindow.h"
#include "ui_pc_map.h"
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QStandardItemModel>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), uiEditCampaign(new Ui::EditCampaign), uiCampaign(new Ui::Campaign), uiDm(new Ui::DmMap), uiPc(new Ui::PcMap), uiEditMap(new Ui::EditMap),
      maps(editCampaign.GetFileName(), editCampaign.GetFolder(), editCampaign.GetFileAbs())
// MainWindow::MainWindow(QWidget *parent)
{
    ui->setupUi(this);
    uiEditCampaign->setupUi(&editCampaignWidget);
    ui->editCampaignLayout->addWidget(&editCampaignWidget);
    uiEditMap->setupUi(&editMapWidget);
    ui->editMapLayout->addWidget(&editMapWidget);

    connect(uiEditCampaign->newEditCampaignBtn, SIGNAL(clicked()), SLOT(CreateNewCampaign()));
    connect(uiEditCampaign->saveEditCampaignBtn, SIGNAL(clicked()), SLOT(SaveCampaign()));
    connect(uiEditCampaign->loadEditCampaignBtn, SIGNAL(clicked()), SLOT(LoadCampaign()));
    connect(uiEditCampaign->titleEdit, SIGNAL(textChanged(QString)), SLOT(SetBaseInformation(QString)));
    connect(uiEditCampaign->addMapBtn, SIGNAL(clicked()), this, SLOT(NewMap()));
    connect(uiEditCampaign->mapsWidget, &QTableWidget::itemChanged, this, &MainWindow::OnItemChanged);
    connect(uiEditCampaign->mapsWidget, &QTableWidget::itemSelectionChanged, this, &MainWindow::OnSelectionChanged);
    connect(uiEditMap->addDMBtn, &QPushButton::clicked, this, &MainWindow::AddDMMap);
    connect(uiEditMap->addPCBtn, &QPushButton::clicked, this, &MainWindow::AddPCMap);

    /// just for testing
    fileName = "/home/tosch/campaigns/test.json";
    campaignOpen = true;
    editCampaign.LoadFiles(fileName.toStdString());
    uiEditCampaign->titleEdit->setText(QString::fromStdString(editCampaign.GetTitle()));
    campaignChanged = false;
    this->setWindowTitle("MainWindow");
    maps.InitializeMaps(editCampaign.GetFileName(), editCampaign.GetFolder(), editCampaign.GetFileAbs());
    maps.LoadMaps(editCampaign.GetFileAbs());
    UpdateMapList();
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
    delete uiEditMap;
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
    if (fileName.size())
    {
        if (!fileName.contains(".json"))
        {
            fileName.append(".json");
        }
        editCampaign.CreateNew(fileName.toStdString());
        campaignOpen = true;
    }
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
            UpdateMapList();
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
        bool ok;
        QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("map filename"), QLineEdit::Normal, "", &ok);
        if (ok && !text.isEmpty())
        {
            maps.NewMap(text.toStdString());
            maps.SaveMaps();
            UpdateMapList();
        }
    }
}

void MainWindow::UpdateMapList()
{
    if (campaignOpen)
    {
        /// Disconnect the signal
        disconnect(uiEditCampaign->mapsWidget, &QTableWidget::itemChanged, this, &MainWindow::OnItemChanged);

        uiEditCampaign->mapsWidget->setRowCount(maps.maps.size());
        for (int row = 0; row < uiEditCampaign->mapsWidget->rowCount(); ++row)
        {
            for (int col = 0; col < uiEditCampaign->mapsWidget->columnCount(); ++col)
            {
                if (col == 0)
                {
                    auto item = new QTableWidgetItem(QString::fromStdString(maps.maps.at(row).GetTitle()));
                    uiEditCampaign->mapsWidget->setItem(row, 0, item);
                }
                else if (col == 1)
                {
                    auto item = new QTableWidgetItem(QString::fromStdString(maps.maps.at(row).GetFileName()));
                    uiEditCampaign->mapsWidget->setItem(row, 1, item);
                }
            }
        }
        /// Reconnect the signal
        connect(uiEditCampaign->mapsWidget, &QTableWidget::itemChanged, this, &MainWindow::OnItemChanged);
    }
}

void MainWindow::OnItemChanged(QTableWidgetItem *item)
{
    if (item->column() == 0)
    {
        maps.maps.at(item->row()).SetTitle(item->text().toStdString());
        maps.SaveMaps();
    }
    else if (item->column() == 1)
    {
        UpdateMapList();
    }
}

void MainWindow::OnSelectionChanged()
{
    mapSelRow = uiEditCampaign->mapsWidget->currentRow();
}

void MainWindow::AddDMMap()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/tosch/", tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty())
    {
        if (std::filesystem::is_regular_file(fileName.toStdString()))
        {
            maps.maps.at(mapSelRow).CopyFile(fileName.toStdString());
            // there is a bug in older gcc versions which did not allow to copy if the file still exists
            maps.maps.at(mapSelRow).CopyFile(fileName.toStdString());
        }
    }
}

void MainWindow::AddPCMap()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/tosch/", tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty())
    {
        if (std::filesystem::is_regular_file(fileName.toStdString()))
        {
            maps.maps.at(mapSelRow).CopyFile(fileName.toStdString());
            // there is a bug in older gcc versions which did not allow to copy if the file still exists
            maps.maps.at(mapSelRow).CopyFile(fileName.toStdString());
        }
    }
}