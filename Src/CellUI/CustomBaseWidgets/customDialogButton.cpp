// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "../../CellCore/CellNamespace.h"
#include "../../CellCore/Kits/CellUtility.h"
#include "customDialogButton.h"
#include "customLabel.h"
#include "ButtonWithIcon.h"
#include "customOptionBlock.h"

#include <QHBoxLayout>

customDialogButton::customDialogButton(const QString &state, QWidget *parent):
    customFrame(customFrame::Radius, parent),
    currState(new customLabel(this)),
    trigger(new ButtonWithIcon(customButton::DynamicRadius, this)),
    mainLayout(new QHBoxLayout(this))
{
    setFixedHeight(30);
    setLayout(mainLayout);

    CellUiGlobal::setCustomTextLabel(currState, CHAR2STR("Microsoft YaHei UI Light"), 15, state);
    currState->setBrightDarkModeColor(Cell::CGL70, Cell::CGL255);

    trigger->setFixedSize(35, 22);
    trigger->setBrightModeHoveringColor(Cell::CGL255);
    trigger->setDarkModeHoveringColor(Cell::CGL130);
    trigger->setBrightDarkModeColor(Cell::CGL218, Cell::CGL70);
    trigger->setAnimationDuration(200);
    trigger->setCursor(Qt::PointingHandCursor);
    trigger->init(CHAR2STR("popUpIcon.png"), 15, 12);

    mainLayout->setContentsMargins(11, 3, 3, 3);
    mainLayout->addWidget(currState);
    mainLayout->addStretch();
    mainLayout->addWidget(trigger);

    _modules << currState << trigger;

    setEventConnections();
}

void customDialogButton::setText(const QString &text)
{
    currState->setText(text);
}

void customDialogButton::setColorScheme(Cell::ColorScheme mode)
{
    customFrame::setColorScheme(mode);
}

void customDialogButton::setEventConnections()
{
    connect(trigger, &QPushButton::clicked, [this]{
        emit clicked();
    });
}
