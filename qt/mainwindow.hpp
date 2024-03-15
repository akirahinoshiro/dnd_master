#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "campaign.hpp"
#include "editcampaign.hpp"
#include "maps.hpp"
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTableWidgetItem>

namespace Ui
{
class MainWindow;
class EditCampaign;
class Campaign;
class DmMap;
class PcMap;
class EditMap;
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
    Ui::EditMap *uiEditMap;
    QWidget editCampaignWidget;
    QWidget editMapWidget;
    EditCampaign editCampaign;
    Maps maps;
    bool campaignOpen = false;
    bool campaignChanged = false;
    QString fileName;
    std::size_t mapSelRow;

  private slots:
    void CreateNewCampaign();
    void SaveCampaign();
    void LoadCampaign();
    void SetBaseInformation(QString title);
    void NewMap();
    void UpdateMapList();
    void OnItemChanged(QTableWidgetItem *item);
    void OnSelectionChanged();
    void AddDMMap();
    void AddPCMap();
};

#endif // MAINWINDOW_H