#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QTimer>


#include <user.h>
#include <camerainteraction.h>

namespace Ui {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

public slots:
    void showCamera();

private slots:

    void on_startGame_clicked();

private:
    Ui::MainView *ui;
    QTimer *timer;

    int hitStartCounter=0;
    bool isGameStarted;

    User *user;
    CameraInteraction *camera;


};

#endif // MAINVIEW_H
