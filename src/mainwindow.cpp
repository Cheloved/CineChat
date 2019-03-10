#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::RefreshWidgetList(QObject* parent)
{
    if ( parent == nullptr )
        parent = this;
    this->widgetList.insert( std::make_pair( parent->objectName(), parent ) );
    QList<QObject*> children = parent->children();
    for ( QObject* child : children )
        RefreshWidgetList(child);
}

void MainWindow::SetupWidgets()
{

    // Media player and it's holder
    this->player = new QMediaPlayer;
    this->videoWidget = new QVideoWidget;

    // Bind media player to widget
    player->setVideoOutput(videoWidget);

    // Default built-in playback
    player->setMedia(QUrl::fromLocalFile("/home/penguin/Downloads/videoplayback"));

    // Add video widget to main window
    dynamic_cast<QWidget*>(widgetList["mainFrame"])->setGeometry(-10, -10, width+20, height);
    videoWidget->setGeometry(0,0,width,height-20);
    auto layout = new QVBoxLayout();
    layout->addWidget(videoWidget);
    dynamic_cast<QWidget*>(widgetList["mainFrame"])->setLayout(layout);

    //player->play();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    this->width = this->geometry().width();
    this->height = this->geometry().height();

    dynamic_cast<QWidget*>(widgetList["mainFrame"])->setGeometry(-10, -10, width+20, height);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RefreshWidgetList(this);
    this->setWindowTitle("CineChat");

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect rect = screen->geometry();

    screenWidth = rect.width();
    screenHeight = rect.height();

    width = 600;
    height = 400;

    this->setGeometry(screenWidth/2-width/2,screenHeight/2-height/2,width,height);

    this->SetupWidgets();
}

MainWindow::~MainWindow()
{
    delete player;
    delete videoWidget;
    delete ui;
}
