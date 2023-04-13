#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <QString>

class IObserver
{
    public:
    virtual ~IObserver(){}
    virtual void update(const QString& s)= 0;
};

#endif // IOBSERVER_H
