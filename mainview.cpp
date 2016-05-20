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



void MainView::on_startGame_clicked()
{
    isGameStarted = true;
    if(hitStartCounter==0){
        ui->startGame->setText("Stop");
        ui->usernameText->setText("Naoufal");
        hitStartCounter++;
    }else if (hitStartCounter==1) {
        ui->startGame->setText("Start");
        ui->usernameText->clear();
        hitStartCounter=0;
    }

}
