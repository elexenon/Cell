// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "../../CellCore/Kits/CellUtility.h"
#include "../CustomBaseWidgets/customListButton.h"
#include "../CustomBaseWidgets/customLabel.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QPropertyAnimation>

customListButton::customListButton(QWidget *parent, const QString &text) :
    customButton(customButton::CHECKABLE, parent)
  , mainLayout(new QHBoxLayout)
  , tag(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, this))
{
    tag->setText(text);
    Init();
}

void customListButton::Init()
{
    tag->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);   
    CellUiGlobal::setCustomTextLabel(tag, CHAR2STR("Microsoft YaHei UI Light"), 16);

    mainLayout->addWidget(tag);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(12, 0, 0, 0);

    setLayout(mainLayout);
}

void customListButton::setFont(const QFont &font)
{
    tag->setFont(font);
}

void customListButton::setMargins(int left, int top, int right, int buttom)
{
    mainLayout->setContentsMargins(left, top, right, buttom);
}

void customListButton::setText(QString &text)
{
    tag->setText(text);
}

void customListButton::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    customButton::setColorScheme(mode);
    tag->setColorScheme(mode);
}
