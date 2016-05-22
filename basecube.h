#ifndef BASECUBE_H
#define BASECUBE_H

#include <QObject>

class BaseCube : public QObject
{
    Q_OBJECT
public:
    explicit BaseCube(QObject *parent = 0);

signals:

public slots:
};

#endif // BASECUBE_H