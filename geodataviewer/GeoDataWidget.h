#ifndef GEODATAWIDGET_H
#define GEODATAWIDGET_H

#include <QPushButton>
#include <QMouseEvent>
#include <QWidget>
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
#include "/home/rakesh/geodataaccessor/geodataaccessor.h"
#include "/home/rakesh/geodataaccessor/geodataexception.h"
#include "IObserver.h"

using namespace GeoDataAccess_Lib;

enum class RENDER_STYLE{GRAPHIC,STATS/*,TEXT*/};

class GeoDataWidget : public QWidget,public IObserver
{
private:
    QString subscriber_name;
    QString geodata_file;
    QMqttClient* m_clientSub;
    QMqttSubscription *subscription;
public:
    explicit GeoDataWidget(QWidget *parent=0,RENDER_STYLE s=RENDER_STYLE::GRAPHIC);
    GeoDataWidget(const GeoDataWidget& other) = delete;
    GeoDataWidget& operator=(const GeoDataWidget& other) = delete;
    ~GeoDataWidget() = default;
    void update(const QString& s) override;
    void registerwithmqtt_subscriber();
    void setSubName(const QString& s);
    void updateMessage(const QMqttMessage &msg);
    void setrenderstype(RENDER_STYLE s);

    virtual void render(QPainter&,const GeoDataAccess_Lib::Geo_data_accessor&) = 0;

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};


#endif // GEODATAWIDGET_H
