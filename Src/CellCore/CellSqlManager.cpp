#include "CellSqlManager.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"
#include "CellProjectEntity.h"
#define FINALIZESTMT(arg) \
        sqlite3_finalize(arg); \
        arg = nullptr

#include <QDebug>
#include <sqlite3.h>
#include <QStringList>

CellSqlManager::CellSqlManager():
    dbHandle(nullptr),
    stmtHandle(nullptr),
    currSqlTuple(new QStringList)
{}

CellSqlManager::~CellSqlManager()
{
    sqlite3_close_v2(dbHandle);
    delete currSqlTuple;
}

bool CellSqlManager::setDbPath(const char *dbPath)
{
    sqlResult = sqlite3_open_v2(dbPath, &dbHandle, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE,
                                nullptr);
    if(SQLITE_OK == sqlResult){
#ifdef  CELL_DEBUG
        CELL_DEBUG("CellSqlManager") << "Database::" << dbPath << "::Connect_Succeed." << endl;
#endif
    }
    else{
#ifdef CELL_DEBUG
        CELL_DEBUG("CellSqlManager") << "Database::" << dbPath << "::Connect_Failed::" << printErrorMsg() << endl;
        CELL_DEBUG("CellSqlManager") << "Then_Create_A_New_One_As::" << dbPath << endl;
#endif
        return false;
    }
    return true;
}

const QStringList* CellSqlManager::fetchRecentPJ()
{
    currSqlTuple->clear();
    static bool recentPJFetched = false;
    if(!recentPJFetched){
        const char *sqlSentence = "SELECT * FROM RecentPJ;";
        if(execSql("ProjectEntity_Fetch", sqlSentence, false, false))
            recentPJFetched = true;
        else
            return currSqlTuple;
    }
    if(sqlite3_step(stmtHandle) == SQLITE_ROW){
        (*currSqlTuple) << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 0)))
                        << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 1)))
                        << QString::number(sqlite3_column_int(stmtHandle, 2))
                        << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 3)))
                        << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 4)));
        return currSqlTuple;
    }
    FINALIZESTMT(stmtHandle);
    return currSqlTuple;
}

bool CellSqlManager::insertProjectEntity(CellProjectEntity &entity)
{
    QString tmp = QString::fromUtf8("INSERT INTO RecentPJ VALUES(") + "'" + entity.name()                          + "'" + ","
                                                                    + "'" + entity.modifiedTime()                  + "'" + ","
                                                                          + QString::number(entity.size())               + ","
                                                                    + "'" + CellProjectEntity::getType(entity.type()) + "'" + ","
                                                                    + "'" + entity.path()                          + "'" + ");";
    QByteArray byteArray = tmp.toUtf8();
    char *sqlSentence = byteArray.data();
    return execSql("Insert", sqlSentence);
}

bool CellSqlManager::removeTuple(const QString &tableName, const QString &mainKey, const QString &id)
{
    QString tmp = CHAR2STR("DELETE FROM ") + tableName + " WHERE " + mainKey + " = '" + id + "';";
    QByteArray byteArray = tmp.toUtf8();
    const char *sqlSentence = byteArray.data();
    return execSql("Remove", sqlSentence);
}

const char* CellSqlManager::printErrorMsg()
{
    return sqlite3_errmsg(dbHandle);
}

bool CellSqlManager::execSql(const char *head, const char *sqlSentence,
                             bool step, bool clearStmtHandle)
{
    // Check if the sqlSentence is valid.
    sqlResult = sqlite3_prepare_v2(dbHandle, sqlSentence, -1, &stmtHandle, nullptr);
    if(sqlResult == SQLITE_OK){
#ifdef  CELL_DEBUG
        CELL_DEBUG("CellSqlManager") << "Valid_" << head << "_Sentence::["
                                     << QString::fromUtf8(sqlSentence) << "]" << endl;
#endif
    }else{
#ifdef  CELL_DEBUG
        CELL_DEBUG("CellSqlManager") << "Invalid_" << head << "_Sentence::["
                                     << QString::fromUtf8(sqlSentence) << "]::" << printErrorMsg() << endl;
#endif
        FINALIZESTMT(stmtHandle);
        return false;
    }
    if(step){
        if(sqlite3_step(stmtHandle) == SQLITE_DONE)
#ifdef      CELL_DEBUG
            CELL_DEBUG("CellSqlManager") << "Query::[" << sqlSentence << "]::Done." << endl;
#endif
        else{
#ifdef      CELL_DEBUG
            CELL_DEBUG("CellSqlManager") << "Query::[" << sqlSentence << "]::Failed." << printErrorMsg() << endl;
#endif
            return false;
        }
    }
    if(clearStmtHandle) FINALIZESTMT(stmtHandle);
    return true;
}

bool CellSqlManager::tableExists(const char *tableName)
{
    const QString sqlSentence = CHAR2STR("SELECT COUNT(*) FROM sqlite_master WHERE type = 'table' AND name = '") + tableName + "'";
    QByteArray byteArray = sqlSentence.toLatin1();
    if(execSql("Query_TableExists", byteArray.data(), false, false)){
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
    FINALIZESTMT(stmtHandle);
    return true;
}
