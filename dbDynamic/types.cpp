#include "connection.h"
#include "db_library.h"

const QString SQL_All_Images = " SELECT * "
                               " FROM images "
                               " LEFT JOIN image_sections ON images.id = image_sections.image_id "
                               " LEFT JOIN image_modules ON images.id = image_modules.image_id ";

Types Database::typesGlobalId(QString identifier)
{
    struct Types type;
    type = {};
    setlocale(LC_CTYPE, "rus");
    if(!connection())
        qDebug() << "Что-то не так с бд";
    else{
        QSqlQuery q(" SELECT * "
                    " FROM variables "
                    " LEFT JOIN types ON types.id = variables.type_id "
                    " WHERE "
                    " variables.name = '" + identifier + "' ");
        while(q.next()){
            type.variable_name.append(q.value(q.record().indexOf("variables.name")).toString());
            type.variable_location = -(q.value(q.record().indexOf("variables.location")).toInt());
            type.name.append(q.value(q.record().indexOf("types.name")).toString());
            type.number_name = (q.value(q.record().indexOf("types.id")).toInt());
            type.size8 = (q.value(q.record().indexOf("types.size8")).toInt());
            type.size1 = (q.value(q.record().indexOf("types.size1")).toInt());
            type.offset1 = (q.value(q.record().indexOf("types.offset1")).toInt());
        }

        if(type.variable_name.isEmpty()){
            qDebug() << "Error: there is no such data in the database" << "\n";
        }
        else{
            qDebug() << "Имя переменной " << type.variable_name;
            qDebug() << "Адрес данной переменной " << type.variable_location;
            qDebug() << "Имя типа " << type.name;
            qDebug() << "Идентификатор типа " << type.number_name;
            qDebug() << "Размер объекта данного типа в байтах " << type.size8;
            qDebug() << "Размер объекта данного типа в битах " << type.size1;
            qDebug() << "Битовый отступ " << type.offset1 << "\n";
        }
    }
    return type;
}
