#ifndef CELLSQLMANAGER_H
#define CELLSQLMANAGER_H

class QStringList;
class sqlite3;
class sqlite3_stmt;
class CellProjectEntity;

class CellSqlManager{
public:
    explicit CellSqlManager();
    ~CellSqlManager();

    bool execSql(const char *head, const char *sqlSentence,
                 bool step = true, bool clearStmtHandle = true);
    //! Set the exsiting Sqlite3 database file path and open.
    //! If it not exists, create a new Sqlite3 database instead.
    bool setDbPath(const char* dbPath);
    //! Not using QList<QStandardItem> is because it aims to
    //! keep the Api as flexible as possible.
    const QStringList* fetchRecentPJ();
    //! Insert New Project Into Database.
    bool insertProjectEntity(CellProjectEntity &entity);

    inline
    bool createTable(const char *sqlSentence) { return execSql("Create_Table", sqlSentence); }

    bool removeTuple(const QString &tableName, const QString &mainKey, const QString &id);

    bool tableExists(const char *tableName);

    const char* printErrorMsg();

private:
    //! The Database Connection Object.
    sqlite3      *dbHandle;
    //! The Prepared Statement Object.
    sqlite3_stmt *stmtHandle;
    QStringList  *currSqlTuple;
    int           sqlResult;
};

#endif // CELLSQLMANAGER_H
