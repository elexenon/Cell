#include "../../Headers/Kits/customscrollarea.h"

customScrollArea::customScrollArea(QWidget *parent):
    QScrollArea(parent)
{

}

const QColor customScrollArea::color() const
{
    return m_color;
}

void customScrollArea::setColor(const QColor color)
{
    m_color = color;
}
