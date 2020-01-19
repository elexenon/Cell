// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMOPTIONSECTOR_H
#define CUSTOMOPTIONSECTOR_H

#include <QWidget>
#include "../../CellCore/Kits/CellGlobalMacros.h"
#include "CellWidgetGlobalInterface.h"

class QVBoxLayout;
class customOptionBlockItem;

class customOptionBlockSector : public QWidget, implements CellWidgetGlobalInterface{
friend class customOptionBlock;
    Q_OBJECT
public:
    explicit customOptionBlockSector(QWidget *parent = nullptr);

    void addItem(customOptionBlockItem *item, bool over = false);
    void adjustItemMargins();
    void setMargins(int left, int top, int right, int bottom);

protected:
    inline
    virtual void setColor(const QColor &color) override { CellWidgetGlobalInterface::setColor(color); }

    QVBoxLayout                   *mainLayout;
    QList<customOptionBlockItem*> *itemsList;

    int itemTagMaxLen = 0;

protected slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
};

#endif // CUSTOMOPTIONSECTOR_H
