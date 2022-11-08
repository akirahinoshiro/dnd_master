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
    uiDm->gvDm->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    QPixmap pixmapDm(QString::fromStdString(campaign.maps.front()->dmMapFile));
    dmScene.addPixmap(pixmapDm);
    uiDm->gvDm->scale(2.5, 2.5);
    QPixmap pixmap(100, 100);
    QPainter p(&pixmap);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRect(0, 0, pixmap.width(), pixmap.height());
    QPen pen(Qt::blue, 0);
    p.setPen(pen);
    p.fillPath(path, Qt::blue);
    p.drawPath(path);
    dmScene.addPixmap(pixmap);

    uiPc->gvPc->setScene(&pcScene);
    uiPc->gvPc->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    QPixmap pixmapPc(QString::fromStdString(campaign.maps.front()->pcMapFile));
    pcScene.addPixmap(pixmapPc);
}