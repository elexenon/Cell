// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "ButtonWithIconTextHint.h"

#include "customLabel.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

ButtonWithIconTextHint::ButtonWithIconTextHint(customButton::ButtonType type, QWidget *parent):
    customButton(type, parent),
    mainLayout(new QHBoxLayout(this)),
    icon(new QLabel(this)),
    tag(new customLabel(this)),
    hint(new customLabel(this))
{
    setCursor(Qt::PointingHandCursor);

    tag->setBrightDarkColor(Cell::CGL70, Cell::CGL255);
    hint->setBrightDarkColor(Cell::CGL70, Cell::CGL255);

    CellWidgetGlobalInterface::_modules << tag << hint;

    QVBoxLayout *VLayoutIcon = new QVBoxLayout;
    VLayoutIcon->setContentsMargins(0, 5, 0, 0);
    VLayoutIcon->addWidget(icon);
    VLayoutIcon->setAlignment(Qt::AlignmentFlag::AlignTop);

    QVBoxLayout *VLayoutTextHint = new QVBoxLayout;
    VLayoutTextHint->setMargin(0);
    VLayoutTextHint->setSpacing(3);
    VLayoutTextHint->addWidget(tag);
    VLayoutTextHint->addWidget(hint);
    VLayoutTextHint->setAlignment(Qt::AlignmentFlag::AlignLeft);

    mainLayout->setContentsMargins(0, 0, 10, 0);
    mainLayout->setSpacing(15);
    mainLayout->addLayout(VLayoutIcon);
    mainLayout->addLayout(VLayoutTextHint);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignCenter);
}

void ButtonWithIconTextHint::initModules(const QString &fileName, int iconWidth, int iconHeight,
                                  const QString& text, int fontSize, const QString& hint)
{
    CellUiGlobal::setLabelPixmap(icon, fileName, iconWidth, iconHeight);
    CellUiGlobal::setCustomTextLabel(tag, CHAR2STR("Microsoft YaHei UI"), fontSize, text);
    CellUiGlobal::setCustomTextLabel(this->hint, CHAR2STR("Microsoft YaHei UI Light"), 12, hint + "。");
}
