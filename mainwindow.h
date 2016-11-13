#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoStack>
#include <memory>
#include "DataProvider.h"

class QWidget;
class QLabel;
class QImage;
class QEvent;
class SectorForm;
class BaseStationForm;
class SelectBaseStationForm;
class QGraphicsScene;
class QGraphicsView;
class QGraphicsPixmapItem;
class QTreeWidgetItem;
class Worker;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DataProvider & p_data, const Worker * p_worker, QWidget *parent = 0);
    void closeEvent(QCloseEvent * event);
    ~MainWindow();

    void addTreeRoot(std::shared_ptr<QTreeWidgetItem> treeItem, QString name, QString description);
    void addTreeChild(QTreeWidgetItem * parent, QString name, QString description);

signals:
    void calculatePressed();

public slots:
    void displayImage(const QPixmap & img);

private:
    void addMenu();
    BaseStations::iterator getIndexOfBaseStation();
    void setTreeView();

    Ui::MainWindow *ui;
    QUndoStack m_Stack;
    DataProvider & data;

    QGraphicsScene * scene;
    QGraphicsPixmapItem * item;

    std::unique_ptr<BaseStationForm> baseStationForm;
    std::unique_ptr<SectorForm> sectorForm;
    std::unique_ptr<SelectBaseStationForm> selectBaseStation;

private slots:
    void on_actionUndo_The_Last_Action_triggered();
    void on_actionSave_triggered();
    void on_saveButton_clicked();
    void on_undoButton_clicked();

    void on_baseStationUi_clicked();
    void on_viewCreatedObject_clicked();
    void on_sectorUI_clliced();

    void selectBase();
    void updateTree();
    void drawImage();

};

#endif // MAINWINDOW_H
