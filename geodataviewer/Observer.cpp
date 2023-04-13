#include "IObserver.h"


class Observer : public IObserver
{
    QString name;
public:
    Observer(const QString& n):name(n){}
    void update(const QString& s)
    {

    }
};
