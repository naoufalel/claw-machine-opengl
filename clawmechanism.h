#ifndef CLAWMECHANISM_H
#define CLAWMECHANISM_H

#include <QObject>

class ClawMechanism : public QObject
{
    Q_OBJECT
public:
    explicit ClawMechanism(QObject *parent = 0);

signals:

public slots:
};

#endif // CLAWMECHANISM_H