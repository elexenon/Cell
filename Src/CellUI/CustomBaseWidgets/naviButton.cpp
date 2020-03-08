#include "naviButton.h"
#include "../../CellCore/CellNamespace.h"
#include "../../CellCore/Kits/CellUtility.h"
#include "customLabel.h"

#include <QVBoxLayout>

naviButton::naviButton(QWidget *parent) noexcept:
    QPushButton(parent),
    mainLayout(new QVBoxLayout(this)),
    tag(new customLabel(this))
{
    setLayout(mainLayout);
    setCursor(Qt::PointingHandCursor);
    setCheckable(true);

    mainLayout->setMargin(0);
    mainLayout->addWidget(tag);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);

    setTextColor(Cell::CGL70, Cell::CGL255);
}

void naviButton::init(const QString &text, int fontSize)
{
    CellUiGlobal::setCustomTextLabel(tag, CHAR2STR("Microsoft YaHei UI Light"), fontSize, text);
}

void naviButton::setTextColor(const CellVariant &b, const CellVariant &d)
{
    tag->setBrightDarkModeColor(b, d);
}

void naviButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if(!isChecked()){
        painter.setBrush(QBrush(QColor(247,247,247)));
        painter.drawRect(this->rect());
    }
    else{
        painter.setBrush(QBrush(QColor(218,218,218)));
        painter.drawRect(this->rect());
        painter.setBrush(QBrush(CellVariant(Cell::CellThemeColor::NavyBlue).toColor()));
        painter.drawRect(0, 0, 5, this->height());
    }
}
