// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMOPTIONBLOCKITEM_H
#define CUSTOMOPTIONBLOCKITEM_H

#include <QWidget>
#include "CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

class QHBoxLayout;
class customLabel;

class customOptionBlockItem : public QWidget, implements CellWidgetGlobalInterface{
friend class customOptionBlock;
    Q_OBJECT
public:
    explicit customOptionBlockItem(QWidget *parent = nullptr);

    inline
    int            getTagLen() { return tagLen; }
    void           setTag(const QString& text);
    void           setOptionWidget(QWidget* widget);
    void           setHint(const QString& text);
    void           setMargins(int left, int top, int right, int bottom);
    void           setSpacing(int value);
    const QMargins getMargins();

protected:
    inline
    virtual void setColor(const QColor &color) override { CellWidgetGlobalInterface::setColor(color); }

    QHBoxLayout *mainLayout;
    customLabel *tag;
    QWidget     *optionWidget;
    customLabel *hint;

    int tagLen;

public slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
};

#endif // CUSTOMOPTIONBLOCKITEM_H
