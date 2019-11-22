// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
//
// This class implemented dropshadow effect & "color" custom property.
#ifndef DROPSHADOWDIALOG_H
#define DROPSHADOWDIALOG_H

#include <QDialog>

class customDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit customDialog(QWidget *parent = nullptr);
    ~customDialog() = default;

public:
    const QColor color() const;
    void         setColor(const QColor &color);

protected:
    QColor       m_color;

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void LoadWinStyle(QDialog *obj);
#endif
};


#endif // DROPSHADOWDIALOG_H
