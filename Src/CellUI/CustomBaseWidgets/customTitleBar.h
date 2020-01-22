// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
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

    void setText(const QString& text, const QColor& color = Qt::black);
    void setLeftMargin(int value);
    void setIcon(const QString& fileName, int iconWidth, int iconHeight);
    void setHeight(int value);
    void setFont(QFont& font, int size);
    void addWidget(QWidget *obj);
    void addLayout(QLayout *obj);

protected:
    //virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

    QHBoxLayout *mainLayout;
    customLabel *label_title;
    QLabel      *icon;

protected slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
};

#endif // CUSTOMTITLEBAR_H
