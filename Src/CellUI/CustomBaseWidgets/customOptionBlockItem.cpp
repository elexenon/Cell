// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "customOptionBlockItem.h"
#include "customLabel.h"
#include "../../CellCore/CellNamespace.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QHBoxLayout>

int customOptionBlockItem::TagTextSize = 17;

customOptionBlockItem::customOptionBlockItem(QWidget *parent, const QString& tag):
    QWidget(parent),
    mainLayout(new QHBoxLayout)
{
    setFixedHeight(50);
    setStyleSheet(CHAR2STR("background-color:transparent"));
    setLayout(mainLayout);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignVCenter);
    mainLayout->setContentsMargins(48, 0, 25, 0);
    mainLayout->setSpacing(20);

    if(tag != " ") setTag(tag);
}

void customOptionBlockItem::setTag(const QString &text){
    tagLen = text.length();
    tag = new customLabel(this);
    tag->setBrightDarkColor(Cell::CGL70, Cell::CGL255);
    CellUiGlobal::setCustomTextLabel(tag, CHAR2STR("Microsoft YaHei UI Light"), TagTextSize, text);
    mainLayout->addWidget(tag);

    CellWidgetGlobalInterface::_modules << tag;
}

void customOptionBlockItem::setOptionWidget(QWidget *widget){
    optionWidget = widget;
    optionWidget->setParent(this);
    mainLayout->addWidget(optionWidget);
    mainLayout->addStretch();
}

void customOptionBlockItem::setHint(const QString &text)
{
    hint = new customLabel(this);
    hint->setBrightDarkColor(Cell::CGL70, Cell::CGL255);
    CellUiGlobal::setCustomTextLabel(hint, CHAR2STR("Microsoft YaHei UI Light"), 13, text+"。");
    mainLayout->addWidget(hint);

    CellWidgetGlobalInterface::_modules << hint;
}

void customOptionBlockItem::setMargins(int left, int top, int right, int bottom){
    mainLayout->setContentsMargins(left,top,right,bottom);
}

void customOptionBlockItem::setMargin(customOptionBlockItem::MarginType direction, int value)
{
    auto tmp = mainLayout->contentsMargins();
    switch (direction) {
    case Left:
        tmp.setLeft(value);
        break;
    case Right:
        tmp.setRight(value);
        break;
    case Top:
        tmp.setTop(value);
        break;
    case Bottom:
        tmp.setBottom(value);
        break;
    }
    setContentsMargins(tmp);
}

void customOptionBlockItem::setSpacing(int value){
    mainLayout->setSpacing(value);
}

const QMargins customOptionBlockItem::getMargins() const{
    return mainLayout->contentsMargins();
}

void customOptionBlockItem::setColor(const QColor &color){
    CellWidgetGlobalInterface::setColor(color);
}

void customOptionBlockItem::changeToColor(const QColor &startColor, const QColor &targetColor, int duration){
    (void)startColor;
    (void)targetColor;
    (void)duration;
}

void customOptionBlockItem::setColorScheme(Cell::ColorScheme mode){
    CellWidgetGlobalInterface::setColorScheme(mode);
}
