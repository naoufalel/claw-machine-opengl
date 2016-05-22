#ifndef SCORE_H
#define SCORE_H

#include <QObject>
#include <QWidget>

using namespace std;


class Score : public QWidget
{
    Q_OBJECT
public:
    explicit Score(QWidget *parent = 0);

signals:

public slots:

private:
    string username;
    string time;
    int numberOfBalls;


};

#endif // SCORE_H
