#pragma once

#include <QLabel>

class customLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit customLabel(QWidget *parent = nullptr);
    ~customLabel() = default;

public:
    const QColor color() const;
    void setColor(const QColor color);

protected:
    QColor m_color;
};
