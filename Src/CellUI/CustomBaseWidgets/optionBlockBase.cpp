// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "optionBlockBase.h"
#include "customLabel.h"

#include "../../CellCore/Kits/CellUtility.h"

#include <QVBoxLayout>

optionBlockBase::optionBlockBase(const QString& name, QWidget *parent):
    customFrame(customFrame::Type::Regular, parent),
    mainLayout(new QVBoxLayout(this))
{
    optionBlockBase::init();
    addThemeTag(name);
}

void optionBlockBase::init()
{
    setLayout(mainLayout);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(3);
    mainLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
}

void optionBlockBase::addThemeTag(const QString &name)
{
    _theme = name;
    theme = new customLabel(this);
    theme->setBrightDarkColor(Cell::CGL70, Cell::CGL255);
    CellUiGlobal::setCustomTextLabel(theme, CHAR2STR("Microsoft YaHei UI Light"), 15, _theme);

    QHBoxLayout *themeTagLayout = new QHBoxLayout;
    themeTagLayout->addWidget(theme);
    themeTagLayout->setAlignment(Qt::AlignmentFlag::AlignLeft);
    themeTagLayout->setMargin(0);

    mainLayout->addLayout(themeTagLayout);

    CellWidgetGlobalInterface::_modules << theme;
}

void optionBlockBase::enterEvent(QEvent*){
    emit entered(_theme);
}

