#ifndef CELLSQLMANAGER_H
#define CELLSQLMANAGER_H
#define CELLSQLMANAGER_HEADER (qDebug() << CHAR2STR("CellSqlManager::"))

class QStringList;
class sqlite3;
class sqlite3_stmt;

class CellSqlManager{
public:
    explicit CellSqlManager();
    ~CellSqlManager();
    //! Set the exsiting Sqlite3 database file path and open.
    //! If it not exists, create a new Sqlite3 database instead.
    bool               setDbPath(const char* dbPath);
    //! Not using QList<QStandardItem> is because it aims to
    //! keep the Api as flexible as possible.
    const QStringList* fetchRecentPJ();

private:
    sqlite3      *dbHandle;
    sqlite3_stmt *stmtHandle;
    QStringList  *currSqlTuple;
};

#endif // CELLSQLMANAGER_H
