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

    void  addThemeHead(const QString& theme = "theme");
    void  addButton(const QString &text, const QColor &b, const QColor &d, int index = -1);
    void  setButtonsBrightDarkModeColor(const QColor &b, const QColor &d);
    const customListButton* getButton(int index = 0) const;
    void  setButtonSize(int width, int height);
    void  setBtnFontPixelSize(int size);
    void  setMargins(int left = 0, int top = 0, int right = 0, int buttom = 0);
    void  setSpacing(int spacing);
    void  clickButton(int index) const;
    void  setButtonCheckable(int index, bool value);
    void  setExlusive(bool value = true);
    virtual void setEventConnections() override;

    inline
    const QList<customListButton*>* getButtons() { return buttons; }

private:
    void init();

    customLabel              *label_theme = nullptr;
    QFrame                   *line_splitter;
    QVBoxLayout              *mainLayout;
    QList<customListButton*> *buttons;
    QButtonGroup             *btnGroup;

    int buttonIndex = 0;

signals:
    void clicked(int id);

private Q_SLOTS:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
    inline
    void btnGroupClicked(int id) { emit clicked(id); }
};

#endif // CUSTOMBUTTONLISTWIDGET_H
