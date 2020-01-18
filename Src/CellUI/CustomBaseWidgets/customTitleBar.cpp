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
    customFrame(CellUiConst::QSS_CUSTOMFRAME, parent),
    mainLayout(new QHBoxLayout),
    label_title(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, this)),
    icon(new QLabel(this))
{
    setFixedHeight(50);

    QPixmap defaultPixmap;
    defaultPixmap.load(CellUiConst::IMG_DIR + QString::fromUtf8("CELL_logo_small"));
    defaultPixmap = defaultPixmap.scaled(height()/2+2, height()/2);
    icon->setPixmap(defaultPixmap);

#ifdef CELL_DEBUG
    qDebug() << height()/2;
#endif

    QFont defaultFont(QString::fromUtf8("Microsoft YaHei UI Light"));
    defaultFont.setPixelSize(height()/3);
    label_title->setText(QString::fromUtf8("Title"));
    label_title->setFont(defaultFont);
    label_title->setColor(CellUiConst::GRAYLEVEL130);

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
    label_title->setColor(color);
}

void customTitleBar::setLeftMargin(int value)
{
    mainLayout->setContentsMargins(value, 0, 0, 0);
}

void customTitleBar::setIcon(const QString &fileName, int width, int height)
{
    QPixmap newPixmap;
    newPixmap.load(CellUiConst::IMG_DIR + fileName);
    newPixmap = newPixmap.scaled(width, height);
    icon->setPixmap(newPixmap);
}

void customTitleBar::setHeight(int value)
{
    setFixedHeight(value);
}

void customTitleBar::setFont(QFont &font, int size)
{
    font.setPixelSize(size);
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
