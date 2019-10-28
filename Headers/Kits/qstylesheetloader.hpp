// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef QSTYLELOADER_H
#define QSTYLELOADER_H
#include <QFile>
class QStyleSheetLoader
{
public:
    explicit QStyleSheetLoader(const QString &DIR) // Must use absolute directory!
        :loader(new QFile)
        ,DIR(DIR)
    {}
    void setStyleSheetName(const QString &name){
        fileName = name;
    }
    const QString styleSheet() const{
        loader->setFileName(DIR + fileName);
        loader->open(QFile::ReadOnly);
        QString tmp = loader->readAll();
        loader->close();
        return tmp;
    }
    ~QStyleSheetLoader(){
        delete loader;
    }
private:
    QFile *loader;
    QString DIR;
    QString fileName;
};
#endif
