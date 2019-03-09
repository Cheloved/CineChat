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

    QMediaPlayer* player = new QMediaPlayer;
    QVideoWidget* videoWidget = new QVideoWidget;

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect rect = screen->geometry();

    int screenWidth = rect.width();
    int screenHeight = rect.height();

    int width = 600;
    int height = 400;

    player->setVideoOutput(videoWidget);
    player->setMedia(QUrl::fromLocalFile("/home/penguin/Downloads/videoplayback"));


    videoWidget->setGeometry(screenWidth/2-width/2,screenHeight/2-height/2,width,height);

    videoWidget->show();
    player->play();

    return a.exec();
}
