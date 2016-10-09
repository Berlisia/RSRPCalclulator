#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button1 = new QPushButton("Add base station");
    layout = new QHBoxLayout;
    layout->addWidget(button1);
    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);
    connect(button1,SIGNAL(pressed()), this, SIGNAL(buttonHasPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete button1;
    delete layout;
}
