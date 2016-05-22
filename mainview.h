#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>

#include <user.h>
#include <camerainteraction.h>
#include <clawinteraction.h>

namespace Ui {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();
    float coordX,coordY;

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void showCamera();
    void vXMove();
    void animate();


private slots:

    void on_startGame_clicked();

    void on_showScores_clicked();

    void on_moveBall_clicked();

private:
    Ui::MainView *ui;
    QTimer *timer;
    QTimer *aTimer;


    User *user;
    Score *scores;
    CameraInteraction *camera;
//    ClawInteraction *claw;

    int hitStartCounter=0;
    bool isGameStarted;

};

#endif // MAINVIEW_H
