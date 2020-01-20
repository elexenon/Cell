// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMBUTTONLISTWIDGET_H
#define CUSTOMBUTTONLISTWIDGET_H

#include "customFrame.h"
#include "../../CellCore/Kits/CellUtility.h" // COLOR_SCHEME

class customListButton;
class QVBoxLayout;
class QButtonGroup;
class customLabel;

class customButtonListWidget : public customFrame{
    Q_OBJECT
public:
    explicit customButtonListWidget(QWidget *parent = nullptr);

    void  setButtonsBrightDarkModeColor(const QColor &b, const QColor &d);
    void  addButton(const QString &text, const QColor &b, const QColor &d);
    const customListButton* getButton(int index = 0);
    void  setButtonSize(int width, int height);
    void  setBtnFontPixelSize(int size);
    void  setMargins(int left = 0, int top = 0, int right = 0, int buttom = 0);
    void  setSpacing(int spacing);
    void  clickButton(int index);
    void  setButtonCheckable(int index, bool value);
    void  addThemeHead(const QString& theme = "theme");

private:
    void Init();

    customLabel              *label_theme = nullptr;
    QFrame                   *line_splitter;
    QVBoxLayout              *mainLayout;
    QList<customListButton*> *buttons;
    QButtonGroup             *btnGroup;

private slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
};

#endif // CUSTOMBUTTONLISTWIDGET_H
