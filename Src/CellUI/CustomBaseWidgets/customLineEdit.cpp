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
    m_mode(CellUiGlobal::_DARK)
{
    init();
}

void customLineEdit::init()
{
    setColorScheme(CellUiGlobal::_BRIGHT);
    setFont(QFont(CHAR2STR("Microsoft YaHei UI Light")));
}

void customLineEdit::setColorScheme(Cell::ColorScheme mode)
{
    if(mode == m_mode) return;
    m_mode = mode;
    const QString targetCss = (mode == CellUiGlobal::_BRIGHT ? "CustomLineEditBright.css"
                                                             : "CustomLineEditDark.css");
    CellUiGlobal::loader.setFileName(targetCss);
    setStyleSheet(CellUiGlobal::loader.content());
}
