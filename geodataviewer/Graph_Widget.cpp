#include "Graph_Widget.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QtDebug>
#include <sstream>
#include <utils.h>

enum class GEO_FEATURE_TYPE{Point,LineString,Polygon,MultiPoint,MultiLineString,MultiPolygon,None};

void Graph_Widget::render(QPainter& painter,
                          const GeoDataAccess_Lib::Geo_data_accessor& geo_accessor)
{
    render_graph(painter,geo_accessor.get_json_doc().object());
}

void Graph_Widget ::render_graph(QPainter& painter,const QJsonObject& jsonObj)
{
    try
    {
        painter.translate(width()/ 2, height() / 2);
        painter.scale(2,2);
        painter.rotate(270);
        QString geomName;
        if (jsonObj.contains("features") && jsonObj["features"].isArray())
        {
            QJsonArray jsonArray =  jsonObj["features"].toArray();

            for (const QJsonValue &v : jsonArray)
            {
                QJsonObject levelObject = v.toObject();
                if(levelObject.contains("properties"))
                {
                    QJsonObject jsonProps = levelObject["properties"].toObject();
                    QJsonValue stateName = jsonProps.value("name");

                    if(levelObject.contains("geometry") && levelObject["geometry"].isObject())
                    {
                        QJsonObject geoMetryObject = levelObject["geometry"].toObject();

                        //bool bIsMultiPoly = false;
                        GEO_FEATURE_TYPE featType = GEO_FEATURE_TYPE::None;
                        if(geoMetryObject.contains("type") && geoMetryObject["type"].isString())
                        {
                            geomName = geoMetryObject["type"].toString();
                            if(geomName == "Point")
                                featType = GEO_FEATURE_TYPE::Point;
                            else if(geomName == "LineString")
                                featType = GEO_FEATURE_TYPE::LineString;
                            else if(geomName == "Polygon")
                                featType = GEO_FEATURE_TYPE::Polygon;
                            else if(geomName == "MultiPoint")
                                featType = GEO_FEATURE_TYPE::MultiPoint;
                            else if(geomName == "MultiLineString")
                                featType = GEO_FEATURE_TYPE::MultiLineString;
                            else if(geomName == "MultiPolygon")
                                featType = GEO_FEATURE_TYPE::MultiPolygon;
                            else
                                return;

                        }
                        if(geoMetryObject.contains("coordinates") && geoMetryObject["coordinates"].isArray())
                        {
                            if(featType == GEO_FEATURE_TYPE::Point)
                            {
                                QJsonArray point = geoMetryObject["coordinates"].toArray();
                                float p = point[0].toDouble();
                                float q = point[1].toDouble();
                                QPoint qp(q,p);
                                painter.drawPoint(qp);
                            }
                            else if(featType == GEO_FEATURE_TYPE::MultiPoint)
                            {
                                QJsonArray jsonCoordinates = geoMetryObject["coordinates"].toArray();
                                for (const QJsonValue &coordinate : jsonCoordinates)
                                {
                                    QJsonArray coordinate1 =  coordinate.toArray();
                                    int index = 0;
                                    for (const QJsonValue &coordinate11 : coordinate1)
                                    {
                                        QJsonArray coorArray =   coordinate11.toArray();
                                        if(coorArray.size()== 2)
                                        {
                                            float p = coorArray[0].toDouble();
                                            float q = coorArray[1].toDouble();
                                            QPoint qp(q,p);
                                            painter.drawPoint(q,p);
                                        }
                                    }
                                }
                            }
                            else if(featType == GEO_FEATURE_TYPE::Polygon || featType == GEO_FEATURE_TYPE::LineString)
                            {
                                QJsonArray jsonCoordinates = geoMetryObject["coordinates"].toArray();
                                for (const QJsonValue &coordinate : jsonCoordinates)
                                {

                                    QJsonArray coordinate1 =  coordinate.toArray();
                                    QPointF* points = new QPointF[coordinate1.size()];
                                    int index = 0;
                                    for (const QJsonValue &coordinate11 : coordinate1)
                                    {
                                        QJsonArray coorArray =   coordinate11.toArray();
                                        if(coorArray.size()== 2)
                                        {

                                            float p = coorArray[0].toDouble();
                                            float q = coorArray[1].toDouble();

                                            //qInfo() <<p<<","<<q<<"\n";
                                            points[index] = QPointF(q,p);
                                            ++index;
                                            //painter.drawPoint(p,q);

                                        }
                                    }
                                    if(featType == GEO_FEATURE_TYPE::Polygon)
                                    {
                                        painter.drawPolygon(points,coordinate1.size());
                                    }
                                    else
                                    {
                                        painter.drawLines(points,coordinate1.size());
                                    }
                                    delete [] points;
                                }
                            }
                            else if(featType == GEO_FEATURE_TYPE::MultiPolygon || featType == GEO_FEATURE_TYPE::MultiLineString)
                            {
                                QJsonArray jsonCoordinates = geoMetryObject["coordinates"].toArray();
                                for (const QJsonValue &coordinate : jsonCoordinates)
                                {

                                    QJsonArray coordinate1 =  coordinate.toArray();

                                    for (const QJsonValue &coordinate11 : coordinate1)
                                    {
                                        QJsonArray coorArray =   coordinate11.toArray();

                                        QPointF* points = new QPointF[coorArray.size()];
                                        int index = 0;
                                        for (const QJsonValue &coordinate22 : coorArray)
                                        {
                                            QJsonArray coorArray2 =   coordinate22.toArray();

                                            if(coorArray2.size()== 2)
                                            {

                                                float p = coorArray2[0].toDouble();
                                                float q = coorArray2[1].toDouble();
                                                points[index] = QPointF(q,p);
                                                ++index;
                                            } //if(coorArray2.size()== 2)
                                        }
                                        if(featType == GEO_FEATURE_TYPE::MultiPolygon)
                                            painter.drawPolygon(points,coorArray.size());
                                        else
                                            painter.drawLines(points,coorArray.size());
                                        delete [] points;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    catch(std::exception& ex)
    {
        //
    }
    catch(...)
    {
        //display_error_message("Unspecified Error during rendering.");
    }
}
