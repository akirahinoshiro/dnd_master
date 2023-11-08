#include "mainwindow.hpp"
#include "global.hpp"
#include "ui_campaign.h"
#include "ui_dm_map.h"
#include "ui_edit_campaign.h"
#include "ui_mainwindow.h"
#include "ui_pc_map.h"
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QPixmap>
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
}

MainWindow::~MainWindow()
{
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
        }
    }
}

void MainWindow::SetBaseInformation(QString title)
{
    if (campaignOpen)
    {
        editCampaign.SetBaseInformation(title.toStdString());
    }
}
