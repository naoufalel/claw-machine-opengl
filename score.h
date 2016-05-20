#ifndef SCORE_H
#define SCORE_H

#include <QObject>

using namespace std;


class Score : public QObject
{
    Q_OBJECT
public:
    explicit Score(QObject *parent = 0);

signals:

public slots:

private:
    string username;
    string time;
    int numberOfBalls;


};

#endif // SCORE_H
