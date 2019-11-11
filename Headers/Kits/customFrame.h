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

#include "cell_util.h" // FRAME_TYPE
#include <QFrame>

class customFrame : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit customFrame(FRAME_TYPE type, QWidget *parent = nullptr);
    ~customFrame() = default;

public:
    const QColor color() const;
    void  setColor(const QColor color);

protected:
    const FRAME_TYPE m_type;
    QColor m_color;
};
#endif
