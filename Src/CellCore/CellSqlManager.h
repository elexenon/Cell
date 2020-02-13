#ifndef CELLSQLMANAGER_H
#define CELLSQLMANAGER_H
#define CELLSQLMANAGER_DEBUG (QTextStream(stdout) << "***CellSqlManager::")

class QStringList;
class sqlite3;
class sqlite3_stmt;
class CellProjectEntity;

class CellSqlManager{
public:
    explicit CellSqlManager();
    ~CellSqlManager();

    bool execSql(const char *head, const char *sqlSentence,
                 bool clearStmt = true, bool step = true);
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

    bool tableExists(const char *tableName);

    const char* printErrorMsg();

private:
    sqlite3      *dbHandle;
    sqlite3_stmt *stmtHandle;
    QStringList  *currSqlTuple;
    int           sqlResult;
};

#endif // CELLSQLMANAGER_H
