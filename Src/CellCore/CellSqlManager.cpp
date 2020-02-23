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
#ifdef CELL_DEBUG
       CELL_DEBUG("CellSqlManager") << "Database::Connection::Closed." << endl;
#endif
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

bool CellSqlManager::fetchRecentPJRow(QList<QStandardItem*> *tuple)
{
    tuple->clear();
    static bool fetchQuerySucceed = false;
    static QStringList nonExistsTuples;
    if(!fetchQuerySucceed){
        const char *sqlSentence = "SELECT * FROM RecentPJ;";
        if(prepareStmt(sqlSentence)){
            fetchQuerySucceed = true;
#ifdef CELL_DEBUG
    CELL_DEBUG("CellSqlManager") << "Start fetching tuples from table \"RecentPJ\"." << endl;
#endif
        }
        else{
            finalizeStmt();
            return false;
        }
    }

    flag = sqlite3_step(stmtHandle);
    QStringList strTuple;
    if(flag == SQLITE_ROW){
        strTuple << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 0)))
                 << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 1)))
                 << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 2)))
                 << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 3)));
        QString PJPath = strTuple.at(CellProjectEntity::Path) + CHAR2STR("/") +
                         strTuple.at(CellProjectEntity::Name) + CHAR2STR(".workshop");
        if(!QFileInfo(PJPath).isFile()){
#ifdef      CELL_DEBUG
            CELL_DEBUG("CellSqlManager") << CHAR2STR("Project::[") << PJPath << "]::Doesn't_Exists." << endl;
#endif
            nonExistsTuples.append(strTuple.at(CellProjectEntity::Name));
            return true;
        }
        for(auto & e : strTuple)
            tuple->append(new QStandardItem(e));
    }
    else if(flag == SQLITE_DONE){
#ifdef  CELL_DEBUG
        CELL_DEBUG("CellSqlManager") << "No more tuples in table \"RecentPJ\"." << endl;
#endif
        finalizeStmt();   
        if(!nonExistsTuples.isEmpty())
            for(auto & e : nonExistsTuples)
                removeTuple("RecentPJ", "Name", e);
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

bool CellSqlManager::prepareStmt(const char *sqlSentence)
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
                                     << "]::Succeed." << endl;
#endif
    return true;
}

bool CellSqlManager::execQuery(const char *sqlSentence, bool clearStmt)
{
    if(!prepareStmt(sqlSentence))
        return false;

    flag = sqlite3_step(stmtHandle);
    if(flag != SQLITE_DONE){
#ifdef  CELL_DEBUG
        CELL_DEBUG("CellSqlManager") << "Execute::[" << QString::fromUtf8(sqlSentence) << "]::Failed::" << printErrorMsg() << endl;
#endif
        finalizeStmt();
        return false;
    }
#ifdef CELL_DEBUG
       CELL_DEBUG("CellSqlManager") << "Execute::[" << QString::fromUtf8(sqlSentence) << "]::Succeed." << endl;
#endif
    if(clearStmt) finalizeStmt();
    return true;
}

bool CellSqlManager::tableExists(const char *tableName)
{
    const QString tmp = CHAR2STR("SELECT COUNT(*) FROM sqlite_master WHERE type = 'table' AND name = '") + tableName + "';";
    QByteArray sqlSentence = tmp.toLatin1();
    if(prepareStmt(sqlSentence.data())){
        flag = sqlite3_step(stmtHandle);
        if(flag == SQLITE_ROW){
            int column = atoi(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 0)));
            if(column == 0){
#ifdef          CELL_DEBUG
                CELL_DEBUG("CellSqlManager") << "Table::" << tableName << "::Doesn't Exist." << endl;
#endif
                finalizeStmt();
                return false;
            }
        }
    }else{
        finalizeStmt();
        return false;
    }
#ifdef CELL_DEBUG
       CELL_DEBUG("CellSqlManager") << "Table::" << tableName << "::Exists." << endl;
#endif
    finalizeStmt();
    return true;
}

bool CellSqlManager::tupleExists(const QString &tableName, const QString &mainKey, const QString &id)
{
    QString tmp = CHAR2STR("SELECT COUNT(*) FROM ") + tableName + " WHERE " + mainKey + " = '" + id + "';";
    QByteArray byteArray = tmp.toUtf8();
    const char *sqlSentence = byteArray.data();
    if(prepareStmt(sqlSentence)){
        flag = sqlite3_step(stmtHandle);
        if(flag == SQLITE_ROW){
            int column = atoi(reinterpret_cast<const char*>(sqlite3_column_text(stmtHandle, 0)));
            if(column == 0){
#ifdef          CELL_DEBUG
                CELL_DEBUG("CellSqlManager") << "Tuple::" << id << "::Doesn't Exist." << endl;
#endif
                finalizeStmt();
                return false;
            }
        }
    }else{
        finalizeStmt();
        return false;
    }
#ifdef CELL_DEBUG
       CELL_DEBUG("CellSqlManager") << "Tuple::" << id << "::Exists." << endl;
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
