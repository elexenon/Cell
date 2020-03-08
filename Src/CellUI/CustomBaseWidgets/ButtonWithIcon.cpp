// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "ButtonWithIcon.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QHBoxLayout>
#include <QLabel>

ButtonWithIcon::ButtonWithIcon(customButton::Type type, QWidget *parent):
    customButton(type, parent),
    mainLayout(new QHBoxLayout(this)),
    icon(new QLabel(this))
{
    setLayout(mainLayout);
    setCursor(Qt::PointingHandCursor);

    mainLayout->setMargin(0);
    mainLayout->addWidget(icon);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
}

void ButtonWithIcon::initModules(const QString& fileName, int iconWidth, int iconHeight)
{
    CellUiGlobal::setLabelPixmap(icon, fileName, iconWidth, iconHeight);
}
