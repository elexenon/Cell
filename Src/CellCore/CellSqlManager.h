// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CELLSQLMANAGER_H
#define CELLSQLMANAGER_H

class QStringList;
class QStandardItem;
class sqlite3;
class sqlite3_stmt;
class CellProjectEntity;

class CellSqlManager{
public:
    explicit CellSqlManager() noexcept = default;
    ~CellSqlManager() noexcept;

    //! Set the exsiting Sqlite3 database file path and open.
    //! If it not exists, create a new Sqlite3 database instead.
    bool
    setDataBase(const char* dbPath);
    //! If the fetching processing is on air, this function will
    //! return false.
    //! Once the fetching processing is done, this function will
    //! return true.
    bool
    fetchRecentPJRow(QList<QStandardItem*> *tuple); //TODO: const
    //! Insert New Cell Project
    //! Into Database.
    bool
    insertProjectEntity(CellProjectEntity &entity);
    //! Create a new table, users have to provide the CREATE
    //! SQL Sentence.
    inline bool
    createTable(const char *sqlSentence) { return execQuery(sqlSentence); }
    //! Remove a specific tuple by TABLENAME, MAINKEY, ID
    bool
    removeTuple(const QString &tableName, const QString &mainKey, const QString &id);
    //! Return a boolean value to judge if the table TABLENAME
    //! provided by user exists, if not, this function wil
    //! return false.
    bool
    tableExists(const char *tableName);

    bool
    tupleExists(const QString &tableName, const QString &mainKey, const QString &id);

    const char*
    printErrorMsg();

private:
    bool
    prepareStmt(const char *sqlSentence);
    //! Exec prepared Statement.
    //! This function only fits situations that the result of
    //! query is SQLITE_DONE.
    bool
    execQuery(const char *sqlSentence, bool clearStmt = true);

    void
    finalizeStmt();

    //! The Database Connection Object.
    sqlite3      *dbHandle = nullptr;
    //! The Prepared Statement Object.
    sqlite3_stmt *stmtHandle = nullptr;
    //! Stores Query Result.
    int           flag = 0;
};

#endif // CELLSQLMANAGER_H
