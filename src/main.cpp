#include "mainwindow.h"
#include <QApplication>

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QLabel>
#include <QRect>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    // Media player and it's holder
    QMediaPlayer* player = new QMediaPlayer;
    QVideoWidget* videoWidget = new QVideoWidget;

    // Get screen resolution
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect rect = screen->geometry();

    int screenWidth = rect.width();
    int screenHeight = rect.height();

    int width = 600;
    int height = 400;

    // Bind media player to widget
    player->setVideoOutput(videoWidget);

    // Default built-in playback
    player->setMedia(QUrl::fromLocalFile("/home/penguin/Downloads/videoplayback"));

    // Install default geometry
    videoWidget->setGeometry(screenWidth/2-width/2,screenHeight/2-height/2,width,height);

    videoWidget->show();
    player->play();

    return a.exec();
}
