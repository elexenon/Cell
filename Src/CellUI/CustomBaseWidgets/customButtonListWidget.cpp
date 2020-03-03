// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "../CustomBaseWidgets/customButtonListWidget.h"
#include "../CustomBaseWidgets/customListButton.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../../CellCore/Kits/CellUtility.h"
#include "../../CellCore/CellNamespace.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>

customButtonListWidget::customButtonListWidget(QWidget *parent) :
    customFrame(customFrame::Regular, parent)
  , mainLayout(new QVBoxLayout(this))
  , buttons(new QList<customListButton*>)
  , btnGroup(new QButtonGroup(this))
{
    init();
    setEventConnections();
}

void customButtonListWidget::setButtonsBrightDarkModeColor(const CellVariant &b, const CellVariant &d)
{
    for(auto & e : *buttons)
        e->setBrightDarkModeColor(b, d);
}

void customButtonListWidget::addButton(const QString &text, const CellVariant &b, const CellVariant &d, int index)
{
    if(index == -1)
        index = buttonIndex++;

    customListButton *btn = new customListButton(this, text);
    btn->setBrightModeCheckedColor(b);
    btn->setDarkModeCheckedColor(d);

    buttons->append(btn);
    btnGroup->addButton(btn, index);
    mainLayout->addWidget(btn);
}

const customListButton* customButtonListWidget::getButton(int index) const
{
    return buttons->at(index);
}

void customButtonListWidget::setButtonSize(int width, int height)
{
    for(auto & e : *buttons)
        e->setFixedSize(width, height);
    setFixedWidth(width);
}

void customButtonListWidget::setBtnFontPixelSize(int size)
{
    QFont font(CHAR2STR("Microsoft YaHei UI Light"));
    font.setPixelSize(size);
    for(auto & e : *buttons)
        e->setFont(font);
}

void customButtonListWidget::setMargins(int left, int top, int right, int buttom)
{
    mainLayout->setContentsMargins(left, top, right, buttom);
}

void customButtonListWidget::setSpacing(int spacing)
{
    mainLayout->setSpacing(spacing);
}

void customButtonListWidget::clickButton(int index) const
{
    buttons->at(index)->click();
}

void customButtonListWidget::setButtonCheckable(int index, bool value)
{
    auto e = buttons->at(index);
    e->setCheckable(value);
}

void customButtonListWidget::setExlusive(bool value)
{
    btnGroup->setExclusive(value);
}

void customButtonListWidget::setEventConnections()
{
    connect(btnGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [=](int id){
        emit clicked(id);
    });
}

void customButtonListWidget::addThemeHead(const QString& theme)
{
    label_theme = new customLabel(this);
    CellUiGlobal::setCustomTextLabel(label_theme, CHAR2STR("Microsoft YaHei UI"), 15, theme);
    label_theme->setBrightDarkModeColor(Cell::CGL70, Cell::CGL255);
    line_splitter = CellUiGlobal::getLine(Cell::LineType::HLine);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label_theme);
    layout->addStretch();
    layout->setContentsMargins(12, 0, 0, 0);

    mainLayout->addLayout(layout);
    mainLayout->addWidget(line_splitter);
}

void customButtonListWidget::init()
{
    mainLayout->setMargin(0);
    mainLayout->setSpacing(3);
    setLayout(mainLayout);
    btnGroup->setExclusive(true);
}

void customButtonListWidget::setColorScheme(Cell::ColorScheme mode)
{
    customFrame::setColorScheme(mode);
    if(label_theme!=nullptr)
        label_theme->setColorScheme(mode);
    for(auto & e : *buttons)
        e->setColorScheme(mode);
}
