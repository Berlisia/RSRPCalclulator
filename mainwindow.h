#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void buttonHasPressed();
private:
    Ui::MainWindow *ui;
    QPushButton *button1;
    QHBoxLayout *layout;
};

#endif // MAINWINDOW_H
