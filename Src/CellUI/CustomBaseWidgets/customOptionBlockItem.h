// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
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
enum MARGIN_DIRE{
    _LEFT, _RIGHT, _TOP, _BOTTOM
};
static int TagTextSize;
    explicit customOptionBlockItem(QWidget *parent = nullptr, const QString& tag = " ");

    inline
    int            getTagLen() { return tagLen; }
    void           setTag(const QString& text);
    void           setOptionWidget(QWidget* widget);
    void           setHint(const QString& text);
    void           setMargins(int left, int top, int right, int bottom);
    void           setMargin(MARGIN_DIRE direction, int margin);
    void           setSpacing(int value);
    const QMargins getMargins();

protected:
    virtual void setColor(const QColor &color) override;
    virtual void setBaseQss(const QString &qss) override;
    virtual void changeToColor(const QColor &startColor, const QColor &targetColor, int duration) override;

    QHBoxLayout *mainLayout;
    customLabel *tag;
    QWidget     *optionWidget;
    customLabel *hint;

    int itemHeight = 0;
    int tagLen     = 0;

public Q_SLOTS:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
};

#endif // CUSTOMOPTIONBLOCKITEM_H
