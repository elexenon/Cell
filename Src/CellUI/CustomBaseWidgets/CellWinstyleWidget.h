// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CELLWINSTYLEINTERFACE_H
#define CELLWINSTYLEINTERFACE_H

#include <QWidget>

class CellWinstyleWidget : public QWidget{
public:
    explicit CellWinstyleWidget(QWidget *parent = nullptr);
protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void         LoadWinStyle(QWidget *obj);
};
#endif // CELLWINSTYLEINTERFACE_H
