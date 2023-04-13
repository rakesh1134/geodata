#include "ISubject.h"
#include <set>
#include <QString>
#include <IObserver.h>

class Subject : public ISubject
{
    public:

    Subject():geoFileName(""){}

    ~Subject(){}

    void subscribe(IObserver* p)
    {
        observers.insert(p);
    }

    void unsubscribe(IObserver* p)
    {
        observers.erase(p);
    }

    void setstate(const QString& newName)
    {
        geoFileName = newName;
        Notify();
    }
    void Notify()
    {
        for(auto p: observers)
        {
            p->update(geoFileName);
        }
    }

private:
    std::set<IObserver*> observers;
    QString geoFileName;
};
