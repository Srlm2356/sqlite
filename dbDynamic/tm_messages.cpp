#include "connection.h"
#include "db_library.h"

QString dPath;
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

QString Database::dbPath(const QString &path){
    dPath = path;
    return dPath;
}

TmMessages Database::tmFrameMessages(QString number_tm, QString number_message)
{
    struct TmMessages tm;
    tm = {};
    setlocale(LC_CTYPE, "rus");
    if(!connection())
         qDebug() << "Что-то не так с бд";
    else{
         QSqlQuery query(" SELECT * "
                         " FROM tm_frame_messages "
                         " LEFT JOIN tm_frames ON tm_frames.id = tm_frame_messages.frame_id "
                         " LEFT JOIN tm_frame_message_classes ON tm_frame_message_classes.id =  tm_frame_messages.class_id "
                         " WHERE tm_frame_messages.frame_id = '" + number_tm + "' "
                         " AND tm_frame_messages.number = '" + number_message + "' ");
         while(query.next()){
            tm.frame_id.append(query.value(query.record().indexOf("tm_frame_messages.frame_id")).toString());
            tm.identifier.append(query.value(query.record().indexOf("tm_frame_messages.identifier")).toString());
            tm.number_messages = (query.value(query.record().indexOf("tm_frame_messages.number")).toInt());
            tm.eng_name_messages.append(query.value(query.record().indexOf("tm_frame_messages.eng_name")).toString());
            tm.number_classes = (query.value(query.record().indexOf("tm_frame_message_classes.id")).toInt());
            tm.name_classes.append(query.value(query.record().indexOf("tm_frame_message_classes.name")).toString());
            tm.eng_name_classes.append(query.value(query.record().indexOf("tm_frame_message_classes.eng_name")).toString());
         }

         if(tm.frame_id.isEmpty()){
             qDebug() << "Error: there is no such data in the database" << "\n";
         }
         else {
             qDebug() << "Номер ТМ кадра: " << tm.frame_id;
             qDebug() << "Идентификатор сообщения: " << tm.identifier;
             qDebug() << "Номер сообщения: " << tm.number_messages;
             qDebug() << "Инженерное название сообщения: " << tm.eng_name_messages;
             qDebug() << "Номер класса аварийности: " << tm.number_classes;
             qDebug() << "Имя класса: " << tm.name_classes;
             qDebug() << "Описание класса: " << tm.eng_name_classes << "\n";
         }
     }
     return tm;
}
