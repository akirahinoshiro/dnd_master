#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "campaign.hpp"
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
    QWidget campaignWidget;
    QWidget dmWidget;
    QWidget pcWidget;
    Campaign campaign;
    QGraphicsScene dmScene;
    QGraphicsScene pcScene;

  private slots:
    void OpenSlot();
    void EditCampaignNewSlot();
    void LoadCampaign(QString filename);
};

#endif // MAINWINDOW_H