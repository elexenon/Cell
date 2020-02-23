// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CUSTOMTITLEBAR_H
#define CUSTOMTITLEBAR_H

#include "../CustomBaseWidgets/customFrame.h"

class customLabel;
class QLabel;
class QHBoxLayout;

class customTitleBar : public customFrame
{
    Q_OBJECT
public:
    explicit customTitleBar(QWidget *parent = nullptr);

    void setText(const QString& text, const CellVariant &color = Cell::CGL0);
    void setLeftMargin(int value);
    void setIcon(const QString& fileName, int iconWidth, int iconHeight);
    void setHeight(int value);
    void setFont(const QFont& font);
    void addWidget(QWidget *obj);
    void addLayout(QLayout *obj);

protected:
    //virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

    QHBoxLayout *mainLayout;
    customLabel *label_title;
    QLabel      *icon;

protected Q_SLOTS:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
};

#endif // CUSTOMTITLEBAR_H
