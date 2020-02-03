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
    tag(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, this))
{
    setLayout(mainLayout);

    mainLayout->setMargin(0);
    mainLayout->addWidget(tag);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    
    tag->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);
}

void ButtonWithText::Init(const QString &text, int fontSize)
{
    CellUiGlobal::setCustomTextLabel(tag, CHAR2STR("Microsoft YaHei UI Light"), fontSize, text);
}
