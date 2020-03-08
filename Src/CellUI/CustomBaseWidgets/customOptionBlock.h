// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CUSTOMOPTIONBLOCK_H
#define CUSTOMOPTIONBLOCK_H

#include "customFrame.h"

class customOptionBlockItem;
class QVBoxLayout;
class customLabel;

class customOptionBlock : public customFrame{
friend class customNavigator;
    Q_OBJECT
public:
    explicit customOptionBlock(QWidget *parent = nullptr, const QString& name = " ");

    void
    addItem(QWidget *optionWidget, const QString& hint, const QString& tag = " ",
            bool addSplitterLine = false);

    void
    addItem(customOptionBlockItem *item, bool addSplitterLine = false);

    void
    setMainBlockBrightDarkModeColor(const CellVariant b, const CellVariant d);

    void
    tidyItems(customOptionBlock *another = nullptr);

    inline int
    getItemTagMaxLen() { return itemTagMaxLen; }

protected:
    void
    addThemeTag(const QString &name);

    virtual void
    mouseEvent(QMouseEvent*);

    QVBoxLayout                     *mainLayout;
    QVBoxLayout                     *mainBlockLayout;
    QString                         _theme;
    customLabel                     *theme;
    customFrame                     *mainBlock;
    QList<customOptionBlockItem*>   *itemsList;

    int blockHeight = 0;
    int itemTagMaxLen = 0;

private:
    void
    _tidyItems(int value = -1);

Q_SIGNALS:
    void
    clicked(const QString&);
};

#endif // CUSTOMOPTIONBLOCK_H
