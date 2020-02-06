#include "CellSqlManager.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

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
    // Check if the open operation of database if valid.
    int ret = sqlite3_open(dbPath, &dbHandle);
    if(SQLITE_OK == ret)
        CELLSQLMANAGER_HEADER << CHAR2STR("Database::") + dbPath + CHAR2STR("::Connect Succeed.");
    else if(SQLITE_ERROR == ret){
        CELLSQLMANAGER_HEADER << CHAR2STR("Database::") + dbPath + CHAR2STR("::Connect Failed.");
        return false;
    }
    return true;
}

const QStringList* CellSqlManager::fetchRecentPJ()
{
    currSqlTuple->clear();
    static bool recentPJFetched = false;
    if(!recentPJFetched){
        const char *sqlSentence = "SELECT NAME, MODIFIED_TIME, SIZE, PATH, TYPE FROM RECENT_PROJECT;";
        int ret = sqlite3_prepare_v2(dbHandle, sqlSentence, -1, &stmtHandle, nullptr);
        if(SQLITE_OK == ret) {
            recentPJFetched = true;
            CELLSQLMANAGER_HEADER << CHAR2STR("Valid Sentence.");
        }
        else{
            CELLSQLMANAGER_HEADER << CHAR2STR("Invalid Sentence.");
            // If Sql Sentense Is Invalid, The Control Flow Will End Up Here.
            return currSqlTuple;
        }
    }
    if(sqlite3_step(stmtHandle) == SQLITE_ROW){
        (*currSqlTuple) << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 0)))
                        << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 1)))
                        << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 2)))
                        << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 3)))
                        << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 4)));
        return currSqlTuple;
    }
    CELLSQLMANAGER_HEADER << CHAR2STR("Recent Projects Fetching Done.");
    sqlite3_finalize(stmtHandle);
    return currSqlTuple;
}
