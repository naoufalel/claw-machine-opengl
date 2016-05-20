#include "mainview.h"
#include "ui_mainview.h"

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    camera = new CameraInteraction(parent);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showCamera()));
    timer->start(30);

}


void MainView::showCamera(){
    camera->displayCamera(ui->cameraShowing);
}


MainView::~MainView()
{
    delete ui;
}


