// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customWidget.h"
#include "../../CellCore/Kits/WindWMAPI.h"

customWidget::customWidget(QWidget *parent):
    CellWinstyleWidget(parent)
{}

void customWidget::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    setStyleSheet(QString("background-color:rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue()));
}
