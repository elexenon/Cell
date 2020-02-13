// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customTitleBar.h"
#include "customLabel.h"

#include <QLabel>
#include <QHBoxLayout>

//#define CELL_DEBUG

customTitleBar::customTitleBar(QWidget *parent):
    customFrame(customFrame::_REGULAR, parent),
    mainLayout(new QHBoxLayout),
    label_title(new customLabel(this)),
    icon(new QLabel(this))
{
    setFixedHeight(50);

    QPixmap defaultPixmap;
    defaultPixmap.load(CellUiConst::IMG_DIR + CHAR2STR("cellLogo28"));
    defaultPixmap = defaultPixmap.scaled(height()/2, height()/2);
    icon->setPixmap(defaultPixmap);

#ifdef CELL_DEBUG
    qDebug() << height()/2;
#endif

    QFont defaultFont(CHAR2STR("Microsoft YaHei UI Light"));
    defaultFont.setPixelSize(height()/3);
    label_title->setText(CHAR2STR("Title"));
    label_title->setFont(defaultFont);
    label_title->setBrightDarkModeColor(CellUiConst::GRAYLEVEL130, CellUiConst::GRAYLEVEL255);

    mainLayout->setContentsMargins(10, 0, 0, 0);
    mainLayout->setSpacing(8);
    mainLayout->addWidget(icon);
    mainLayout->addWidget(label_title);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void customTitleBar::setText(const QString &text, const QColor& color)
{
    label_title->setText(text);
    label_title->setBrightDarkModeColor(color, CellUiConst::GRAYLEVEL255);
}

void customTitleBar::setLeftMargin(int value)
{
    mainLayout->setContentsMargins(value, 0, 0, 0);
}

void customTitleBar::setIcon(const QString &fileName, int iconWidth, int iconHeight)
{
    QPixmap newPixmap;
    newPixmap.load(CellUiConst::IMG_DIR + fileName);
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

void customTitleBar::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    customFrame::setColorScheme(mode);
    label_title->setColorScheme(mode);
}
