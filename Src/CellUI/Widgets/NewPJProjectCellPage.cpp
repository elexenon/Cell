// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "NewPJProjectCellPage.h"
#include "../../CellCore/Kits/CellUtility.h"

NewPJProjectCellPage::NewPJProjectCellPage(QWidget *parent):
    customFrame(Cell_Const::QSS_CUSTOMFRAME,parent)
{
    Init();
}

void NewPJProjectCellPage::Init()
{
    setColor(Cell_Const::GRAYLEVEL247);
    setGeometry(0,0,599,405);

    using CellEntityTools::styleSheetLoader;


}
