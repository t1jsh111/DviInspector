#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QSharedPointer>
#include <QDebug>
#include "ViewingPane/viewingpane.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this);
    if(filePath.isEmpty()) return;

    QSharedPointer<DataStorage> dataStorage = QSharedPointer<DataStorage>(new DataStorage(filePath));

    ViewingPane* viewingPane = ui->widget;

    viewingPane->setData(dataStorage);
}
