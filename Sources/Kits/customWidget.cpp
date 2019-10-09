#include "Headers/Kits/customWidget.h"

customWidget::customWidget(QWidget *parent):
    QWidget(parent)
{}

const QColor customWidget::color() const
{
    return m_color;
}

void customWidget::setColor(const QColor color)
{
    m_color = color;
    QString qss=QString("QWidget{background-color:rgb(%1,%2,%3);}").arg(color.red()).arg(color.green()).arg(color.blue());
    setStyleSheet(qss);
}

void customWidget::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    QStyleOption opt;
    opt.initFrom(this);
    opt.rect = rect();
    painter.drawPrimitive(QStyle::PE_Widget, opt);
    QWidget::paintEvent(event);
}
