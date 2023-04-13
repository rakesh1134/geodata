#ifndef STATS_WIDGET_H
#define STATS_WIDGET_H

#include "GeoDataWidget.h"
#include <QPainter>
#include "/home/rakesh/geodataaccessor/geodataaccessor.h"
#include "/home/rakesh/geodataaccessor/geodataexception.h"

using namespace GeoDataAccess_Lib;

class Stats_Widget : public GeoDataWidget
{
public:
    virtual void render(QPainter&,const GeoDataAccess_Lib::Geo_data_accessor&) override;
private:
    void render_stats(QPainter&,const std::vector<QString>&);
};


#endif // STATS_WIDGET_H
