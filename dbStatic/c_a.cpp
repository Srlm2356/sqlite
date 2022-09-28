#include "connection.h"
#include "db_library.h"

/*const QString SQL_Program =     " INNER JOIN programs ON programs.id = control_actions.program_id ";
const QString SQL_Param =       " LEFT JOIN control_action_params ON control_actions.id = control_action_params.ca_id ";*/
const QString SQLconst =        " SELECT * "
                                " FROM control_actions "
                                " INNER JOIN programs ON programs.id = control_actions.program_id "
                                " LEFT JOIN control_action_params ON control_actions.id = control_action_params.ca_id "
                                " LEFT JOIN control_action_param_types ON control_action_param_types.id = control_action_params.param_type_id "
                                " LEFT JOIN control_action_param_values ON control_action_params.id = control_action_param_values.ca_param_id ";
ControlActions Database::controlActionId(QString identifier)
{
    struct ControlActions id;
    id = {};
    setlocale(LC_CTYPE, "rus");
    if(!connection())
        qDebug() << "Что-то не так с бд";
    else{
        QSqlQuery q(SQLconst +
                    " WHERE "
                    " control_actions.identifier = '" + identifier + "' ");

        qDebug() << identifier << "\n";

        int i=0;
        QString params1, params2, param_id1, param_id2 ;

        while(q.next()){
            i++;

            id.eng_name.clear();
            id.identifier.clear();
            id.comment.clear();
            id.variable_param_len.clear();
            id.data_id.clear();

            id.identifier.append(q.value(q.record().indexOf("control_actions.identifier")).toString());
            id.data_id.append(q.value(q.record().indexOf("control_actions.data_id")).toString());
            id.eng_name.append(q.value(q.record().indexOf("eng_name")).toString());
            id.comment.append(q.value(q.record().indexOf("control_actions.comment")).toString());
            //id.variable_param_len.append(q.value(q.record().indexOf("variable_param_len")).toString());

            id.program.eng_name.clear();
            id.program.comment.clear();
            id.program.name.clear();

            id.program.name.append(q.value(q.record().indexOf("programs.name")).toString());
            id.program.eng_name.append(q.value(q.record().indexOf("programs.eng_name")).toString());
            id.program.comment.append(q.value(q.record().indexOf("programs.comment")).toString());

            params1 = (q.value(q.record().indexOf("control_action_params.eng_name")).toString());

            if(params1 != params2){;
                params2 = (q.value(q.record().indexOf("control_action_params.eng_name")).toString());
                id.param.order.append(q.value(q.record().indexOf("control_action_params.order")).toString());
                id.param.name.append(q.value(q.record().indexOf("control_action_params.name")).toString());
                id.param.eng_name.append(q.value(q.record().indexOf("control_action_params.eng_name")).toString());
                id.param.comment.append(q.value(q.record().indexOf("control_action_params.comment")).toString());
                id.param.min_value.append(q.value(q.record().indexOf("control_action_params.min_value")).toString());
                id.param.max_value.append(q.value(q.record().indexOf("control_action_params.max_value")).toString());
                id.param.unit.append(q.value(q.record().indexOf("control_action_params.unit")).toString());

                id.param.type_name.append(q.value(q.record().indexOf("control_action_param_types.name")).toString());
                id.param.type_eng_name.append(q.value(q.record().indexOf("control_action_param_types.eng_name")).toString());
            }

            id.param.param_id.append(q.value(q.record().indexOf("control_action_params.id")).toString());
            id.param.ca_param_id.append(q.value(q.record().indexOf("control_action_param_values.ca_param_id")).toString());
            id.param.param_value.append(q.value(q.record().indexOf("control_action_param_values.value")).toString());
            id.param.param_value_name.append(q.value(q.record().indexOf("control_action_param_values.eng_name")).toString());

        }
        if(id.identifier.isEmpty()){
            qDebug() << "Error: there is no such data in the database" << "\n";
        }
        else{
            qDebug() << "Идентификатор УВ " << id.identifier << "\n";
            qDebug() << "Номер УВ " << id.data_id;
            qDebug() << "Инженерное название УВ" << id.eng_name;
            qDebug() << "Комментарий разработчика к УВ " << id.comment << "\n";

            qDebug() << "Краткое имя программы" << id.program.name;
            qDebug() << "Инженерное название программы" << id.program.eng_name;
            qDebug() << "Комментарий разработчика к программе" << id.program.comment << "\n";

            for(int i=0; i!=id.param.eng_name.size(); i++){
                qDebug() << "Номер аргумента " << id.param.order[i] << " параметра УВ";
                qDebug() << "Краткое имя параметра " << i << " " << id.param.name[i];
                qDebug() << "Инж название параметра " << i << " " << id.param.eng_name[i];
                qDebug() << "Комментарий разработчика к параметру " << i << " " << id.param.comment[i];
                qDebug() << "Минимально возможное значение параметра " << i << " " << id.param.min_value[i];
                qDebug() << "Максимально возможное значение параметра " << i << " " << id.param.max_value[i];
                qDebug() << "Единица измерения параметра " << i << " " << id.param.unit[i];

                qDebug() << "Тип данных параметра " << i << " " << id.param.type_name[i];
                qDebug() << "Описание типа данных параметра " << i << " " << id.param.type_eng_name[i] << "\n";
            }
            for(int j=0; j!=id.param.param_value.size(); j++){
                param_id1 = id.param.param_id[j];
                if(param_id1 != param_id2){
                    param_id2 = id.param.param_id[j];
                    qDebug() << "-----------------------Значения параметра " <<  "-----------------------" << "\n";
                    qDebug() << "Само описываемое значение " << id.param.param_value[j];
                    qDebug() << "Физический смысл значения " << id.param.param_value_name[j];
                    qDebug() << "ID param = " << id.param.param_id[j];
                }
                else{
                    qDebug() << "Само описываемое значение " << id.param.param_value[j];
                    qDebug() << "Физический смысл значения " << id.param.param_value_name[j];
                    qDebug() << "ID param = " << id.param.param_id[j];
                }
            }
        }
    }
    return id;
}

QStringList Database::allIdentifier()
{
    //removeConnection();
    setlocale(LC_CTYPE, "rus");
    QStringList all_id;

    if(!connection())
        qDebug() << "Что-то не так с бд";
    else {
        QSqlQuery query("SELECT "
                        "   control_actions.identifier "
                        "FROM "
                        "   control_actions ");
        while(query.next()){
           all_id.append(query.value(query.record().indexOf("control_actions.identifier")).toString());
        }
    }
    return all_id;
}
