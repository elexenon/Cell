// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "ButtonWithText.h"
#include "customLabel.h"
#include "../../CellCore/CellNamespace.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QVBoxLayout>

ButtonWithText::ButtonWithText(customButton::Type type, QWidget *parent):
    customButton(type, parent),
    mainLayout(new QVBoxLayout(this)),
    tag(new customLabel(this))
{
    setLayout(mainLayout);
    setCursor(Qt::PointingHandCursor);

    mainLayout->setMargin(0);
    mainLayout->addWidget(tag);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    
    setTextColor(Cell::CGL70, Cell::CGL255);

    _modules << tag;
}

void ButtonWithText::setTextColor(const CellVariant &b, const CellVariant &d){
    tag->setBrightDarkColor(b, d);
}

void ButtonWithText::initModules(const QString &text, int fontSize)
{
    CellUiGlobal::setCustomTextLabel(tag, CHAR2STR("Microsoft YaHei UI Light"), fontSize, text);
}
