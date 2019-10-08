#pragma once

#include "_utility.h"
#include <QFrame>

class customFrame : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit customFrame(WINDOW_TYPE type, QWidget *parent = nullptr);
    ~customFrame() = default;

public:
    const QColor color() const;
    void  setColor(const QColor color);

protected:
    const WINDOW_TYPE m_type;
    QColor m_color;
};
