#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::RefreshWidgetList(QObject* parent)
{
    this->widgetList.insert( std::make_pair( parent->objectName(), parent ) );
    QList<QObject*> children = parent->children();
    for ( QObject* child : children )
        RefreshWidgetList(child);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RefreshWidgetList(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
