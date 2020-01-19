// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customOptionBlock.h"
#include "../../CellCore/Kits/CellUtility.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"
#include "customOptionBlockSector.h"
#include "customOptionBlockItem.h"
#include "customLabel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

customOptionBlock::customOptionBlock(QWidget *parent, const QString& name):
    customFrame(CellUiConst::QSS_CUSTOMFRAME, parent),
    mainLayout(new QVBoxLayout),
    mainBlockLayout(new QVBoxLayout),
    theme(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, this)),
    sectorsList(new QList<customOptionBlockSector*>)
{
    theme->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);
    CellUiGlobal::setCustomTextLabel(theme, CHAR2STR("Microsoft YaHei UI Light"), 15, name);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(3);

    mainBlockLayout->setMargin(0);
    mainBlockLayout->setSpacing(0);

    using CellEntityTools::styleSheetLoader;
    styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherSettings_OptionBlock11.css"));
    mainBlock = new customFrame(styleSheetLoader->styleSheet(), this);
    mainBlock->setObjectName(CHAR2STR("optionMainBlock"));
    mainBlock->setBrightDarkModeColor(CellUiConst::GRAYLEVEL218, CellUiConst::GRAYLEVEL45);
    mainBlock->setLayout(mainBlockLayout);

    // Layout For theme tag.
    QHBoxLayout *HLayout = new QHBoxLayout;
    HLayout->addWidget(theme);
    HLayout->addStretch();
    HLayout->setMargin(0);

    mainLayout->addLayout(HLayout);
    mainLayout->addWidget(mainBlock);
    setLayout(mainLayout);
}

void customOptionBlock::addSector(customOptionBlockSector *sector, bool over)
{
    sectorsList->append(sector);
    mainBlockLayout->addWidget(sector);
    sector->setParent(mainBlock);

    blockHeight += sector->height();

    if(!over){
        // Layout For line splitter.
        QFrame *lineSplitter = CellUiGlobal::getLine(CellUiGlobal::LINE_TYPE::HLine);
        QHBoxLayout *layout = new QHBoxLayout;
        layout->setContentsMargins(10, 0, 10, 0);
        layout->addWidget(lineSplitter);
        mainBlockLayout->addLayout(layout);
        blockHeight += 1;
        return;
    }

    int maxTagLen = 0;
    for(auto & sector : *sectorsList)
        if(sector->itemTagMaxLen > maxTagLen) maxTagLen = sector->itemTagMaxLen;

    for(auto & sector : *sectorsList)
    for(auto & item : *(sector->itemsList)){
        int currItemTagLen = item->getTagLen();
        if(currItemTagLen < maxTagLen){
            const QMargins currItemMargins = item->getMargins();
            item->setMargins(item->getMargins().left()+((maxTagLen-currItemTagLen)*18),
                          currItemMargins.top(),currItemMargins.right(),currItemMargins.bottom());
        }
    }

    setFixedHeight(blockHeight + 25);
}
