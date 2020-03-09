// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CELLSETTINGS_H
#define CELLSETTINGS_H

class CellSettings{
public:
    enum SaveAttribute{
        Auto,
        AbateEffect,
        MultiInstance,
        onShowGuideDialog
    };
    virtual ~CellSettings() = default;
protected:
    virtual void
    write(SaveAttribute key, const QString &value) = 0;

    virtual void
    loadFile() = 0;

    virtual void
    saveFile() = 0;

    virtual void
    read(const QJsonObject&) = 0;
};

#endif // CELLSETTINGS_H
