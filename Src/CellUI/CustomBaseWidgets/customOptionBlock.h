// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMOPTIONBLOCK_H
#define CUSTOMOPTIONBLOCK_H

#include "customFrame.h"

class customOptionBlockSector;
class QVBoxLayout;
class customLabel;

class customOptionBlock : public customFrame{
    Q_OBJECT
public:
    explicit customOptionBlock(QWidget *parent = nullptr, const QString& name = " ");

    void addSector(customOptionBlockSector *sector, bool addSplitterLine = true);
    void tidyItemTags();

protected:
    void addThemeTag(const QString &name);

    QVBoxLayout                     *mainLayout;
    QVBoxLayout                     *mainBlockLayout;
    customLabel                     *theme;
    customFrame                     *mainBlock;
    QList<customOptionBlockSector*> *sectorsList;

    int blockHeight = 0;
};

#endif // CUSTOMOPTIONBLOCK_H
