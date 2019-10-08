#pragma once

#include <QFrame>

class customFrame : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit customFrame(QWidget *parent = nullptr);
    ~customFrame() = default;

public:
    const QColor color() const;
    void setColor(const QColor color);
    const QColor b_color() const;
    const QColor d_color() const;

protected:
    QColor m_color;
    QColor bright;
    QColor dark;
};
