#include "geodataaccessor.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "geodataexception.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

namespace GeoDataAccess_Lib
{
    Geo_data_accessor::Geo_data_accessor()
    {
    }

    QJsonDocument Geo_data_accessor::get_json_doc() const
    {
        return json_doc;
    }

    bool Geo_data_accessor::load_file(const QString& geoDataFile )
    {
        if(geoDataFile.isEmpty())
        {
            throw Geo_data_exception("Invalid Geo data file.");
        }
        QFile loadFile(geoDataFile);
        if(!loadFile.exists())
        {
            throw Geo_data_exception("Geo data file does not exist.");
        }
        bool result = false;
        if(loadFile.open(QIODevice::ReadOnly) == true)
        {
            QByteArray saveData = loadFile.readAll();
            if(saveData.isEmpty() == false)
            {
                QJsonDocument tempdoc = QJsonDocument::fromJson(saveData);
                if(tempdoc.isNull() == false)
                {
                    json_doc = tempdoc;
                }
            }
        }
        return result;
    }

    QString Geo_data_accessor::get_as_text()
    {
        QByteArray jsonBytes = json_doc.toJson(QJsonDocument::Compact);
        if(jsonBytes.isEmpty())
        {
            throw Geo_data_exception("Can not read Jeo Json ```````data.");
        }
        return QString(jsonBytes);
    }

    std::vector<QString> Geo_data_accessor::get_as_stats() const
    {
        std::vector<QString> statsLines;
        std::map<QString,quint32> featureTypeToCount;

        QJsonObject jsonObj = json_doc.object();

        QString geomName;

        if (jsonObj.contains("features") == true &&  jsonObj["features"].isArray() == true)
        {
            QJsonArray jsonArray =  jsonObj["features"].toArray();

            for (const QJsonValue &v : jsonArray)
            {
                QJsonObject levelObject = v.toObject();

                if(levelObject.contains("geometry") && levelObject["geometry"].isObject())
                {
                    QJsonObject geoMetryObject = levelObject["geometry"].toObject();

                    if(geoMetryObject.contains("type") && geoMetryObject["type"].isString())
                    {
                        geomName = geoMetryObject["type"].toString();
                        featureTypeToCount[geomName]++;
                    }
                }
            }
        }

        QString featureLine;
        quint32 featureCount= 0;

        std::map<QString,quint32>::const_iterator iter = featureTypeToCount.begin();

        while(iter != featureTypeToCount.end())
        {
            featureLine = iter->first;
            featureCount = iter->second;

            featureLine.append(" : " +  QString::number(featureCount));
            statsLines.push_back(featureLine);
            ++iter;
        }
        return statsLines;
    }
}
