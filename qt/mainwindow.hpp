#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "campaign.hpp"
#include "editcampaign.hpp"
#include "maps.hpp"
#include <QGraphicsScene>
#include <QMainWindow>

namespace Ui
{
class MainWindow;
class EditCampaign;
class Campaign;
class DmMap;
class PcMap;
} // namespace Ui

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:
    Ui::MainWindow *ui;
    Ui::EditCampaign *uiEditCampaign;
    Ui::Campaign *uiCampaign;
    Ui::DmMap *uiDm;
    Ui::PcMap *uiPc;
    QWidget editCampaignWidget;
    EditCampaign editCampaign;
    Maps maps;
    bool campaignOpen = false;
    QString fileName;

  private slots:
    void CreateNewCampaign();
    void SaveCampaign();
    void LoadCampaign();
    void SetBaseInformation(QString title);
};

#endif // MAINWINDOW_H