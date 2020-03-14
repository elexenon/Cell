#include "customScrollBlockItem.h"
#include "ButtonWithIcon.h"
#include "customLabel.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QVBoxLayout>

unsigned customScrollBlockItem::_buttonWidth = 200;
unsigned customScrollBlockItem::_unitSpacing = 8;
unsigned customScrollBlockItem::_fontSize = 15;

customScrollBlockItem::customScrollBlockItem(QWidget *parent):
    QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    btn(new ButtonWithIcon(customButton::Type::Checkable, this)),
    label(new customLabel(this))
{
    init();
    setEventConnections();
}

void customScrollBlockItem::initModules(const QString &tag, const QString &fileName, int iconWidth, int iconHeight)
{
    btn->setBrightDarkColor(Cell::CGL218, Cell::CGL100);
    btn->setBrightCheckedColor(Cell::CGL218);
    btn->setDarkCheckedColor(Cell::CGL100);
    btn->initModules(fileName, iconWidth, iconHeight);
    btn->setFixedSize(_buttonWidth, _buttonWidth - _unitSpacing - _fontSize);
    btn->drawFocusEdgeOnChecked();
    label->setBrightDarkColor(Cell::CGL70, Cell::CGL255);
    CellUiGlobal::setCustomTextLabel(label, CHAR2STR("Microsoft YaHei UI Light"), _fontSize, tag);
}

void customScrollBlockItem::init()
{
    mainLayout->setMargin(0);
    mainLayout->setSpacing(_unitSpacing);
    mainLayout->addWidget(btn);
    mainLayout->addWidget(label);
    _modules << btn << label;
}

void customScrollBlockItem::setColorScheme(Cell::ColorScheme mode){
    CellWidgetGlobalInterface::setColorScheme(mode);
}

void customScrollBlockItem::setColor(const QColor &color){
    CellWidgetGlobalInterface::setColor(color);
}

void customScrollBlockItem::changeToColor(const QColor &startColor, const QColor &targetColor, int duration)
{
    (void)startColor;
    (void)targetColor;
    (void)duration;
}
