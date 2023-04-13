#ifndef GEODATAACCESSOR_H
#define GEODATAACCESSOR_H
#include <QJsonDocument>
#include "geodataaccessor_global.h"
#include <vector>

namespace GeoDataAccess_Lib
{
    class GEODATAACCESSOR_EXPORT Geo_data_accessor
    {
    private:
        QJsonDocument json_doc;
    public:
        Geo_data_accessor( );
        bool load_file(const QString& geo_json_file );
        QString get_as_text();
        std::vector<QString> get_as_stats() const;
        QJsonDocument get_json_doc() const;
    };
}

#endif // GEODATAACCESSOR_H
