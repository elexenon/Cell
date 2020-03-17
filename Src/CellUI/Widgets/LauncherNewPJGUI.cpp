// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "LauncherNewPJGUI.h"

#include "../CustomBaseWidgets/ButtonWithText.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/customFrame.h"
#include "../CustomBaseWidgets/customTitleBar.h"
#include "../CustomBaseWidgets/newPJPageBase.h"
#include "../../CellCore/Kits/CellUtility.h"

#include "NewPJGUIModel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>

LauncherNewPJGUI::LauncherNewPJGUI(QWidget *parent):
    customWinstyleDialog(parent),
    mainLayout(new QVBoxLayout(this)),
    titleBar(new customTitleBar(this)),
    stackedWidget(new QStackedWidget(this)),
    modelPage(new NewPJGUIModel(this)),
    configPage(new newPJPageBase(this)),
    bottomBar(new customFrame(customFrame::Type::Regular, this)),
    btnCancel(new ButtonWithText(customButton::Type::Dynamic, bottomBar)),
    btnBackward(new ButtonWithText(customButton::Type::Dynamic, bottomBar)),
    btnForward(new ButtonWithText(customButton::Type::Dynamic, bottomBar))
{
    init();
    setEventConnections();
}

void LauncherNewPJGUI::init()
{
    customWinstyleDialog::LoadWinStyle(this);
    setWindowTitle(CHAR2STR("New Project"));
    setAttribute(Qt::WA_DeleteOnClose);
    setBrightDarkColor(Cell::CGL255, Cell::CGL30);
    resize(900, 560);

    // Set title bar.
    titleBar->setFixedHeight(40);
    titleBar->setBrightDarkColor(Cell::CGL218, Cell::CGL45);
    titleBar->setText(CHAR2STR("新建项目"), Cell::CGL70);

    // Set  bottom Bar.
    btnCancel->setBrightDarkColor(Cell::CGL60, Cell::CGL60);
    btnCancel->setBrightHoveringColor(Cell::CellThemeColor::ExitRed);
    btnCancel->setDarkHoveringColor(Cell::CellThemeColor::ExitRed);
    btnCancel->setAnimationDuration(200);
    btnCancel->setTextColor(Cell::CGL255, Cell::CGL255);
    btnCancel->initModules(CHAR2STR("取消"), 15);
    btnCancel->setFixedSize(100, 40);

    btnBackward->setBrightDarkColor(Cell::CGL70, Cell::CGL70);
    btnBackward->setBrightHoveringColor(Cell::CellThemeColor::NavyBlue);
    btnBackward->setDarkHoveringColor(Cell::CellThemeColor::NavyBlue);
    btnBackward->setAnimationDuration(200);
    btnBackward->setTextColor(Cell::CGL255, Cell::CGL255);
    btnBackward->initModules(CHAR2STR("后退"), 15);
    btnBackward->setFixedSize(100, 40);

    btnForward->setBrightDarkColor(Cell::CGL100, Cell::CGL100);
    btnForward->setBrightHoveringColor(Cell::CellThemeColor::NavyBlue);
    btnForward->setDarkHoveringColor(Cell::CellThemeColor::NavyBlue);
    btnForward->setAnimationDuration(200);
    btnForward->setTextColor(Cell::CGL255, Cell::CGL255);
    btnForward->initModules(CHAR2STR("前进"), 15);
    btnForward->setFixedSize(100, 40);

    QHBoxLayout *HLayoutBottom = new QHBoxLayout(bottomBar);
    HLayoutBottom->setMargin(0);
    HLayoutBottom->setSpacing(0);
    HLayoutBottom->addWidget(btnCancel);
    HLayoutBottom->addStretch();
    HLayoutBottom->addWidget(btnBackward);
    HLayoutBottom->addWidget(btnForward);

    // Set Bottom Bar.
    bottomBar->setBrightDarkColor(Cell::CGL60, Cell::CGL60);
    bottomBar->setFixedHeight(40);

    // Set Config Page
    configPage->setPageTitle(CHAR2STR("配置"));

    stackedWidget->addWidget(modelPage);
    stackedWidget->addWidget(configPage);

    // Set main layout.
    mainLayout->addWidget(titleBar);
    mainLayout->addWidget(stackedWidget);
    mainLayout->addWidget(bottomBar);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    CellWidgetGlobalInterface::_modules << titleBar << btnCancel
             << btnForward << btnBackward << bottomBar << modelPage << configPage;
}

void LauncherNewPJGUI::setEventConnections()
{
    connect(btnCancel, &QPushButton::clicked, [=]{this->close();});
    connect(btnForward, &QPushButton::clicked, this, [=]{
        if(stackedWidget->currentIndex() == 1){
            emit projectSettled();
            this->close();
        }
        else{
            stackedWidget->setCurrentIndex(1);
            btnForward->setEnabled(false);
        }
    });
    connect(btnBackward, &QPushButton::clicked, [=]{

        stackedWidget->setCurrentIndex(0);
    });
    connect(modelPage, &NewPJGUIModel::typeSeleted, [=](CellProjectEntity::ProjectType type){
        currEntity.setType(type);
    });
    connect(configPage, &newPJPageBase::pathSettled, this, &LauncherNewPJGUI::setPath);
    connect(configPage, &newPJPageBase::nameSettled, this, &LauncherNewPJGUI::setName);
}

void LauncherNewPJGUI::setName(const QString &name)
{
    currEntity.setName(name);
    judgeValidProject();
}

void LauncherNewPJGUI::setPath(const QString &path)
{
    currEntity.setPath(path);
    judgeValidProject();
}

void LauncherNewPJGUI::judgeValidProject()
{
    CellProjectEntity::validEntity(currEntity) ?
        btnForward->setEnabled(true):
        btnForward->setEnabled(false);
}
