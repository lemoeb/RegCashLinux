#ifndef DBUTILITY_H
#define DBUTILITY_H

#include <QtSql>


class dbUtility
{
public:
    dbUtility();
    void chiudiScontrino(float);

private:
    QSqlDatabase db = QSqlDatabase::database();

};

#endif // DBUTILITY_H
