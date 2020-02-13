// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "ButtonWithText.h"
#include "customLabel.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QVBoxLayout>

ButtonWithText::ButtonWithText(customButton::TYPE type, QWidget *parent):
    customButton(type, parent),
    mainLayout(new QVBoxLayout(this)),
    tag(new customLabel(this))
{
    setLayout(mainLayout);
    setCursor(Qt::PointingHandCursor);

    mainLayout->setMargin(0);
    mainLayout->addWidget(tag);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    
    setTextColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);
}

void ButtonWithText::setTextColor(const QColor &b, const QColor &d)
{
    tag->setBrightDarkModeColor(b, d);
}

void ButtonWithText::init(const QString &text, int fontSize)
{
    CellUiGlobal::setCustomTextLabel(tag, CHAR2STR("Microsoft YaHei UI Light"), fontSize, text);
}
