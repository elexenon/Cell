#ifndef CUSTOMSCROLLAREA_H
#define CUSTOMSCROLLAREA_H

#include <QScrollArea>

class customScrollArea : public QScrollArea
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit customScrollArea(QWidget *parent = nullptr);
    ~customScrollArea() = default;

public:
    const QColor color() const;
    void setColor(const QColor color);

protected:
    QColor m_color;
};
#endif
