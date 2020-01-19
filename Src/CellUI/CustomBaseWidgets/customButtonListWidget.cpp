// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "../CustomBaseWidgets/customButtonListWidget.h"
#include "../CustomBaseWidgets/customListButton.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>

customButtonListWidget::customButtonListWidget(QWidget *parent) :
    customFrame(CellUiConst::QSS_CUSTOMFRAME, parent)
  , mainLayout(new QVBoxLayout(this))
  , buttons(new QList<customListButton*>)
  , btnGroup(new QButtonGroup(this))
{
    Init();
}

void customButtonListWidget::addButton(const QString &text, const QColor& c1, const QColor& c2, const QColor& c3, const QColor& c4)
{
    customListButton *btn = new customListButton(this, text);
    btn->setBrightModeCheckedUncheckedColor(c1,c2);
    btn->setDarkModeCheckedUncheckedColor(c3,c4);
    btn->setCheckable(true);

    buttons->append(btn);
    btnGroup->addButton(btn);
    mainLayout->addWidget(btn);

    setColor(c2);

    if(!buttons->first()->isChecked())
        buttons->first()->setChecked(true);
}

const customListButton* customButtonListWidget::getButton(int index)
{
    return buttons->at(index);
}

void customButtonListWidget::setButtonSize(int width, int height)
{
    for(auto & e : *buttons)
        e->setFixedSize(width, height);
    setFixedWidth(width);
}

void customButtonListWidget::setFont(const QFont &font)
{
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

void customButtonListWidget::clickButton(int index)
{
    buttons->at(index)->click();
}

void customButtonListWidget::setButtonCheckable(int index, bool value)
{
    auto e = buttons->at(index);
    e->setCheckable(value);
}

void customButtonListWidget::addThemeHead(const QString& theme)
{
    label_theme = new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, this);
    CellUiGlobal::setCustomTextLabel(label_theme, CHAR2STR("Microsoft YaHei UI"), 15, theme);
    label_theme->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);
    line_splitter = CellUiGlobal::getLine(CellUiGlobal::LINE_TYPE::HLine);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label_theme);
    layout->addStretch();
    layout->setContentsMargins(12, 0, 0, 0);

    mainLayout->addLayout(layout);
    mainLayout->addWidget(line_splitter);
}

void customButtonListWidget::Init()
{
    mainLayout->setMargin(0);
    mainLayout->setSpacing(3);
    setLayout(mainLayout);
    btnGroup->setExclusive(true);
}

void customButtonListWidget::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    customFrame::setColorScheme(mode);
    if(label_theme!=nullptr)
        label_theme->setColorScheme(mode);
    for(auto & e : *buttons)
        e->setColorScheme(mode);
}
