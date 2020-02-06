// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include "customFrame.h"

class QHBoxLayout;
class customLabel;
class ButtonWithIcon;
class customOptionBlock;
class customOptionBlockItem;

class customComboBox : public customFrame{
    Q_OBJECT
public:
    explicit customComboBox(const QString& state, QWidget *parent = nullptr);
    void     setOptionBlockParent(QWidget* parent);
    void     addItem(customOptionBlockItem *item,  bool addSplitterLine = false);
    void     tidyItemTags() const;
    void     setOptionBlockStartEndPos(const QPoint &posS, const QPoint &posE);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

    QPoint                         optionBlockStartPos;
    QPoint                         optionBlockEndPos;
    customLabel                   *currState;
    ButtonWithIcon                *trigger;
    customOptionBlock             *optionBlock;
    QHBoxLayout                   *mainLayout;
    QList<customOptionBlockItem*> *itemsList;

};

#endif // CUSTOMCOMBOBOX_H
