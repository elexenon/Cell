#include "CellSqlManager.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"
#include "CellProjectEntity.h"

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
        CELLSQLMANAGER_DEBUG << "Database::" << dbPath << "::Connect_Succeed." << endl;
    }
    else{
        CELLSQLMANAGER_DEBUG << "Database::" << dbPath << "::Connect_Failed::" << printErrorMsg() << endl;
        CELLSQLMANAGER_DEBUG << "Then create a new one as: " << dbPath << endl;
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
                        << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 2)))
                        << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 3)))
                        << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 4)));
        return currSqlTuple;
    }
    sqlite3_finalize(stmtHandle);
    return currSqlTuple;
}

bool CellSqlManager::insertProjectEntity(CellProjectEntity &entity)
{
    QString tmp = QString("INSERT INTO RecentPJ VALUES(") + "'" + entity.name()                          + "'" + ","
                                                          + "'" + entity.modifiedTime()                  + "'" + ","
                                                                + QString::number(entity.size())               + ","
                                                          + "'" + CellProjectEntity::getType(entity.type()) + "'" + ","
                                                          + "'" + entity.path()                          + "'" + ");";
    qDebug() << tmp;
    const char *sqlSentence = tmp.toLatin1().data();
    return execSql("Insert", sqlSentence);
}

const char* CellSqlManager::printErrorMsg()
{
    return sqlite3_errmsg(dbHandle);
}

bool CellSqlManager::execSql(const char *head, const char *sqlSentence, bool clearStmt, bool step)
{
    sqlResult = sqlite3_prepare_v2(dbHandle, sqlSentence, -1, &stmtHandle, nullptr);
    if(sqlResult == SQLITE_OK){
        CELLSQLMANAGER_DEBUG << head << "_Succeed" << endl;
    }else{
        CELLSQLMANAGER_DEBUG << head << "_Failed::" << printErrorMsg() << endl;
        sqlite3_finalize(stmtHandle);
        return false;
    }
    if(step)      sqlite3_step(stmtHandle);
    if(clearStmt) sqlite3_finalize(stmtHandle);
    return true;
}

bool CellSqlManager::tableExists(const char *tableName)
{
    const QString sqlSentence = CHAR2STR("SELECT COUNT(*) FROM sqlite_master WHERE type = 'table' AND name = '") + tableName + "'";
    if(execSql("Query_TableExists", sqlSentence.toLatin1().data(), false, false)){
        if(sqlite3_step(stmtHandle) == SQLITE_ROW){
            if(atoi(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 0))) == 0){
                CELLSQLMANAGER_DEBUG << "Table::" << tableName << "::Doesn't Exist." << endl;
                return false;
            }
        }
    }else{
        return false;
    }
    CELLSQLMANAGER_DEBUG << "Table::" << tableName << "::Exist." << endl;
    sqlite3_finalize(stmtHandle);
    return true;
}
