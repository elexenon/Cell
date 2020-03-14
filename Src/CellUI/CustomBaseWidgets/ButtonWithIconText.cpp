// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "ButtonWithIconText.h"
#include "customLabel.h"
#include "../../CellCore/Kits/CellUtility.h" // CellUiGlobal

#include <QHBoxLayout>
#include <QLabel>

ButtonWithIconText::ButtonWithIconText(customButton::ButtonType type, QWidget *parent):
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

    tag->setBrightDarkColor(Cell::CGL70, Cell::CGL255);

    CellWidgetGlobalInterface::_modules << tag;
}

void ButtonWithIconText::initModules(const QString& fileName, int iconWidth, int iconHeight, const QString& text, int fontSize)
{
    CellUiGlobal::setLabelPixmap(icon, fileName, iconWidth, iconHeight);
    CellUiGlobal::setCustomTextLabel(tag, CHAR2STR("Microsoft YaHei UI Light"), fontSize, text);
}
