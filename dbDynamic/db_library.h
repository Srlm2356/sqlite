#ifndef DB_LIBRARY_H
#define DB_LIBRARY_H

#include <QString>
#include <QStringList>
#include "dbDyn_global.h"

extern DBDYN_EXPORT QString dPath;

/** * @brief Базовая информация для всех переменных и глобальных идентификаторов, описываемых в БД*/
struct DBDYN_EXPORT Types
{
    QString name; // Имя типа
    int number_name; // Номер типа
    int size8; // Размер объекта данного типа, единица измерения − байт.
    int size1; // Размер объекта данного типа, единица измерения − бит.
    int offset1; // Битовый отступ до значения объекта типа внутри области, ограниченной параметром size8.
    QString name_metatypes; // Имя метатипа
    QString variable_name; // Имя переменной
    int variable_location; // Адрес данной переменной. Имеется в виду глобальный адрес в оперативной памяти ЦВМ
} ;

struct program
{
    QStringList name; // Идентификатор функции, которая исполняет УВ данной программы, например, CFNC_V_TLM_EXECUTE_CA
    QStringList eng_name; // Инженерное название программы, например, "Управление выдачей телеметрических кадров"
    QStringList comment; // Комментарий разработчика к программе
} ;
struct params
{
    QStringList param_id;
    QStringList ca_param_id;
public:
    QStringList order; // Номер аргуента
    QStringList name;
    QStringList eng_name; // Инженерное название программы
    QStringList comment; // Комментарий разработчика
    QStringList min_value; // Минимально возможное значение параметра (может иметь значение NULL)
    QStringList max_value; // Максимально возможное значение параметра (может иметь значение NULL)
    QStringList unit; // Единица измерения параметра
    QStringList param_value; // Само описываемое значение параметра
    QStringList param_value_name; // Физический смысл значения
    QStringList type_name;
    QStringList type_eng_name;
}  ;

/** * @brief Структура управляющих воздействий. */
struct DBDYN_EXPORT ControlActions
{
public:
    QString identifier; // Идентификатор УВ для операторов
    QString data_id; // Номер УВ. Исп как номер данных при формировании МЦИ
    QString eng_name; // Инж название УВ
    QString comment; // Комментарий к УВ
    QString variable_param_len; // Поле, показывающее имеет ли это УВ нефиксир-ое кол-во параметров

    /** * @brief Структура атрибутов программных компонентов ПО.*/
    struct program program;
    /** * @brief Структура описания параметров УВ.*/
    struct params param;
} ;

/** * @brief Содержит собщения и классы сообщений, передаваемые посредством ТМ кадров; */
struct DBDYN_EXPORT TmMessages
{
    QString frame_id; // Номер ТМ кадра
    QString identifier; // Иденитификатор сообщения
    int number_messages; // Номер сообщения
    QString eng_name_messages; // Инж название сообщения
    int number_classes; // Номер класса сообщения
    QString name_classes; // Имя класса
    QString eng_name_classes; // Краткое описание
};

/** * @brief  Класс. Выводит список параметров и программных компонентов конкретного УВ.*/
class DBDYN_EXPORT Database
{
public:
    /** * @brief  Путь к БД*/
    static QString dbPath(const QString &path);
    /** * @brief  Общая информация УВ*/
    static ControlActions controlActionId(QString identifier);
    /** * @brief Полный список УВ*/
    static QStringList allIdentifier();
    /** * @brief Получение данных по аварийным сообщениям */
    static TmMessages tmFrameMessages(QString number_tm, QString number_message);
    /** * Получение информации по переменным из БД */
    static Types typesGlobalId(QString identifier);
};

#endif // DB_LIBRARY_H

