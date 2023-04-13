#ifndef GEODATAEXCEPTION_H
#define GEODATAEXCEPTION_H
#include "geodataaccessor_global.h"
#include <QString>

namespace GeoDataAccess_Lib
{
class GEODATAACCESSOR_EXPORT Geo_data_exception : public std::exception
{
private:
    const char* err_msg;
public:
    Geo_data_exception(const char* err);
    const char * what() const noexcept override;
};
}
#endif // GEODATAEXCEPTION_H
