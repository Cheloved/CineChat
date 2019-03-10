#include "mainwindow.h"
#include <QApplication>

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QLabel>
#include <QRect>
#include <QScreen>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();

    // Get screen resolution
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect rect = screen->geometry();

    int screenWidth = rect.width();
    int screenHeight = rect.height();

    int width = 600;
    int height = 400;

    // Install default geometry
    window.setGeometry(screenWidth/2-width/2,screenHeight/2-height/2,width,height);

    // Media player and it's holder
    QMediaPlayer* player = new QMediaPlayer;
    QVideoWidget* videoWidget = new QVideoWidget;

    // Bind media player to widget
    player->setVideoOutput(videoWidget);

    // Default built-in playback
    player->setMedia(QUrl::fromLocalFile("/home/penguin/Downloads/videoplayback"));

    // Add video widget to main window
    dynamic_cast<QWidget*>(window.widgetList["mainFrame"])->setGeometry(0, 0, width, height-20);
    auto layout = new QVBoxLayout();
    layout->addWidget(videoWidget);
    window.RefreshWidgetList();
    dynamic_cast<QWidget*>(window.widgetList["mainFrame"])->setLayout(layout);


    //videoWidget->show();
    player->play();

    return a.exec();
}
