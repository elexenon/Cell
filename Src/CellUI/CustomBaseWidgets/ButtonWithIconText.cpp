// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "ButtonWithIconText.h"
#include "customLabel.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QHBoxLayout>
#include <QLabel>

ButtonWithIconText::ButtonWithIconText(customButton::TYPE type, QWidget *parent):
    customButton(type, parent),
    mainLayout(new QHBoxLayout(this)),
    icon(new QLabel(this)),
    tag(new customLabel(this))
{
    setLayout(mainLayout);
    setCursor(Qt::PointingHandCursor);

    mainLayout->setContentsMargins(10, 0, 0, 0);
    mainLayout->setSpacing(8);
    mainLayout->addWidget(icon);
    mainLayout->addWidget(tag);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    
    tag->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);
}

void ButtonWithIconText::init(const QString& fileName, int iconWidth, int iconHeight, const QString& text, int fontSize)
{
    CellUiGlobal::setLabelPixmap(icon, fileName, iconWidth, iconHeight);
    CellUiGlobal::setCustomTextLabel(tag, CHAR2STR("Microsoft YaHei UI Light"), fontSize, text);
}
