// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customLabel.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"

customLabel::customLabel(QWidget *parent):
    QLabel(parent)
{
    using CellEntityTools::styleSheetLoader;
    styleSheetLoader->setStyleSheetName(CHAR2STR("CustomLabel.css"));
    setBaseQss(styleSheetLoader->styleSheet());
}

void customLabel::setBaseQss(const QString &qss)
{
    CellWidgetGlobalInterface::setBaseQss(qss);
}

void customLabel::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue()));
}

void customLabel::changeToColor(const QColor &startColor, const QColor &targetColor, int duration)
{
    CellUiGlobal::setPropertyAnimation({animi},
                                      "color",
                                       startColor,
                                       targetColor,
                                       duration,
                                       easingCurve,
                                      {this}, nullptr);
}

void customLabel::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    CellWidgetGlobalInterface::setColorScheme(mode);
}
