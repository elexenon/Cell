#include "customLineEdit.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"
#include "../../CellCore/Kits/CellGlobalMacros.h"

#include <QLineEdit>

using CellEntityTools::styleSheetLoader;

customLineEdit::customLineEdit(QWidget *parent):
    QLineEdit(parent),
    m_mode(CellUiGlobal::_DARK)
{
    init();
}

void customLineEdit::init()
{
    setColorScheme(CellUiGlobal::_BRIGHT);
}

void customLineEdit::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = mode;
    const QString targetCss = (mode == CellUiGlobal::_BRIGHT ? "CustomLineEditBright.css"
                                                             : "CustomLineEditDark.css");
    styleSheetLoader->setStyleSheetName(targetCss);
    setStyleSheet(styleSheetLoader->styleSheet());
}
