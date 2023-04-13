#ifndef ISUBJECT_H
#define ISUBJECT_H

class IObserver;

class ISubject
{
    public:
    ISubject(){}
    virtual ~ISubject(){}
    virtual void subscribe(IObserver*)=0;
    virtual void unsubscribe(IObserver*)=0;

    virtual void Notify()=0;

    virtual void registerwithmqtt() = 0;
};
#endif // ISUBJECT_H
