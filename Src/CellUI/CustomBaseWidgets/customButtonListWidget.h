// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CUSTOMBUTTONLISTWIDGET_H
#define CUSTOMBUTTONLISTWIDGET_H

#include "customFrame.h"
#include "../../CellCore/CellNamespace.h"

class customListButton;
class QVBoxLayout;
class QButtonGroup;
class customLabel;

class customButtonListWidget : public customFrame{
    Q_OBJECT
public:
    explicit customButtonListWidget(QWidget *parent = nullptr);

    void  addThemeHead(const QString& theme = "theme");
    void  addButton(const QString &text, const CellVariant &b, const CellVariant &d, int index = -1);
    void  setButtonsBrightDarkModeColor(const CellVariant &b, const CellVariant &d);
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

public Q_SLOTS:
    virtual void setColorScheme(Cell::ColorScheme mode) override;
};

#endif // CUSTOMBUTTONLISTWIDGET_H
