#ifndef USER_H
#define USER_H

#include <QObject>
#include <vector>
#include <score.h>

using namespace std;

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = 0);
    void setUserName(string username){ this->username = username;}
    string getUserName(){ return this->username;}

signals:

public slots:

private:
    string username;
    vector<Score> score;


};

#endif // USER_H
