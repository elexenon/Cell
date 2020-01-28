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
#include "ButtonWithIcon.h"
#include "customOptionBlock.h"

#include <QHBoxLayout>

customComboBox::customComboBox(const QString &state, QWidget *parent):
    customFrame(CellUiConst::QSS_CUSTOMFRAME_RADIUS, parent),
    currState(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, this)),
    trigger(new ButtonWithIcon(customButton::DYNAMIC_RADIUS, this)),
    optionBlock(new customOptionBlock),
    mainLayout(new QHBoxLayout),
    itemsList(new QList<customOptionBlockItem*>)
{
    setFixedHeight(30);
    setLayout(mainLayout);

    optionBlock->setMainBlockBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL45);

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
}

void customComboBox::setOptionBlockParent(QWidget *parent)
{
    optionBlock->setParent(parent);
}

void customComboBox::addItem(customOptionBlockItem *item, bool addSplitterLine)
{
    optionBlock->addItem(item, addSplitterLine);
}

void customComboBox::tidyItemTags()
{
    optionBlock->tidyItemTags();
}

void customComboBox::setOptionBlockStartEndPos(const QPoint &posS, const QPoint &posE)
{
    optionBlockStartPos = posS;
    optionBlockEndPos = posE;
    optionBlock->move(posS.x(), posS.y());
    optionBlock->hide();
}

void customComboBox::resizeEvent(QResizeEvent *event)
{
    optionBlock->setFixedWidth(event->size().width());
}
