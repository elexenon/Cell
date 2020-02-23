// This Module Declares A Class That Aims to Load StyleSheets From Local Files.
//
// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef QSTYLELOADER_H
#define QSTYLELOADER_H
#include <QFile>

class textFileLoader
{
public:
    explicit textFileLoader(const QString &DIR) // Must Use An Absolute Directory.
        :loader(new QFile)
        ,DIR(DIR)
    {}
    textFileLoader(const textFileLoader&) = delete;
    textFileLoader& operator=(const textFileLoader&) = delete;
    inline
    static textFileLoader& instance(const QString &DIR){
        static textFileLoader mInstance(DIR);
        return mInstance;
    }
    inline
    void setFileName(const QString &name){
        fileName = name;
    }
    inline
    const QString content() const{
        loader->setFileName(DIR + fileName);
        loader->open(QFile::ReadOnly);
        QString tmp = loader->readAll();
        loader->close();
        return tmp;
    }
    ~textFileLoader(){
        delete loader;
    }
private:
    QFile *loader;
    QString DIR;
    QString fileName;
};
#endif
