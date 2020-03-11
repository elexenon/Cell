// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CUSTOMOPTIONBLOCK_H
#define CUSTOMOPTIONBLOCK_H

#include "optionBlockBase.h"

class customOptionBlockItem;

class customOptionBlock : public optionBlockBase{
friend class customNavigator;
    Q_OBJECT
public:
    explicit customOptionBlock(const QString& name, QWidget *parent = nullptr);

    void
    addItem(QWidget *optionWidget, const QString& tag, const QString& hint,
            bool addSplitterLine = false);

    void
    addItem(customOptionBlockItem *item, bool addSplitterLine = false);

    void
    setMainBlockBrightDarkModeColor(const CellVariant &b, const CellVariant &d);

    void
    tidyItems(customOptionBlock *another = nullptr);

    inline int
    getItemTagMaxLen() { return itemTagMaxLen; }

protected:
    QVBoxLayout                   *mainBlockLayout;
    customFrame                   *mainBlock;
    QList<customOptionBlockItem*> *itemsList;

    int blockHeight = 0;
    int itemTagMaxLen = std::numeric_limits<int>::lowest();

private:
    virtual void
    init() override;

    void
    _tidyItems(int value = -1);

    void
    _addSplitterLine(bool add = true);
};

#endif // CUSTOMOPTIONBLOCK_H
