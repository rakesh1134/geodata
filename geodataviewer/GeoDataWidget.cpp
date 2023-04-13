#include "GeoDataWidget.h"
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
#include <QPainter>
#include "utils.h"

GeoDataWidget::GeoDataWidget(QWidget *parent,RENDER_STYLE s) : QWidget(parent)
{
}

void GeoDataWidget::update(const QString& s)
{
    geodata_file = s;
    repaint();
}

void GeoDataWidget::setSubName(const QString& s)
{
    subscriber_name = s;
    setWindowTitle(subscriber_name);
}

void GeoDataWidget::registerwithmqtt_subscriber()
{
    qint32 res = 0;
    m_clientSub = new QMqttClient();
    m_clientSub->setHostname("localhost");
    m_clientSub->setPort(1883);
    m_clientSub->setClientId(subscriber_name);
    m_clientSub->setProtocolVersion(QMqttClient::ProtocolVersion::MQTT_5_0);

    QObject::connect(m_clientSub, &QMqttClient::stateChanged, [this](QMqttClient::ClientState state){
        if(state == QMqttClient::Disconnected)
            qDebug() << " State: Disconnected";
        else if(state == QMqttClient::Connecting)
            qDebug() << " State: Connecting";
        else if(state == QMqttClient::Connected)
        {
            QMessageBox msgBox;
            msgBox.setText("Subscriber connected.");
            msgBox.exec();
            QMqttTopicFilter f("consumer/in");
            subscription = m_clientSub->subscribe(f,0);
                if (!subscription) {
                    QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
                    return;
                }
                else
                {
                     QObject::connect(subscription, &QMqttSubscription::messageReceived, this,&GeoDataWidget::updateMessage);
                }
        }
    });

    QObject::connect(m_clientSub, &QMqttClient::errorChanged, [](QMqttClient::ClientError error){
         qDebug() << "error Mqtt: " << error;

     });

    m_clientSub->connectToHost();
}

void GeoDataWidget::updateMessage(const QMqttMessage &msg)
{
    //Read message from MQTT
    QString geoFileName = msg.payload();
    //Update the view
    update(geoFileName);
}

void GeoDataWidget::paintEvent(QPaintEvent *event)
{
    if(geodata_file.isEmpty())
        return;

    QPainter textPainter(this);
    try
    {
        GeoDataAccess_Lib::Geo_data_accessor geo_accessor;
        geo_accessor.load_file(geodata_file);
        render(textPainter,geo_accessor);
    }
    catch(GeoDataAccess_Lib::Geo_data_exception& e)
    {
        display_error_message(e.what());
    }
}
