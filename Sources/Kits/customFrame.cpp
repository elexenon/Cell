#include "../../Headers/Kits/customFrame.h"
#include <QDebug>

customFrame::customFrame(QWidget *parent):
    QFrame(parent)
{
    m_color = QColor(218, 218, 218);
}

const QColor customFrame::color() const
{
    return m_color;
}

void customFrame::setColor(const QColor color)
{
    m_color = color;
    QString qss=QString("QFrame{border-radius:5px; background-color: rgb(%1, %2, %3);}").arg(color.red()).arg(color.green()).arg(color.blue());
    setStyleSheet(qss);
}

const QColor customFrame::b_color() const
{
    return bright;
}

const QColor customFrame::d_color() const
{
    return dark;
}
