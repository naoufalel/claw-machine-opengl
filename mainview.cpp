#include "mainview.h"
#include "ui_mainview.h"


MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{

    ui->setupUi(this);
    //camera = new CameraInteraction(parent);
    user = new User();

//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(showCamera()));
//    timer->start(20);

    coordX=0;

//    aTimer = new QTimer(this);
//    connect(aTimer, SIGNAL(timeout()), this, SLOT(animate()));
//    aTimer->start(100);


    setWindowTitle(tr("Claw Machine Game"));
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
        if(ui->usernameText->text()==""){
            QMessageBox(QMessageBox::Critical,tr("Error"),tr("Please enter a username before starting the game")).exec();
        }else{
            ui->startGame->setText("Stop");
            user->setUserName(ui->usernameText->text().toStdString());
            //QMessageBox(QMessageBox::Information,tr("YOW"),tr("trtyu")).exec();
            hitStartCounter++;
        }

    }else if (hitStartCounter==1) {
        ui->startGame->setText("Start");
        ui->usernameText->clear();
        hitStartCounter=0;
    }

}

void MainView::on_showScores_clicked()
{
    scores = new Score();
    scores->show();
}

void MainView::keyPressEvent(QKeyEvent *e)
{
//    if (e->key() == Qt::Key_Escape)
//        close();
//    else
//        QWidget::keyPressEvent(e);
}

void MainView::vXMove()
{

//    coordX =m_webcam->m_deplaceX;
//    coordY =m_webcam->m_deplaceY;
//    qDebug()<<coordY;
}

void MainView::animate()
{

//    (claw->x)= coordX;
//    //(m_poGlArea->y)=coordY;
//    claw->update();
//    qDebug()<<claw->x;
}


void MainView::on_moveBall_clicked()
{
    int a = ui->clawShowing->getBase().getLimit();
    if(ui->clawShowing->getBall().getX()<a){
        ui->clawShowing->getBall().setX(ui->clawShowing->getBall().getX()+1%a);
    }

    ui->clawShowing->updateGL();
}
