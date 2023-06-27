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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), uiEditCampaign(new Ui::EditCampaign), uiCampaign(new Ui::Campaign), uiDm(new Ui::DmMap), uiPc(new Ui::PcMap)
{
    ui->setupUi(this);
    uiEditCampaign->setupUi(&editCampaignWidget);
    ui->editCampaignLayout->addWidget(&editCampaignWidget);
    uiCampaign->setupUi(&campaignWidget);
    ui->campaign_layout->addWidget(&campaignWidget);
    uiDm->setupUi(&dmWidget);
    ui->dm_layout->addWidget(&dmWidget);
    uiPc->setupUi(&pcWidget);
    ui->pc_layout->addWidget(&pcWidget);
    ui->splitter->setStretchFactor(0, 2);

    // connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(OpenSlot()));
    connect(uiEditCampaign->newEditCampaignBtn, SIGNAL(clicked()), this, SLOT(EditCampaignNewSlot()));
    connect(uiEditCampaign->saveEditCampaignBtn, SIGNAL(clicked()), this, SLOT(EditCampaignSaveSlot()));
    connect(uiEditCampaign->loadEditCampaignBtn, SIGNAL(clicked()), this, SLOT(EditCampaignLoadSlot()));
    // LoadCampaign("/home/tosch/.projects/private/dnd_master/campaigns/dragon_of_icespire_peak/base.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete uiEditCampaign;
    delete uiCampaign;
    delete uiDm;
    delete uiPc;
}

void MainWindow::EditCampaignNewSlot()
{
    QString filter = "*.json";
    auto filename = QFileDialog::getSaveFileName(this, "Select a file to save...", QDir::homePath(), filter);
    if (filename.size())
    {
        if (!(filename.mid(filename.size() - filter.size() + 1, filter.size() - 1) == filter.mid(1, filter.size() - 1)))
        {
            filename.append(".json");
        }
        editCampaign.CreateNew(filename.toStdString());
    }
}

void MainWindow::EditCampaignSaveSlot()
{
}

void MainWindow::EditCampaignLoadSlot()
{
    QString filter = "*.json";
    auto filename = QFileDialog::getOpenFileName(this, "Select a file to load...", QDir::homePath(), filter);
    if (filename.size())
    {
        if (!(filename.mid(filename.size() - filter.size() + 1, filter.size() - 1) == filter.mid(1, filter.size() - 1)))
        {
            filename.append(".json");
        }
        editCampaign.LoadFiles(filename.toStdString());
    }
}

// void MainWindow::OpenSlot()
// {
// QString filter = "*.xml";
// QStringList filenameList = QFileDialog::getOpenFileNames(this, "Select a file to open...", QDir::homePath(), filter);
// if (filenameList.size())
//     LoadCampaign(filenameList.at(0));
// }

// void MainWindow::CampaignLoadSlot(QString filename)
// {
// campaign.LoadCampaign(filename.toStdString());

// uiDm->gvDm->setScene(&dmScene);
// uiDm->gvDm->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
// QPixmap pixmapDm(QString::fromStdString(campaign.maps.front()->dmMapFile));
// dmScene.addPixmap(pixmapDm);
// uiDm->gvDm->scale(2.5, 2.5);

// // QPixmap pixmap(100, 100);
// // QPainter p(&pixmap);
// // p.setRenderHint(QPainter::Antialiasing);
// // QPainterPath path;
// // path.addRect(0, 0, pixmap.width(), pixmap.height());
// // QPen pen(Qt::blue, 0);
// // p.setPen(pen);
// // p.fillPath(path, Qt::blue);
// // p.drawPath(path);
// // dmScene.addPixmap(pixmap);

// uiPc->gvPc->setScene(&pcScene);
// uiPc->gvPc->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
// QPixmap pixmapPc(QString::fromStdString(campaign.maps.front()->pcMapFile));
// pcScene.addPixmap(pixmapPc);
// }