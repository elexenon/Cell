#ifndef CELLSQLMANAGER_H
#define CELLSQLMANAGER_H

class QStringList;
class QStandardItem;
class sqlite3;
class sqlite3_stmt;
class CellProjectEntity;

class CellSqlManager{
public:
    explicit CellSqlManager() = default;
    ~CellSqlManager();

    bool prepareStmt(const char *sqlSentence);
    //! Exec prepared Statement.
    //! This function only fits situations that the result of
    //! query is SQLITE_DONE.
    bool execQuery(const char *sqlSentence);
    //! Set the exsiting Sqlite3 database file path and open.
    //! If it not exists, create a new Sqlite3 database instead.
    bool setDataBase(const char* dbPath);
    //! If the fetching processing is on air, this function will
    //! return false.
    //! Once the fetching processing is done, this function will
    //! return true.
    bool fetchRecentPJRow(QList<QStandardItem*> *tuple); //TODO: const
    //! Insert New Project Into Database.
    bool insertProjectEntity(CellProjectEntity &entity);

    inline
    bool createTable(const char *sqlSentence) { return execQuery("Create_Table", sqlSentence); }

    bool removeTuple(const QString &tableName, const QString &mainKey, const QString &id);

    bool tableExists(const char *tableName);

    const char* printErrorMsg();

private:
    void finalizeStmt();

    //! The Database Connection Object.
    sqlite3      *dbHandle = nullptr;
    //! The Prepared Statement Object.
    sqlite3_stmt *stmtHandle = nullptr;
    //! Stores Query Result.
    int           flag = 0;
};

#endif // CELLSQLMANAGER_H
