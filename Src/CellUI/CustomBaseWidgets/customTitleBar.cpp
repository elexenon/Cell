// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "customTitleBar.h"
#include "customLabel.h"
#include "../../CellCore/CellNamespace.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QLabel>
#include <QHBoxLayout>

customTitleBar::customTitleBar(QWidget *parent):
    customFrame(customFrame::Regular, parent),
    mainLayout(new QHBoxLayout),
    label_title(new customLabel(this)),
    icon(new QLabel(this))
{
    setFixedHeight(50);

    QPixmap defaultPixmap;
    defaultPixmap.load(CellUiLiteral::IMG_DIR + CHAR2STR("cellLogo28"));
    defaultPixmap = defaultPixmap.scaled(height()/2, height()/2);
    icon->setPixmap(defaultPixmap);

    QFont defaultFont(CHAR2STR("Microsoft YaHei UI Light"));
    defaultFont.setPixelSize(height()/3);
    label_title->setText(CHAR2STR("Title"));
    label_title->setFont(defaultFont);
    label_title->setBrightDarkModeColor(Cell::CGL130, Cell::CGL255);

    mainLayout->setContentsMargins(10, 0, 0, 0);
    mainLayout->setSpacing(8);
    mainLayout->addWidget(icon);
    mainLayout->addWidget(label_title);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void customTitleBar::setText(const QString &text, const CellVariant &color)
{
    label_title->setText(text);
    label_title->setBrightDarkModeColor(color, Cell::CGL255);
}

void customTitleBar::setLeftMargin(int value)
{
    mainLayout->setContentsMargins(value, 0, 0, 0);
}

void customTitleBar::setIcon(const QString &fileName, int iconWidth, int iconHeight)
{
    QPixmap newPixmap;
    newPixmap.load(CellUiLiteral::IMG_DIR + fileName);
    newPixmap = newPixmap.scaled(iconWidth, iconHeight);
    icon->setPixmap(newPixmap);
}

void customTitleBar::setHeight(int value)
{
    setFixedHeight(value);
}

void customTitleBar::setFont(const QFont &font)
{
    label_title->setFont(font);
}

void customTitleBar::addWidget(QWidget *obj)
{
    mainLayout->addWidget(obj);
}

void customTitleBar::addLayout(QLayout *obj)
{
    mainLayout->addLayout(obj);
}

void customTitleBar::setColorScheme(Cell::ColorScheme mode)
{
    customFrame::setColorScheme(mode);
    label_title->setColorScheme(mode);
}
