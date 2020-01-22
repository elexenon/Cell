// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "../../CellCore/Kits/CellUtility.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"
#include "customComboBox.h"
#include "customLabel.h"
#include "customButton.h"
#include "customOptionBlock.h"

#include <QHBoxLayout>

customComboBox::customComboBox(const QString &state, QWidget *parent):
    customFrame(CellUiConst::QSS_CUSTOMFRAME_RADIUS, parent),
    currState(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, this)),
    trigger(new customButton(customButton::DYNAMIC_RADIUS, this)),
    optionBlock(new customOptionBlock(this)),
    mainLayout(new QHBoxLayout)
{
    mainLayout->setContentsMargins(5, 3, 5, 3);
    mainLayout->addWidget(currState);
    mainLayout->addStretch();
    mainLayout->addWidget(trigger);

    CellUiGlobal::setCustomTextLabel(currState, CHAR2STR("Microsoft YaHei UI Light"), 14, state);

}
