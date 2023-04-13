#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "IObserver.h"
#include "ISubject.h"
#include <set>
#include<QtMqtt/QMqttClient>
#include<QtMqtt/QMqttSubscription>
#include <memory>
#include "GeoDataWidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow,public ISubject
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent* event);

    void subscribe(IObserver* p);
    void unsubscribe(IObserver* p);
    void setstate(const QString& newName);
    void Notify();
    void registerwithmqtt();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    QMqttClient* m_clientPub ;
    //std::set<IObserver*> observers;
    QString geoFileName;
    Ui::MainWindow *ui;
    std::set<GeoDataWidget*> observers;
    //std::set<std::unique_ptr<MyWidget>> observers;
    QString GetInputFile();
};
#endif // MAINWINDOW_H

