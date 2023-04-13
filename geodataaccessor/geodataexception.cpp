#include "geodataexception.h"

namespace GeoDataAccess_Lib
{
    Geo_data_exception::Geo_data_exception(const char* msg):err_msg(msg)
    {

    }

    const char * Geo_data_exception::what() const noexcept
    {
        return err_msg;
    }
}
