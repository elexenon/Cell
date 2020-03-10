#include "LauncherNewPJGUI.h"

#include "../CustomBaseWidgets/ButtonWithText.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/customFrame.h"
#include "../CustomBaseWidgets/customTitleBar.h"
#include "../CustomBaseWidgets/customNavigator.h"
#include "../CustomBaseWidgets/customSmoothScrollArea.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

LauncherNewPJGUI::LauncherNewPJGUI(QWidget *parent):
    customWinstyleDialog(parent),
    mainLayout(new QVBoxLayout(this)),
    titleBar(new customTitleBar(this)),
    navigator(new customNavigator(this)),
    scrollArea(new customSmoothScrollArea(this)),
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

    // Set navigator.
    navigator->setFixedWidth(200);
    navigator->setButtonHeight(60);

    // Set the secondary layout.
    QHBoxLayout *HLayout = new QHBoxLayout;
    HLayout->setMargin(0);
    HLayout->setSpacing(0);
    HLayout->addWidget(navigator);
    HLayout->addWidget(scrollArea);

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

    bottomBar->setBrightDarkColor(Cell::CGL60, Cell::CGL60);
    bottomBar->setFixedHeight(40);

    // Set main layout.
    mainLayout->addWidget(titleBar);
    mainLayout->addLayout(HLayout);
    mainLayout->addWidget(bottomBar);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
}

void LauncherNewPJGUI::setEventConnections()
{

}
