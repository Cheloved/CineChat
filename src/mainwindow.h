#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "custominclude.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void RefreshWidgetList(QObject* parent = nullptr);
    void SetupWidgets();

private:
    Ui::MainWindow *ui;
    std::map<QString, QObject*> widgetList;

    QMediaPlayer* player;
    QVideoWidget* videoWidget;

    int screenWidth, screenHeight, width, height;
};

#endif // MAINWINDOW_H
