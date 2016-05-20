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

private:
    Ui::MainView *ui;
    User *user;
    CameraInteraction *camera;
    QTimer *timer;

};

#endif // MAINVIEW_H
