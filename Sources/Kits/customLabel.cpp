#include "../../Headers/Kits/customLabel.h"

customLabel::customLabel(QWidget *parent):
    QLabel(parent)
{

}

const QColor customLabel::color() const
{
    return m_color;
}

void customLabel::setColor(const QColor color)
{
    m_color = color;
}


