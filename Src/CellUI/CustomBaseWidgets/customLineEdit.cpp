// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "customLineEdit.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

#include <QLineEdit>

customLineEdit::customLineEdit(QWidget *parent):
    QLineEdit(parent),
    mMode(Cell::ColorScheme::Dark)
{
    init();
}

void customLineEdit::init()
{
    setColorScheme(Cell::ColorScheme::Bright);
    setFont(QFont(CHAR2STR("Microsoft YaHei UI Light")));
}

void customLineEdit::setColorScheme(Cell::ColorScheme mode)
{
    if(mode == mMode) return;
    mMode = mode;
    const QString targetCss = (mode == Cell::ColorScheme::Bright ? "CustomLineEditBright.css"
                                                             : "CustomLineEditDark.css");
    CellUiGlobal::loader.setFileName(targetCss);
    setStyleSheet(CellUiGlobal::loader.content());
}
