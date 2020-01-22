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
    mainLayout(new QHBoxLayout),
    icon(new QLabel(this)),
    tag(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, this))
{
    tag->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);

    mainLayout->setContentsMargins(10, 0, 0, 0);
    mainLayout->setSpacing(8);
    mainLayout->addWidget(icon);
    mainLayout->addWidget(tag);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    setLayout(mainLayout);
}

void ButtonWithIconText::Init(const QString& fileName, int iconWidth, int iconHeight, const QString& text, int fontSize)
{
    QPixmap newPixmap;
    newPixmap.load(CellUiConst::IMG_DIR + fileName);
    newPixmap = newPixmap.scaled(iconWidth, iconHeight);

    icon->setPixmap(newPixmap);
    icon->setStyleSheet(CHAR2STR("QLabel{background:transparent;}"));

    CellUiGlobal::setCustomTextLabel(tag, CHAR2STR("Microsoft YaHei UI Light"), fontSize, text);
}
