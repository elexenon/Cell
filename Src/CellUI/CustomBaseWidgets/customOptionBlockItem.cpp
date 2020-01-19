// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customOptionBlockItem.h"
#include "customLabel.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QHBoxLayout>

customOptionBlockItem::customOptionBlockItem(QWidget *parent):
    QWidget(parent),
    mainLayout(new QHBoxLayout)
{
    setStyleSheet(CHAR2STR("background-color:transparent"));
    mainLayout->setContentsMargins(60, 0, 0, 0);
    mainLayout->setSpacing(20);

    setLayout(mainLayout);
}

void customOptionBlockItem::setTag(const QString &text)
{
    tagLen = text.length();
    tag = new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, this);
    tag->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);
    CellUiGlobal::setCustomTextLabel(tag, CHAR2STR("Microsoft YaHei UI Light"), 18, text);
    mainLayout->addWidget(tag);
}

void customOptionBlockItem::setOptionWidget(QWidget *widget)
{
    optionWidget = widget;
    optionWidget->setParent(this);
    mainLayout->addWidget(optionWidget);

    mainLayout->addStretch();
}

void customOptionBlockItem::setHint(const QString &text)
{
    hint = new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, this);
    hint->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);
    CellUiGlobal::setCustomTextLabel(hint, CHAR2STR("Microsoft YaHei UI Light"), 14, text+"。");
    mainLayout->addWidget(hint);
    mainLayout->addStretch();
}

void customOptionBlockItem::setMargins(int left, int top, int right, int bottom)
{
    mainLayout->setContentsMargins(left,top,right,bottom);
}

void customOptionBlockItem::setSpacing(int value)
{
    mainLayout->setSpacing(value);
}

const QMargins customOptionBlockItem::getMargins()
{
    return mainLayout->contentsMargins();
}

void customOptionBlockItem::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    tag->setColorScheme(mode);

    hint->setColorScheme(mode);
}
