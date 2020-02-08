// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "../../CellCore/Kits/CellUtility.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"
#include "customDialogButton.h"
#include "customLabel.h"
#include "ButtonWithIcon.h"
#include "customOptionBlock.h"

#include <QHBoxLayout>

customDialogButton::customDialogButton(const QString &state, QWidget *parent):
    customFrame(customFrame::_RADIUS, parent),
    currState(new customLabel(this)),
    trigger(new ButtonWithIcon(customButton::DYNAMIC_RADIUS, this)),
    mainLayout(new QHBoxLayout(this))
{
    setFixedHeight(30);
    setLayout(mainLayout);

    CellUiGlobal::setCustomTextLabel(currState, CHAR2STR("Microsoft YaHei UI Light"), 15, state);
    currState->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);

    trigger->setFixedSize(35, 22);
    trigger->setBrightModeHoveringColor(CellUiConst::GRAYLEVEL255);
    trigger->setDarkModeHoveringColor(CellUiConst::GRAYLEVEL180);
    trigger->setBrightDarkModeColor(CellUiConst::GRAYLEVEL218, CellUiConst::GRAYLEVEL45);
    trigger->setAnimationDuration(200);
    trigger->setCursor(Qt::PointingHandCursor);
    trigger->Init(CHAR2STR("popUpIcon.png"), 15, 12);

    mainLayout->setContentsMargins(11, 3, 3, 3);
    mainLayout->addWidget(currState);
    mainLayout->addStretch();
    mainLayout->addWidget(trigger);

    setEventConnections();
}

void customDialogButton::setText(const QString &text)
{
    currState->setText(text);
}

void customDialogButton::setEventConnections()
{
    connect(trigger, &QPushButton::clicked, this, &customDialogButton::triggerClicked);
}
