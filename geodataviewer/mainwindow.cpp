#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qmessagebox.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QtDebug>
#include <QFileDialog>
#include<QtMqtt/QMqttClient>
#include <sstream>
#include <QTextEdit>
#include<QVBoxLayout>
#include "utils.h"
#include "GeoDataWidget.h"
#include "Graph_Widget.h"
#include "Stats_Widget.h"


GeoDataWidget* GetWidget(RENDER_STYLE style)
{
    if(style == RENDER_STYLE::GRAPHIC)
        return new Graph_Widget();
    else if(style == RENDER_STYLE::STATS)
        return new Stats_Widget();

    return nullptr;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() &~ Qt::WindowMaximizeButtonHint);

    ui->pushButton_3->hide();
    ui->lineEdit->hide();
    ui->radioButton_3->hide();
    ui->radioButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    //for(auto observer : observers)
     //   delete observer;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
}


void MainWindow::on_pushButton_clicked()
{
    static int viewerNum = 0;
    QString subscr_name = ui->lineEdit_2->text();

    RENDER_STYLE render_style = RENDER_STYLE::GRAPHIC;

    if(ui->radioButton->isChecked())
    {
        render_style = RENDER_STYLE::GRAPHIC;
    }
    else if(ui->radioButton_2->isChecked())
    {
        render_style = RENDER_STYLE::STATS;
    }

    GeoDataWidget*  subscr_widget = GetWidget(render_style);

    if(subscr_widget == nullptr)
        return;

    if(subscr_name.isEmpty())
    {
        subscr_name = "Viewer " + QString::number(viewerNum++);
    }
    //MyWidget* subscr_widget = new MyWidget(0,render_style);
    //std::unique_ptr<MyWidget> subscr_widget = std::unique_ptr<MyWidget>(new MyWidget(0,render_style));
    subscr_widget->setSubName(subscr_name);
    //subscr_widget->setrenderstype(render_style);
    ////widget2 = new MyWidget;
    subscribe(subscr_widget);
    //subscribe(widget2);

    subscr_widget->show();
    //widget2->show();


    subscr_widget->registerwithmqtt_subscriber();

    observers.insert(subscr_widget);
}


void MainWindow::on_pushButton_2_clicked()
{
    if(m_clientPub == nullptr)
    {
        display_error_message("Publisher must be connected to MTQQ Server before selecting Geo data file.");
        return;
    }
     QString p = GetInputFile();
     setstate(p);

     QMqttTopicName topic("consumer/in");
     QString payload = p;
     m_clientPub->publish(topic,payload.toUtf8(),0,true);
}

QString MainWindow::GetInputFile()
{
    QString file_name = QFileDialog::getOpenFileName(this,
        tr("Open Geo Json File"), "/home/jana", tr("Geo Json Files (*.json *.geojson)"));

    return file_name;
}

void MainWindow::subscribe(IObserver* p)
{
    //observers.insert(p);
}

void MainWindow::unsubscribe(IObserver* p)
{
    //observers.erase(p);
}

void MainWindow::setstate(const QString& newName)
{
    //to notify observers directly uncomment this code.
    //geoFileName = newName;
    //Notify();
}

void MainWindow::Notify()
{
    //to notify observers directly uncomment this code.
    //for(auto p: observers)
    //{
    //    p->update(geoFileName);
    //}
}

//UNUSED
void MainWindow::on_pushButton_3_clicked()
{
}

void MainWindow::registerwithmqtt()
{
    qint32 res = 0;
    m_clientPub = new QMqttClient();
    m_clientPub->setHostname("localhost");
    m_clientPub->setPort(1883);
    m_clientPub->setClientId("publisher");
    m_clientPub->setProtocolVersion(QMqttClient::ProtocolVersion::MQTT_5_0);

    QObject::connect(m_clientPub, &QMqttClient::stateChanged, [this](QMqttClient::ClientState state){
        if(state == QMqttClient::Disconnected)
            qDebug() << " State: Disconnected";
        else if(state == QMqttClient::Connecting)
            qDebug() << " State: Connecting";
        else if(state == QMqttClient::Connected)
        {
            QMessageBox msgBox;
            msgBox.setText("Publisher connected.");
            msgBox.exec();
            //QMqttTopicName topic("consumer/in");
            //QString payload = "hello from qt vw";
            //int res2 = m_client->publish(topic,payload.toUtf8(),0,true);
            //qDebug() << " State: Connected";
        }
    });

    QObject::connect(m_clientPub, &QMqttClient::errorChanged, [](QMqttClient::ClientError error){
         qDebug() << "error Mqtt: " << error;

     });

    m_clientPub->connectToHost();
}

// Publisher
void MainWindow::on_pushButton_4_clicked()
{
    //TODO: If clicked on second time, return.
     registerwithmqtt();
}

