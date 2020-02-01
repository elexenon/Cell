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

class customOptionBlockItem;
class QVBoxLayout;
class customLabel;

class customOptionBlock : public customFrame{
    Q_OBJECT
public:
    explicit customOptionBlock(QWidget *parent = nullptr, const QString& name = " ");

    void addItem(QWidget *optionWidget, const QString& hint, const QString& tag = " ",
                 bool addSplitterLine = false);
    void addItem(customOptionBlockItem *item, bool addSplitterLine = false);
    void setMainBlockBrightDarkModeColor(const QColor &b, const QColor &d);
    void tidyItemTags();
protected:
    void addThemeTag(const QString &name);

    QVBoxLayout                     *mainLayout;
    QVBoxLayout                     *mainBlockLayout;
    customLabel                     *theme;
    customFrame                     *mainBlock;
    QList<customOptionBlockItem*>   *itemsList;

    int blockHeight = 0;
    int itemTagMaxLen = 0;
};

#endif // CUSTOMOPTIONBLOCK_H
