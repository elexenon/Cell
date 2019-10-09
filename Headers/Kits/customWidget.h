/*

  CREATED BY HENGYI YU 2019/10/06
  This class achieve "color" property.

*/
#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QStylePainter>
#include <QStyleOption>

class customWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit customWidget(QWidget *parent = nullptr);

public:
    const QColor color() const;
    void setColor(const QColor color);

protected:
    void paintEvent(QPaintEvent *event) override;

protected:
    QColor m_color;
};
#endif
