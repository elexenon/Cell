// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "ButtonWithIcon.h"

#include <QHBoxLayout>
#include <QLabel>

ButtonWithIcon::ButtonWithIcon(customButton::TYPE type, QWidget *parent):
    customButton(type, parent),
    mainLayout(new QHBoxLayout),
    icon(new QLabel(this))
{
    mainLayout->setMargin(0);
    mainLayout->addWidget(icon);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    setLayout(mainLayout);
}

void ButtonWithIcon::Init(const QString& fileName, int iconWidth, int iconHeight)
{
    QPixmap newPixmap;
    newPixmap.load(CellUiConst::IMG_DIR + fileName);
    newPixmap = newPixmap.scaled(iconWidth, iconHeight);

    icon->setPixmap(newPixmap);
    icon->setStyleSheet(CHAR2STR("QLabel{background:transparent;}"));
}
