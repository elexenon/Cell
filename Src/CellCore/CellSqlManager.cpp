#include "CellSqlManager.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"
#include "CellProjectEntity.h"
#include <QDebug>
#include <sqlite3.h>
#include <QList>
#include <QStringList>

CellSqlManager::~CellSqlManager()
{
    sqlite3_close_v2(dbHandle);
}

bool CellSqlManager::setDataBase(const char *dbPath)
{
    flag = sqlite3_open(dbPath, &dbHandle);
    if(SQLITE_OK != flag){
#ifdef  CELL_DEBUG
        CELL_DEBUG("CellSqlManager") << "Database::" << dbPath << "::Connect_Failed::" << printErrorMsg() << endl;
        CELL_DEBUG("CellSqlManager") << "Created A New Database As::" << dbPath << endl;
#endif
        return false;
    }
#ifdef  CELL_DEBUG
        CELL_DEBUG("CellSqlManager") << "Database::" << dbPath << "::Connect_Succeed." << endl;
#endif
    return true;
}

bool fetchRecentPJRow(QList<QStandardItem*> *tuple)
{
    tuple->clear();
    static bool fetchQuerySucceed = false;
    if(!fetchQuerySucceed){
        const char *sqlSentence = "SELECT * FROM RecentPJ;";
        if(prepareStmt(sqlSentence))
            fetchQuerySucceed = true;
        else
            return false;
    }

    flag = sqlite3_step(stmtHandle);
    QStringList strTuple;
    if(flag == SQLITE_ROW){
        strTuple << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 0)))
                 << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 1)))
                 << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 2)))
                 << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 3)));
        QString PJPath = strTuple->at(CellProjectEntity::_PATH) + CHAR2STR("/") + 
                         strTuple->at(CellProjectEntity::_NAME) + CHAR2STR(".workshop");    
        if(!QFileInfo(PJPath).isFile()){
#ifdef      CELL_DEBUG
            CELL_DEBUG("CellSqlManager") << CHAR2STR("Project::[") << PJPath << "]::Doesn't_Exists." << endl;
#endif
            recentPJSql.removeTuple("RecentPJ", "Name", strTuple->at(CellProjectEntity::_NAME));
            return true;
        }
        for(auto & e : strTuple) tuple.append(new QStandardItem(e));
    }else if(flag == SQLITE_DONE){
        finalizeStmt();
        return false;
    }
    return true;
}

bool CellSqlManager::insertProjectEntity(CellProjectEntity &entity)
{
    QString tmp = QString::fromUtf8("INSERT INTO RecentPJ VALUES(") + "'" + entity.name()                          + "'" + ","
                                                                    + "'" + entity.modifiedTime()                  + "'" + ","
                                                                    + "'" + CellProjectEntity::getType(entity.type()) + "'" + ","
                                                                    + "'" + entity.path()                          + "'" + ");";
    QByteArray byteArray = tmp.toUtf8();
    char *sqlSentence = byteArray.data();
    return execQuery(sqlSentence);
}

bool CellSqlManager::removeTuple(const QString &tableName, const QString &mainKey, const QString &id)
{
    QString tmp = CHAR2STR("DELETE FROM ") + tableName + " WHERE " + mainKey + " = '" + id + "';";
    QByteArray byteArray = tmp.toUtf8();
    const char *sqlSentence = byteArray.data();
    return execQuery(sqlSentence);
}

const char* CellSqlManager::printErrorMsg()
{
    return sqlite3_errmsg(dbHandle);
}

bool prepareStmt(const char *sqlSentence)
{
    flag = sqlite3_prepare_v2(dbHandle, sqlSentence, -1, &stmtHandle, nullptr);
    if(flag != SQLITE_OK){
#ifdef  CELL_DEBUG
        CELL_DEBUG("CellSqlManager") << "Prepared Statement For" << "::[" << QString::fromUtf8(sqlSentence) 
                                     << "]::Failed::" << printErrorMsg() << endl;
#endif
        finalizeStmt();
        return false;
    }
#ifdef  CELL_DEBUG
        CELL_DEBUG("CellSqlManager") << "Prepared Statement For" << "::[" << QString::fromUtf8(sqlSentence) 
                                     << "]::Succeed::" << endl;
#endif
    return true;
}

bool CellSqlManager::execQuery(const char *sqlSentence)
{
    if(!prepareStmt(head, sqlSentence)) 
        return false;

    flag = sqlite3_step(stmtHandle);
    if(flag != SQLITE_DONE){
#ifdef  CELL_DEBUG
        CELL_DEBUG("CellSqlManager") << "Execute::[" << sqlSentence << "]::Failed::" << printErrorMsg() << endl;
#endif
        finalizeStmt();
        return false;
    }
#ifdef CELL_DEBUG
       CELL_DEBUG("CellSqlManager") << "Execute::[" << sqlSentence << "]::Succeed." << endl;
#endif
    finalizeStmt();
    return true;
}

bool CellSqlManager::tableExists(const char *tableName)
{
    const QString sqlSentence = CHAR2STR("SELECT COUNT(*) FROM sqlite_master WHERE type = 'table' AND name = '") + tableName + "'";
    QByteArray byteArray = sqlSentence.toLatin1();
    if(execQuery("Query_TableExists", byteArray.data(), false, false)){
        int res = sqlite3_step(stmtHandle);
        qDebug() << res;
        if(res == SQLITE_ROW){
            int column = atoi(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 0)));
            qDebug() << "columns:" << column;
            if(column == 0){
#ifdef          CELL_DEBUG
                CELL_DEBUG("CellSqlManager") << "Table::" << tableName << "::Doesn't Exist." << endl;
#endif
                return false;
            }
        }
        qDebug() << printErrorMsg();
    }else{
        return false;
    }
#ifdef CELL_DEBUG
       CELL_DEBUG("CellSqlManager") << "Table::" << tableName << "::Exists." << endl;
#endif
    finalizeStmt();
    return true;
}

void CellSqlManager::finalizeStmt()
{
    if(stmtHandle){
        sqlite3_finalize(stmtHandle);
        stmtHandle = nullptr;
    }
}
