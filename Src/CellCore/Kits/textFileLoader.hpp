// This Module Declares A Class That Aims to Load StyleSheets From Local Files.
//
// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This File May Be Used Under The Terms Of The GNU General Public License
// version 3.0 As Published By The Free Software Foundation And Appearing In
// The File LICENSE Included In The Packaging Of This File.
#ifndef QSTYLELOADER_H
#define QSTYLELOADER_H
#include <QFile>

class StyleSheetLoader
{
public:
    explicit StyleSheetLoader(const QString &DIR) // Must use an absolute directory!
        :loader(new QFile)
        ,DIR(DIR)
    {}
    inline
    void setStyleSheetName(const QString &name){
        fileName = name;
    }
    inline
    const QString styleSheet() const{
        loader->setFileName(DIR + fileName);
        loader->open(QFile::ReadOnly);
        QString tmp = loader->readAll();
        loader->close();
        return tmp;
    }
    ~StyleSheetLoader(){
        delete loader;
    }
private:
    QFile *loader;
    QString DIR;
    QString fileName;
};
#endif
