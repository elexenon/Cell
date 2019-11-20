// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
//
// This class implemented "color" custom property.
#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

//#include "cell_util.h"
#include <QLabel>

class customLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit customLabel(const QString &qss, QWidget *parent = nullptr);
    ~customLabel() = default;

public:
    const QColor color() const;
    void         setColor(const QColor color);

protected:
    QColor m_color;
    virtual void mouseReleaseEvent(QMouseEvent*);

private:
    QString BASEQSS;

signals:
    void clicked(void);
};
#endif // CUSTOMLABEL_H
