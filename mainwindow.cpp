#include "mainwindow.hpp"
#include "ui_campaign.h"
#include "ui_dm_map.h"
#include "ui_mainwindow.h"
#include "ui_pc_map.h"
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), uiCampaign(new Ui::Campaign), uiDm(new Ui::DmMap), uiPc(new Ui::PcMap)
{
    ui->setupUi(this);
    uiCampaign->setupUi(&campaignWidget);
    ui->campaign_layout->addWidget(&campaignWidget);
    uiDm->setupUi(&dmWidget);
    ui->dm_layout->addWidget(&dmWidget);
    uiPc->setupUi(&pcWidget);
    ui->pc_layout->addWidget(&pcWidget);
    ui->splitter->setStretchFactor(0, 2);

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(OpenSlot()));
    LoadCampaign("/home/tobermann/.projects/private/dnd_master/campaigns/dragon_of_icespire_peak/base.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenSlot()
{
    QString filter = "*.xml";
    QStringList filenameList = QFileDialog::getOpenFileNames(this, "Select a file to open...", QDir::homePath(), filter);
    LoadCampaign(filenameList.at(0));
}

void MainWindow::LoadCampaign(QString filename)
{
    campaign.LoadCampaign(filename.toStdString());

    uiDm->gvDm->setScene(&dmScene);
    QPixmap pixmapDm(QString::fromStdString(campaign.maps.front()->dmMapFile));
    dmScene.addPixmap(pixmapDm);
    uiDm->gvDm->scale(.5, .5);
    uiPc->gvPc->setScene(&pcScene);
    QPixmap pixmapPc(QString::fromStdString(campaign.maps.front()->pcMapFile));
    pcScene.addPixmap(pixmapPc);
}