// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
//
// This class implemented "color" custom property for different shape of frames.
#ifndef CUSTOMFRAME_H
#define CUSTOMFRAME_H

#include <QFrame>

class customFrame : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

    const QString BASEQSS;
public:
    explicit customFrame(const QString &qss, QWidget *parent = nullptr);
    ~customFrame() = default;

public:
    const QColor color() const;
    void         setColor(const QColor color);

protected:
    QColor       m_color;
};
#endif
