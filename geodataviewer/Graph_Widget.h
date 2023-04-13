#ifndef GRAPH_WIDGET_H
#define GRAPH_WIDGET_H

#include "GeoDataWidget.h"
#include <QPainter>
#include "/home/rakesh/geodataaccessor/geodataaccessor.h"
#include "/home/rakesh/geodataaccessor/geodataexception.h"

using namespace GeoDataAccess_Lib;

class Graph_Widget : public GeoDataWidget
{
public:
    virtual void render(QPainter&,const GeoDataAccess_Lib::Geo_data_accessor&) override;
private:
    void render_graph(QPainter&,const QJsonObject&);
};

#endif // GRAPH_WIDGET_H
