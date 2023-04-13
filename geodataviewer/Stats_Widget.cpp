#include "Stats_Widget.h"
#include <QPainter>

void Stats_Widget::render(QPainter& painter,
                                            const GeoDataAccess_Lib::Geo_data_accessor& geo_accessor)
{
    render_stats(painter,geo_accessor.get_as_stats());
};

void Stats_Widget::render_stats(QPainter& textPainter,const std::vector<QString>& vecStatLines)
{
    textPainter.setFont(QFont("Times", 10, QFont::Bold,true));

    constexpr int x = 20;
    constexpr int y = 30;
    constexpr int factor = 2;
    int index = 1;

    for (const auto &line : vecStatLines)
    {
        textPainter.drawText(QPoint(x, y*index), line);
        ++index;
    }
}
