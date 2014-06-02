#include "object.h"
#include <QString>

object::object(QStringList params)
{
    attributes.insert("name", params[0]);
}
