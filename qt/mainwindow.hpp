#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "campaign.hpp"
#include "editcampaign.hpp"
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
    Campaign campaign;
    EditCampaign editCampaign;
    Ui::MainWindow *ui;
    Ui::EditCampaign *uiEditCampaign;
    Ui::Campaign *uiCampaign;
    Ui::DmMap *uiDm;
    Ui::PcMap *uiPc;
    QWidget editCampaignWidget;
    QWidget campaignWidget;
    QWidget dmWidget;
    QWidget pcWidget;
    QGraphicsScene dmScene;
    QGraphicsScene pcScene;

  private slots:
    // void OpenSlot();
    // void CampaignLoadSlot(QString filename);
    void EditCampaignNewSlot();
    void EditCampaignSaveSlot();
    void EditCampaignLoadSlot();
    // void EditCampaignNewSlot();
    // void EditCampaignNewSlot();
};

#endif // MAINWINDOW_H