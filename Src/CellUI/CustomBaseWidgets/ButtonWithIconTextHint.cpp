// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "ButtonWithIconTextHint.h"

#include "customLabel.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

ButtonWithIconTextHint::ButtonWithIconTextHint(customButton::TYPE type, QWidget *parent):
    customButton(type, parent),
    mainLayout(new QHBoxLayout),
    icon(new QLabel(this)),
    tag(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, this)),
    hint(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, this))
{
    tag->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);
    hint->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);

    QVBoxLayout *VLayoutIcon = new QVBoxLayout;
    VLayoutIcon->setMargin(0);
    VLayoutIcon->addWidget(icon);
    VLayoutIcon->setAlignment(Qt::AlignmentFlag::AlignTop);

    QVBoxLayout *VLayoutTextHint = new QVBoxLayout;
    VLayoutTextHint->setMargin(0);
    VLayoutTextHint->setSpacing(3);
    VLayoutTextHint->addWidget(tag);
    VLayoutTextHint->addWidget(hint);
    VLayoutTextHint->setAlignment(Qt::AlignmentFlag::AlignLeft);

    mainLayout->setContentsMargins(10, 0, 0, 0);
    mainLayout->setSpacing(8);
    mainLayout->addLayout(VLayoutIcon);
    mainLayout->addLayout(VLayoutTextHint);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignCenter);
    setLayout(mainLayout);
}

void ButtonWithIconTextHint::Init(const QString &fileName, int iconWidth, int iconHeight,
                                  const QString& text, int fontSize, const QString& hint)
{
    QPixmap newPixmap;
    newPixmap.load(CellUiConst::IMG_DIR + fileName);
    newPixmap = newPixmap.scaled(iconWidth, iconHeight);
    icon->setPixmap(newPixmap);

    CellUiGlobal::setCustomTextLabel(tag, CHAR2STR("Microsoft YaHei UI Light"), fontSize, text);

    CellUiGlobal::setCustomTextLabel(this->hint, CHAR2STR("Microsoft YaHei UI Light"), 13, hint);
}
